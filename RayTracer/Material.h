#ifndef __MATERIAL__H
#define __MATERIAL__H
#include "Vec3.h"


class Material
{
public:
	Material(int index);
	Material(){}
	int index;
	Vec3 ambient;
	Vec3 diffuse;
	Vec3 specular;
	float specExp;
	float refractionIndex;
	Vec3 attenuation;
	Vec3 reflection;
};




#endif //__MATERIAL__H
