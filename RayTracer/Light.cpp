#include "CommonIncludes.h"
#include "Light.h"


void Light::read(TiXmlNode* node)
{
	TiXMLHelper::GetAttribute(node, "position", &position);
	TiXMLHelper::GetAttribute(node, "intensity", &intensity);
}
