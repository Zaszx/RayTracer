#include "CommonIncludes.h"
#include "Sphere.h"

bool Sphere::intersects(const Ray& ray, float* distance /*= nullptr*/, Vec3* point /*= nullptr*/)
{
	Vec3 d,e,c;
	e = ray.getOrigin();
	d = ray.getDirection();

	c = position;
	float first = (d.dot(e-c)) * (d.dot(e-c));
	float second = (d.dot(d));
	float third = (e-c).dot(e-c) - (radius*radius);
	float disc = (first - (second*third));
	if( disc < 0)
	{
		return false;
	}
	else
	{
		float solutions[2];
		solutions[0] = ((d * -1).dot(e-c) + sqrt(disc)) / d.dot(d);
		solutions[1] = ((d * -1).dot(e-c) - sqrt(disc)) / d.dot(d);
		Vec3 dir = ray.getDirection();
		float intersectionDistance;
		Vec3 intersectionPoint;
		if(solutions[0] >= 0 && solutions[0] < solutions[1])
		{
			intersectionDistance = solutions[0];
		}
		else if(solutions[1] >= 0)
		{
			intersectionDistance = solutions[1];
		}
		else
		{
			return false;
		}

		Vec3 iteration(intersectionDistance*dir.x, intersectionDistance*dir.y, intersectionDistance*dir.z);
		intersectionPoint = Vec3(ray.getOrigin().x + iteration.x, ray.getOrigin().y + iteration.y, ray.getOrigin().z + iteration.z);
		normal = intersectionPoint - position;
		normal.normalize();

		if (distance)
		{
			*distance = intersectionDistance;
		}
		if (point)
		{
			*point = intersectionPoint;
		}

		return true;

	}
}

Sphere::Sphere()
{
	
}

void Sphere::read(TiXmlNode* node)
{
	TiXMLHelper::GetAttribute(node, "position", &position);
	TiXMLHelper::GetAttribute(node, "radius", &radius);
	String materialName;
	TiXMLHelper::GetAttribute(node, "materialName", &materialName);
	material = resourceManager.getMaterial(materialName);
}
