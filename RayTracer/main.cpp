// Simple ray tracer by Ozan Celik.
// Using the code without any permission is allowed.

#include "CommonIncludes.h"

const string defaultSceneXMLPath = "Resources/scene.xml";
const string defaultMaterialXMLPath = "Resources/materials.xml";
const string defaultCameraXMLPath = "Resources/cameras.xml";

ResourceManager resourceManager;

void readCamerasAndRender(const Scene* scene)
{
	TiXmlDocument xmlDocument(defaultCameraXMLPath.c_str());
	bool success = xmlDocument.LoadFile();
	assert(success);

	TiXmlNode* camerasNode = xmlDocument.FirstChild("cameras");
	assert(camerasNode);

	int cameraIndex = 0;
	TiXmlNode* cameraNode = camerasNode->FirstChild("camera");
	while (cameraNode)
	{
		Camera camera;
		camera.read(cameraNode);
		char fileName[512];
		sprintf(fileName, "render_%d.ppm", cameraIndex);

		scene->render(camera, fileName);
		cameraNode = cameraNode->NextSibling();
	}
}

int main()
{
	resourceManager.readMaterials(defaultMaterialXMLPath);

	Scene* scene = new Scene();
	scene->read(defaultSceneXMLPath);
	readCamerasAndRender(scene);

	return 0;
}
