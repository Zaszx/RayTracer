#ifndef __RAY__H
#define __RAY__H

class Ray
{
public:

	Ray(Vec3 origin, Vec3 direction);

	Vec3 getOrigin() const;
	Vec3 getDirection() const;

private:

	Vec3 origin;
	Vec3 destination;
	Vec3 direction;
};



#endif //__RAY__H
