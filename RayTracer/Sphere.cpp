#include "CommonIncludes.h"
#include "Sphere.h"

bool Sphere::intersects(const Ray& ray, float& distance, Vec3& point)
{
	Vec3 d,e,c;
	e = ray.origin;
	d.x = ray.destination.x - ray.origin.x;
	d.y = ray.destination.y - ray.origin.y;
	d.z = ray.destination.z - ray.origin.z;
	d.normalize();

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
		Vec3 dir;
		dir.x = ray.destination.x - ray.origin.x;
		dir.y = ray.destination.y - ray.origin.y;
		dir.z = ray.destination.z - ray.origin.z;
		dir.normalize();
		if(solutions[0] >= 0 && solutions[0] < solutions[1])
		{
			distance = solutions[0];
			Vec3 iteration(distance*dir.x, distance*dir.y, distance*dir.z);
			point = Vec3(ray.origin.x + iteration.x, ray.origin.y + iteration.y, ray.origin.z + iteration.z) ;
			normal = point - position;
			normal.normalize();
			return true;
		}
		else if(solutions[1] >= 0)
		{
			distance = solutions[1];
			Vec3 iteration(distance*dir.x, distance*dir.y, distance*dir.z);
			point = Vec3(ray.origin.x + iteration.x, ray.origin.y + iteration.y, ray.origin.z + iteration.z) ;
			normal = point - position;
			normal.normalize();
			return true;
		}
		else
		{
			return false;
		}
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
