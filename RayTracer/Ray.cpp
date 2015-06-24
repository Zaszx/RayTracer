#include "CommonIncludes.h"
#include "Ray.h"

Ray::Ray(Vec3 origin, Vec3 direction)
{
	direction.normalize();
	this->origin = origin;
	this->direction = direction;
}

Vec3 Ray::getOrigin() const
{
	return origin;
}

Vec3 Ray::getDirection() const
{
	return direction;
}

