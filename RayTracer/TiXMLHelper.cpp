#include "CommonIncludes.h"
#include "TiXMLHelper.h"



void TiXMLHelper::GetAttribute(TiXmlNode* node, char* attributeName, float* value)
{
	*value = atof(node->ToElement()->Attribute(attributeName));
}

void TiXMLHelper::GetAttribute(TiXmlNode* node, char* attributeName, int* value)
{
	*value = atoi(node->ToElement()->Attribute(attributeName));
}

void TiXMLHelper::GetAttribute(TiXmlNode* node, char* attributeName, Vec3* value)
{
	String valueString(node->ToElement()->Attribute(attributeName));
	char buffer[256];
	int bufferIndex = 0;

	float values[3];
	int valueIndex = 0;

	for (int i = 0; i < valueString.length(); i++)
	{
		if (valueString[i] == ' ')
		{
			buffer[bufferIndex] = 0;
			values[valueIndex++] = atof(buffer);
			bufferIndex = 0;
		}
		else
		{
			buffer[bufferIndex] = valueString[i];
		}
	}
	buffer[bufferIndex] = 0;
	values[valueIndex] = atof(buffer);

	value->x = values[0];
	value->y = values[1];
	value->z = values[2];
}

void TiXMLHelper::GetAttribute(TiXmlNode* node, char* attributeName, String* value)
{
	*value = node->ToElement()->Attribute(attributeName);
}
