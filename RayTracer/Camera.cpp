#include "CommonIncludes.h"
#include "Camera.h"


void Camera::read(TiXmlNode* node)
{
	TiXMLHelper::GetAttribute(node, "position", &pos);
	TiXMLHelper::GetAttribute(node, "forward", &gaze);
	TiXMLHelper::GetAttribute(node, "up", &up);
	TiXMLHelper::GetAttribute(node, "left", &left);
	TiXMLHelper::GetAttribute(node, "right", &right);
	TiXMLHelper::GetAttribute(node, "bottom", &bottom);
	TiXMLHelper::GetAttribute(node, "top", &top);
	TiXMLHelper::GetAttribute(node, "distance", &distance);
	TiXMLHelper::GetAttribute(node, "imageWidth", &imageWidth);
	TiXMLHelper::GetAttribute(node, "imageHeight", &imageHeight);
}

