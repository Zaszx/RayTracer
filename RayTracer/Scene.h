#ifndef __SCENE__H__
#define __SCENE__H__

#include "Vec3.h"

#include <string>
#include <vector>
#include "String.h"
#include "Camera.h"
using namespace std;

class Object;
class Light;

class Scene
{
public:
	Scene();
	~Scene();

	void read(string xmlPath);
	void render(const Camera& camera, const String& outputFilePath) const;

private:

	Vec3 traceRay(const Ray& ray, const Camera& camera, int depth = 0) const;

	Vec3 calculateLighting(Vec3 nearestPoint, const Ray& ray, Object* nearest, const Camera &camera) const;

	vector<Object*> objects;
	vector<Light*> lights;

	Vec3 backgroundColor;
	Vec3 ambientLightColor;
	int reflectionCount;

};

#endif //__SCENE__H__