#ifndef __OBJECT__H
#define __OBJECT__H
#include "Vec3.h"
class Ray;

class Object
{
	public:
	
	int materialIndex;
	Object();
	virtual bool intersects(const Ray& ray, float& distance, Vec3& point) = 0;
	Vec3 normal;
	protected:
	
	
};
#endif //__OBJECT__H
