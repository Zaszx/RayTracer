#ifndef __SPHERE__H
#define __SPHERE__H
#include "Vec3.h"
#include "Ray.h"
class Object;
class Vec3;
class Ray;
class TiXmlNode;

class Sphere: public Object
{
public:
	Sphere();
	virtual bool intersects(const Ray& ray, float* distance = nullptr, Vec3* point = nullptr) override;
	void read(TiXmlNode* node);
	
	Vec3 position;
	float radius;

protected:
	
	
};
#endif //__SPHERE__H
