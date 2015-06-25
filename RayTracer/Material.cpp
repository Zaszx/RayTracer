#include "CommonIncludes.h"
#include "Material.h"

Material::Material(int index)
{
	this->index = index;
}

void Material::read(TiXmlNode* node)
{
	TiXMLHelper::GetAttribute(node, "name", &name);
	TiXMLHelper::GetAttribute(node, "ambientColor", &ambient);
	TiXMLHelper::GetAttribute(node, "diffuseColor", &diffuse);
	TiXMLHelper::GetAttribute(node, "specularColor", &specular);
	TiXMLHelper::GetAttribute(node, "specularExponent", &specExp);
	TiXMLHelper::GetAttribute(node, "reflectionRate", &reflection);
	TiXMLHelper::GetAttribute(node, "refractionRate", &refractionIndex);
	TiXMLHelper::GetAttribute(node, "attenuation", &attenuation);
}

Vec3 Material::getReflectionRate(int depth)
{
	Vec3 result(1, 1, 1);
	for (int i = 0; i < depth; i++)
	{
		result = result * reflection;
	}
	return result;
}
