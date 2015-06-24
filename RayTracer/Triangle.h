#ifndef __TRIANGLE__H
#define __TRIANGLE__H
#include "Vec3.h"
#include "Ray.h"
class Object;

class Triangle: public Object
{
public:
	Triangle(Vec3 coords1, Vec3 coords2, Vec3 coords3);
	Triangle();
	virtual bool intersects(const Ray& ray, float& distance, Vec3& point);
	Vec3 coords[3];
	float range;
protected:
	
	
};

#endif //__TRIANGLE__H
