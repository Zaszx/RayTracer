#include "CommonIncludes.h"
#include "Triangle.h"


Triangle::Triangle()
{
}

bool Triangle::intersects(const Ray& ray, float& distance, Vec3& point)
{
	float a,b,c,d,e,f,g,h,i,j,k,l;
	Vec3 dir;
	dir.x = ray.destination.x - ray.origin.x;
	dir.y = ray.destination.y - ray.origin.y;
	dir.z = ray.destination.z - ray.origin.z;
	dir.normalize();
	a = coords[0].x - coords[1].x;
	b = coords[0].y - coords[1].y;
	c = coords[0].z - coords[1].z;
	d = coords[0].x - coords[2].x;
	e = coords[0].y - coords[2].y;
	f = coords[0].z - coords[2].z;
	g = dir.x;
	h = dir.y;
	i = dir.z;
	j = coords[0].x - ray.origin.x;
	k = coords[0].y - ray.origin.y;
	l = coords[0].z - ray.origin.z;

	float t, beta, gama, m;

	m = a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h-e*g);
	beta = ( j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g) ) / m;
	gama = ( i*(a*k-j*b) + h*(j*c-a*l) + g*(b*l-k*c) ) / m;
	t = 0- (f*(a*k-j*b) + e*(j*c-a*l) + d*(b*l-k*c)) / m;
	distance = t;
	Vec3 iteration(t*dir.x, t*dir.y, t*dir.z);
	point = Vec3(ray.origin.x + iteration.x, ray.origin.y + iteration.y, ray.origin.z + iteration.z);
	if(gama<=0 || gama>=1)
		return false;
	if(beta<=0 || beta>=1-gama)
		return false;
	Vec3 edge1 = coords[1] - coords[0];
	Vec3 edge2 = coords[2] - coords[1];
	normal = edge1.cross(edge2);
	normal.normalize();
	return true;
}

void Triangle::read(TiXmlNode* node)
{
	TiXMLHelper::GetAttribute(node, "materialName", &materialName);
	TiXmlNode* vertexInfosNode = node->FirstChild("vertexInfos");
	assert(vertexInfosNode);

	TiXmlNode* vertexInfoNode = vertexInfosNode->FirstChild("vertexInfo");
	int vertexIndex = 0;
	while (vertexInfoNode)
	{
		TiXMLHelper::GetAttribute(vertexInfoNode, "position", &coords[vertexIndex]);

		vertexIndex++;
		vertexInfoNode = vertexInfoNode->NextSibling();
	}
	assert(vertexIndex == 3);

	recomputeNormal();
}

void Triangle::recomputeNormal()
{
	Vec3 edge1 = coords[1] - coords[0];
	Vec3 edge2 = coords[2] - coords[1];
	normal = edge1.cross(edge2);
	normal.normalize();
}
