#ifndef __CAMERA__H
#define __CAMERA__H
#include "Vec3.h"
class Camera
{
public:
	Vec3 pos;
	Vec3 gaze;
	Vec3 up;
	float left,right,bottom,top, distance;

	int imageWidth;
	int imageHeight;
	
	void read(TiXmlNode* node);

	private:
	
};



#endif //__CAMERA__H
