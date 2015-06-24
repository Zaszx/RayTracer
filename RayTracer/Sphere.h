#ifndef __SPHERE__H
#define __SPHERE__H
#include "Vec3.h"
#include "Ray.h"
class Object;
class Vec3;
class Ray;

class Sphere: public Object
{
	public:
	Sphere(Vec3 coords, float range);
	Sphere(){}
	virtual bool intersects(const Ray& ray, float& distance, Vec3& point);
	Vec3 coords;
	float range;
	protected:
	
	
};
#endif //__SPHERE__H
