#ifndef __LIGHT__H__
#define __LIGHT__H__

#include "Vec3.h"

class TiXmlNode;

class Light
{
public:
	Vec3 position;
	Vec3 intensity;

	void read(TiXmlNode* node);
};

#endif //__LIGHT__H__