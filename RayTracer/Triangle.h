#ifndef __TRIANGLE__H
#define __TRIANGLE__H
#include "Vec3.h"
#include "Ray.h"
#include "Object.h"

class TiXmlNode;

class Triangle: public Object
{
public:
	Triangle();
	virtual bool intersects(const Ray& ray, float& distance, Vec3& point);
	void read(TiXmlNode* node);
	Vec3 coords[3];

	void recomputeNormal();
protected:
	
};

#endif //__TRIANGLE__H
