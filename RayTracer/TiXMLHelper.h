#ifndef __TINY__XML__HELPER__H__
#define __TINY__XML__HELPER__H__

class TiXmlNode;
class Vec3;
class String;

class TiXMLHelper
{
public:

	static void GetAttribute(TiXmlNode* node, char* attributeName, float* value);
	static void GetAttribute(TiXmlNode* node, char* attributeName, int* value);
	static void GetAttribute(TiXmlNode* node, char* attributeName, Vec3* value);
	static void GetAttribute(TiXmlNode* node, char* attributeName, String* value);

};

#endif //__TINY__XML__HELPER__H__