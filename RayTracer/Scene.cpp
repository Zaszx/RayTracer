#include "CommonIncludes.h"
#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::read(string xmlPath)
{
	TiXmlDocument xmlDocument(xmlPath.c_str());
	bool success = xmlDocument.LoadFile();
	assert(success);

	TiXmlNode* sceneNode = xmlDocument.FirstChild("scene");
	assert(sceneNode);

	// Read objects
	TiXmlNode* objectsNode = sceneNode->FirstChild("objects");
	if (objectsNode)
	{
		TiXmlNode* trianglesNode = objectsNode->FirstChild("triangles");
		if (trianglesNode)
		{
			TiXmlNode* triangleNode = trianglesNode->FirstChild("triangle");
			while (triangleNode)
			{
				Triangle* triangle = new Triangle();
				triangle->read(triangleNode);
				objects.push_back(triangle);
				triangleNode = triangleNode->NextSibling();
			}
		}

		TiXmlNode* spheresNode = objectsNode->FirstChild("spheres");
		if (spheresNode)
		{
			TiXmlNode* sphereNode = spheresNode->FirstChild("sphere");
			while (sphereNode)
			{
				Sphere* sphere = new Sphere();
				sphere->read(sphereNode);
				objects.push_back(sphere);
				sphereNode = sphereNode->NextSibling();
			}
		}
	}

	// Read Lights
	TiXmlNode* lightsNode = sceneNode->FirstChild("lights");
	if (lightsNode)
	{
		TiXmlNode* lightNode = lightsNode->FirstChild("light");
		while (lightNode)
		{
			Light* light = new Light();
			light->read(lightNode);
			lights.push_back(light);
			lightNode = lightNode->NextSibling();
		}
	}

	// Read Attributes
	TiXMLHelper::GetAttribute(sceneNode, "backgroundColor", &backgroundColor);
	TiXMLHelper::GetAttribute(sceneNode, "ambientLight", &ambientLightColor);
	TiXMLHelper::GetAttribute(sceneNode, "reflectionCount", &reflectionCount);
}

void Scene::render(const Camera& camera, const String& outputFilePath) const
{
	Vec3 renderedPixels[1024][1024];

	for (int i = 0; i < camera.imageWidth; i++)
	{
		for (int j = 0; j < camera.imageHeight; j++)
		{
			Vec3 p = camera.pos + (camera.gaze * camera.distance);
			float uIterationAmount = (camera.left + ((camera.right - camera.left) / camera.imageWidth) * (i + 0.5));
			Vec3 u = camera.gaze.cross(camera.up);
			u.normalize();
			float vIterationAmount = (camera.bottom + ((camera.top - camera.bottom) / camera.imageHeight) * (j + 0.5));
			Vec3 rayDestination = p + (u * uIterationAmount) + (camera.up * vIterationAmount);
			Vec3 rayDirection = rayDestination - camera.pos;
			rayDirection.normalize();

			Ray ray(camera.pos, rayDirection);
			Vec3 resultColor = traceRay(ray, camera, Vec3(1, 1, 1));
			renderedPixels[i][j] = resultColor;
		}
	}

	int totalImageSize = camera.imageWidth * camera.imageHeight * 3;
	unsigned char* toPPM = new unsigned char[totalImageSize];
	for (int i = 0; i < camera.imageHeight; i++)
	{
		for (int j = 0; j < camera.imageWidth; j++)
		{
			toPPM[(camera.imageWidth - j - 1)*camera.imageWidth * 3 + i * 3] = renderedPixels[i][j].x > 255 ? 255 : renderedPixels[i][j].x;
			toPPM[(camera.imageWidth - j - 1)*camera.imageWidth * 3 + i * 3 + 1] = renderedPixels[i][j].y > 255 ? 255 : renderedPixels[i][j].y;
			toPPM[(camera.imageWidth - j - 1)*camera.imageWidth * 3 + i * 3 + 2] = renderedPixels[i][j].z > 255 ? 255 : renderedPixels[i][j].z;
		}
	}
	FILE* out = fopen(outputFilePath.charP(), "wb");
	fprintf(out, "P6 %d %d %d\n", camera.imageWidth, camera.imageHeight, 255);
	fwrite(toPPM, totalImageSize, 1, out);
	fclose(out);
}

Vec3 Scene::traceRay(const Ray& ray, const Camera& camera, Vec3 reflectionFactor, int depth /*= 0*/) const
{
	Vec3 resultColor;

	float minDist = FLT_MAX;
	Object* nearest = nullptr;
	Vec3 nearestPoint;
	for (int o = 0; o < objects.size(); o++)
	{
		float dist;
		Vec3 point;
		if (objects[o]->intersects(ray, &dist, &point))
		{
			if (dist < minDist && dist < 100000)
			{
				minDist = dist;
				nearest = objects[o];
				nearestPoint = point;
			}
		}
	}

	if (nearest)
	{
		resultColor = resultColor + calculateLighting(nearestPoint, ray, nearest, camera);

		if (depth != reflectionCount)
		{
			Vec3 reflectionVector = ray.getDirection() - nearest->normal * 2 * (ray.getDirection().dot(nearest->normal));
			reflectionVector.normalize();
			Ray reflectionRay(nearestPoint, reflectionVector);
			resultColor = resultColor + traceRay(reflectionRay, camera, reflectionFactor * nearest->material->reflection, depth + 1) * reflectionFactor;
		}

		if (depth == 0)
		{
			resultColor = resultColor + nearest->material->ambient * ambientLightColor;	
		}
	}
	else if (depth == 0)
	{
		resultColor = backgroundColor;
	}

	return resultColor;
}

Vec3 Scene::calculateLighting(Vec3 nearestPoint, const Ray& ray, Object* nearest, const Camera &camera) const
{
	Vec3 resultColor;

	for (int l = 0; l < lights.size(); l++)
	{
		float lightDistanceToIntersection = (lights[l]->position - nearestPoint).length();
		Vec3 lightDirection = lights[l]->position - nearestPoint;
		lightDirection.normalize();

		Ray lightRay(nearestPoint, lightDirection);
		bool isInShadow = false;

		for (int o = 0; o < objects.size(); o++)
		{
			float intersectionDistance;
			if (objects[o] != nearest && 
				objects[o]->intersects(lightRay, &intersectionDistance) &&
				intersectionDistance < lightDistanceToIntersection)
			{
				isInShadow = true;
				break;
			}
		}

		if (!isInShadow)
		{
			// Diffuse Light
			nearest->normal.normalize();
			float ndotl = lightRay.getDirection().dot(nearest->normal);
			ndotl = ndotl < 0 ? 0 : ndotl;

			float distanceToLightSquared = (nearestPoint - lights[l]->position).lengthSquared();
			Vec3 lightEffectiveIntensity = lights[l]->intensity / (4 * PI * distanceToLightSquared);

			resultColor = resultColor + nearest->material->diffuse * lightEffectiveIntensity * ndotl;

			// Specular Light
			Vec3 pointToCamera = camera.pos - nearestPoint;
			pointToCamera.normalize();
			Vec3 h = pointToCamera + lightRay.getDirection();
			h.normalize();
			float ndoth = nearest->normal.dot(h);
			if (ndoth < 0) ndoth = 0;

			ndoth = pow(ndoth, nearest->material->specExp);

			resultColor = resultColor + nearest->material->specular * lightEffectiveIntensity * ndoth;

		}
	}

	return resultColor;
}
