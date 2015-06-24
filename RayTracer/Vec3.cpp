#include "Vec3.h"
#include "math.h"

Vec3::Vec3(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3::Vec3()
{
	x=0;
	y=0;
	z=0;
}

void Vec3::operator=(const Vec3& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}

float Vec3::lengthSquared() const
{
	return (x*x + y*y + z*z);
}

float Vec3::length() const
{
	return sqrt(x*x + y*y + z*z);
}

void Vec3::normalize()
{
	float len = length();
	x = x / len;
	y = y / len;
	z = z / len;
}

Vec3 Vec3::operator*(const float& f) const
{
	Vec3 hebele(x*f, y*f, z*f);
	return hebele;
}

Vec3 Vec3::operator*(const Vec3& rhs) const
{
	Vec3 value(x * rhs.x, y * rhs.y, z * rhs.z);
	return value;
}

Vec3 Vec3::operator+(const Vec3& rhs) const
{
	Vec3 hebele(x + rhs.x, y + rhs.y, z + rhs.z);
	return hebele;
}

Vec3 Vec3::operator-(const Vec3& rhs) const
{
	Vec3 hebele(x - rhs.x, y - rhs.y, z - rhs.z);
	return hebele;
}

Vec3 Vec3::cross(const Vec3& vect) const 
{ 
    float x,y,z; 
    x = ( this->y*(vect.z) - this->z*(vect.y) ); 
    y = ( this->z*(vect.x) - this->x*(vect.z) ); 
    z = ( this->x*(vect.y) - this->y*(vect.x) ); 
    Vec3 a(x,y,z); 
    return a; 
}

float Vec3::dot(const Vec3& rhs) const
{
	return (x * rhs.x + y*rhs.y + z*rhs.z);
}
	
