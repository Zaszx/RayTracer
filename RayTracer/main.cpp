// Simple ray tracer by Ozan Celik.
// Using the code without any permission is allowed.

#include "CommonIncludes.h"

const string defaultSceneFolderPath = "Resources/Scene2/";

string sceneFolderPath;

ResourceManager resourceManager;

void readCamerasAndRender(const Scene* scene)
{
	string cameraXMLPath = sceneFolderPath + "cameras.xml";
	TiXmlDocument xmlDocument(cameraXMLPath.c_str());
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
		sprintf(fileName, "%srender_%d.ppm", sceneFolderPath.c_str(), cameraIndex);

		scene->render(camera, fileName);
		cameraNode = cameraNode->NextSibling();
		cameraIndex++;
	}
}

int main(int argc, char** argv)
{
	sceneFolderPath = defaultSceneFolderPath;
	if (argc > 1)
	{
		sceneFolderPath = argv[1];
	}
	string materialXMLPath = sceneFolderPath + "materials.xml";
	string sceneXMLPath = sceneFolderPath + "scene.xml";
	resourceManager.readMaterials(materialXMLPath);

	Scene* scene = new Scene();
	scene->read(sceneXMLPath);
	readCamerasAndRender(scene);

	return 0;
}
