#include "CommonIncludes.h"
#include "Scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::read(string xmlPath)
{
	TiXmlDocument xmlDocument(xmlPath.c_str());
	bool success = xmlDocument.LoadFile();
	assert(success);

	TiXmlNode* sceneNode = xmlDocument.FirstChild("scene");
	assert(sceneNode);

	// Read objects
	TiXmlNode* objectsNode = sceneNode->FirstChild("objects");
	if (objectsNode)
	{
		TiXmlNode* trianglesNode = objectsNode->FirstChild("triangles");
		if (trianglesNode)
		{
			TiXmlNode* triangleNode = trianglesNode->FirstChild("triangle");
			while (triangleNode)
			{
				Triangle* triangle = new Triangle();
				triangle->read(triangleNode);
				objects.push_back(triangle);
				triangleNode = triangleNode->NextSibling();
			}
		}

		TiXmlNode* spheresNode = objectsNode->FirstChild("spheres");
		if (spheresNode)
		{
			TiXmlNode* sphereNode = trianglesNode->FirstChild("triangle");
			while (sphereNode)
			{
				Sphere* sphere = new Sphere();
				sphere->read(sphereNode);
				objects.push_back(sphere);
				sphereNode = sphereNode->NextSibling();
			}
		}
	}

	// Read Lights
	TiXmlNode* lightsNode = sceneNode->FirstChild("lights");
	if (lightsNode)
	{
		TiXmlNode* lightNode = lightsNode->FirstChild("light");
		while (lightNode)
		{
			Light* light = new Light();
			light->read(lightNode);
			lights.push_back(light);
			lightNode = lightNode->NextSibling();
		}
	}

	// Read Attributes
	TiXMLHelper::GetAttribute(sceneNode, "backgroundColor", &backgroundColor);
	TiXMLHelper::GetAttribute(sceneNode, "ambientLight", &ambientLightColor);
}
