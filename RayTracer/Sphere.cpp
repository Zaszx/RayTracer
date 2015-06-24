#include "Object.h"
#include "Sphere.h"
#include "Vec3.h"
#include <iostream>
#include <math.h>
using namespace std;
Sphere::Sphere(Vec3 coords, float range):Object()
{
	this->coords = coords;
	this->range = range;
}


bool Sphere::intersects(const Ray& ray, float& distance, Vec3& point)
{
	Vec3 d,e,c;
	e = ray.origin;
	d.x = ray.destination.x - ray.origin.x;
	d.y = ray.destination.y - ray.origin.y;
	d.z = ray.destination.z - ray.origin.z;
	d.normalize();

	c = coords;
	float first = (d.dot(e-c)) * (d.dot(e-c));
	float second = (d.dot(d));
	float third = (e-c).dot(e-c) - (range*range);
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
			normal = point - coords;
			normal.normalize();
			return true;
		}
		else if(solutions[1] >= 0)
		{
			distance = solutions[1];
			Vec3 iteration(distance*dir.x, distance*dir.y, distance*dir.z);
			point = Vec3(ray.origin.x + iteration.x, ray.origin.y + iteration.y, ray.origin.z + iteration.z) ;
			normal = point - coords;
			normal.normalize();
			return true;
		}
		else
		{
			return false;
		}
	}
}
