#include "CommonIncludes.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::readMaterials(string xmlPath)
{
	TiXmlDocument xmlDocument(xmlPath.c_str());
	bool success = xmlDocument.LoadFile();
	assert(success);
	
	TiXmlNode* materialsNode = xmlDocument.FirstChild("materials");
	assert(materialsNode);

	TiXmlNode* materialNode = materialsNode->FirstChild("material");
	while (materialNode)
	{
		Material* material = new Material();
		material->read(materialNode);
		materials.push_back(material);
		materialNode = materialNode->NextSibling();
	}
}

Material* ResourceManager::getMaterial(const String& name)
{
	for (int i = 0; i < materials.size(); i ++)
	{
		Material* curMaterial = materials[i];
		if (curMaterial->name.sameAs(name))
		{
			return curMaterial;
		}
	}
	return nullptr;
}

