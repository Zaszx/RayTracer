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
}

void Scene::render(const Camera& camera, const String& outputFilePath) const
{
	Vec3 renderedPixels[1024][1024];

	for (int i = 0; i < camera.imageWidth; i++)
	{
		for (int j = 0; j < camera.imageHeight; j++)
		{
			Ray* ray = new Ray();
			ray->origin = camera.pos;
			Vec3 p = camera.pos + (camera.gaze * camera.distance);
			float ununyataydakimiktari = (camera.left + ((camera.right - camera.left) / camera.imageWidth) * (i + 0.5));
			Vec3 u = camera.gaze.cross(camera.up);
			u.normalize();
			float vnindikeydekimiktari = (camera.bottom + ((camera.top - camera.bottom) / camera.imageHeight) * (j + 0.5));
			ray->destination = p + (u * ununyataydakimiktari) + (camera.up * vnindikeydekimiktari);
			float minDist = 10000000;
			Object* nearest = NULL;
			Vec3 nearestPoint;
			for (int o = 0; o < objects.size(); o++)
			{
				float dist;
				Vec3 point;
				if (objects[o]->intersects(*ray, dist, point))
				{
					if (dist < minDist)
					{
						minDist = dist;
						nearest = objects[o];
						nearestPoint = point;
					}
				}
			}
			if (nearest)
			{
				Ray* lightRay;
				for (int l = 0; l < lights.size(); l++)
				{
					lightRay = new Ray();
					lightRay->origin = nearestPoint;
					lightRay->destination = lights[l]->position;
					Vec3 d;
					d.x = lightRay->destination.x - lightRay->origin.x;
					d.y = lightRay->destination.y - lightRay->origin.y;
					d.z = lightRay->destination.z - lightRay->origin.z;
					d.normalize();
					nearest->normal.normalize();
					float hebele = d.dot(nearest->normal);
					hebele = hebele < 0 ? 0 : hebele;

					float lol = hebele * lights[l]->intensity.x;
					renderedPixels[i][j].x += nearest->material->diffuse.x * lol;

					lol = hebele * lights[l]->intensity.y;
					renderedPixels[i][j].y += nearest->material->diffuse.y * lol;

					lol = hebele * lights[l]->intensity.x;
					renderedPixels[i][j].z += nearest->material->diffuse.z * lol;

					Vec3 pointToCamera = nearestPoint - camera.pos;
					pointToCamera.normalize();
					Vec3 h = pointToCamera + d;
					h.normalize();
					float ndoth = nearest->normal.dot(h);
					if (ndoth < 0) ndoth = 0;
					pow(ndoth, nearest->material->specExp);

					lol = nearest->material->specular.x * lights[l]->intensity.x * ndoth;
					renderedPixels[i][j].x += lol;

					lol = nearest->material->specular.y * lights[l]->intensity.y * ndoth;
					renderedPixels[i][j].y += lol;

					lol = nearest->material->specular.z * lights[l]->intensity.z * ndoth;
					renderedPixels[i][j].z += lol;

					delete lightRay;
				}


				renderedPixels[i][j].x += nearest->material->ambient.x * ambientLightColor.x;
				renderedPixels[i][j].y += nearest->material->ambient.y * ambientLightColor.y;
				renderedPixels[i][j].z += nearest->material->ambient.z * ambientLightColor.z;
			}
			else
			{
				renderedPixels[i][j] = backgroundColor;
			}
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
