#ifndef __VEC3__H
#define __VEC3__H


class Vec3
{
	public:
	Vec3(float x, float y, float z);
	Vec3();
	void operator=(const Vec3& rhs);
	Vec3 operator*(const float& f) const;
	Vec3 operator*(const Vec3& rhs) const;
	Vec3 operator+(const Vec3& rhs) const;
	Vec3 operator-(const Vec3& rhs) const;
	Vec3 cross(const Vec3& vect) const;
	float dot(const Vec3& rhs) const;
	void normalize();
	float length() const;
	float lengthSquared() const;
	float x,y,z;
	private:
};

#endif //__VEC3__H
