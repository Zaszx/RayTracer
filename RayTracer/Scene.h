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

	vector<Object*> objects;
	vector<Light*> lights;

	Vec3 backgroundColor;
	Vec3 ambientLightColor;

};

#endif //__SCENE__H__