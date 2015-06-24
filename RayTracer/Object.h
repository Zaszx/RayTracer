#ifndef __OBJECT__H
#define __OBJECT__H
#include "Vec3.h"
#include "String.h"
class Ray;
class Material;

class Object
{
	public:
	
	int materialIndex;
	String materialName;
	Material* material;

	Object();
	virtual bool intersects(const Ray& ray, float& distance, Vec3& point) = 0;
	Vec3 normal;
	protected:
	
	
};
#endif //__OBJECT__H
