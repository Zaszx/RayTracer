#ifndef __RESOURCE__MANAGER__H__
#define __RESOURCE__MANAGER__H__
#include <vector>
#include <string>
using namespace std;
class Material;
class TiXmlNode;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void readMaterials(string xmlPath);
	Material* getMaterial(const String& name);
private:

	vector<Material*> materials;

};

extern ResourceManager resourceManager;

#endif //__RESOURCE__MANAGER__H__