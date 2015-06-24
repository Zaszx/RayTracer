#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "Object.h"
#include "Vec3.h"
#include "Sphere.h"
#include <vector>
#include <algorithm>
#include <string>
#include <string.h>
#include "Camera.h"
#include "Material.h"
#include "Triangle.h"
#include "Ray.h"
#include <math.h>
#include "TinyXML/tinyxml.h"
using namespace std;

const string defaultSceneXMLPath = "Resources/scene.xml";
const string defaultMaterialXMLPath = "Resources/materials.xml";
const string defaultCameraXMLPath = "Resources/cameras.xml";

class Light
{
	public:
	Vec3 position;
	Vec3 intensity;
};

string sceneFileName;

int rayReflectCount;
vector<Object*> objects;
vector<Material*> materials;
vector<Camera*> cameras;
vector<Light*> lights;
int imageWidth, imageHeight;
float near,far;
Vec3 bgColor;
Vec3 ambientLight;

string outputFileName;
FILE *in,*out;

Vec3 screen[5000][5000];

Material* getMaterial(int index)
{
	for(int i=0;i<materials.size();i++)
	{
		if(materials[i]->index == index) return materials[i];
	}
	return NULL;
}

void readScene()
{
	char temp[256];
	Sphere* sphere;
	Triangle* triangle;
	Material* material;
	Light* light;
	TiXmlAttribute s;
	string whatNext;
	fscanf(in, " %d", &rayReflectCount);
	
	while(fscanf(in, " %s ",temp) != EOF)
	{
		if(!strcmp(temp,"#material"))
		{
			material = new Material();
			fscanf(in, " %d",&material->index);
			fscanf(in, " %f %f %f", &material->ambient.x, &material->ambient.y, &material->ambient.z);
			fscanf(in, " %f %f %f", &material->diffuse.x, &material->diffuse.y, &material->diffuse.z);
			fscanf(in, " %f %f %f", &material->specular.x, &material->specular.y, &material->specular.z);
			fscanf(in, " %f",&material->specExp);
			fscanf(in, " %f %f %f", &material->reflection.x, &material->reflection.y, &material->reflection.z);
			fscanf(in, " %f",&material->refractionIndex);
			fscanf(in, " %f %f %f", &material->attenuation.x, &material->attenuation.y, &material->attenuation.z);
			materials.push_back(material);
			continue;
		}
		else if(!strcmp(temp, "#sphere"))
		{
			sphere = new Sphere();
			fscanf(in, " %f %f %f", &sphere->coords.x, &sphere->coords.y, &sphere->coords.z);
			fscanf(in, " %f %d", &sphere->range, &sphere->materialIndex);
			objects.push_back(sphere);
			continue;
		}
		else if(!strcmp(temp, "#ambient"))
		{
			fscanf(in, " %s",temp);
			fscanf(in, " %f %f %f", &ambientLight.x, &ambientLight.y, &ambientLight.z);
			continue;
		}
		else if(!strcmp(temp, "#background"))
		{
			fscanf(in, " %s",temp);
			fscanf(in, " %f %f %f", &bgColor.x, &bgColor.y, &bgColor.z);
			continue;		
		}
		else if(!strcmp(temp, "#point"))
		{
			light = new Light();
			fscanf(in, "%s ",temp);
			fscanf(in, " %f %f %f", &light->position.x, &light->position.y, &light->position.z);
			fscanf(in, " %f %f %f", &light->intensity.x, &light->intensity.y, &light->intensity.z);
			lights.push_back(light);
			continue;
		}
		else if(!strcmp(temp, "#triangle"))
		{
			triangle = new Triangle();
			fscanf(in, " %f %f %f", &triangle->coords[0].x, &triangle->coords[0].y, &triangle->coords[0].z);
			fscanf(in, " %f %f %f", &triangle->coords[1].x, &triangle->coords[1].y, &triangle->coords[1].z);
			fscanf(in, " %f %f %f", &triangle->coords[2].x, &triangle->coords[2].y, &triangle->coords[2].z);
			fscanf(in, " %d",&triangle->materialIndex);
			objects.push_back(triangle);
			continue;
		}
		else
		{
			printf("I read %s, probably something wrong.\n",temp);
		}
	}
}

void readCamera()
{
	int i = 0;
	Camera* camera;
	fscanf(in, " %d %d %f %f",&imageWidth, &imageHeight, &near, &far);
	while(1)
	{
		camera = new Camera();
		i++;
		if(fscanf(in, " %f %f %f",&camera->pos.x, &camera->pos.y, &camera->pos.z) == EOF)
		{
			delete camera;
			return;
		}
		printf("Reading camera info for camera # %d",i);
		fscanf(in, " %f %f %f",&camera->gaze.x, &camera->gaze.y, &camera->gaze.z);
		fscanf(in, " %f %f %f",&camera->up.x, &camera->up.y, &camera->up.z);
		fscanf(in, " %f %f %f %f %f",&camera->left, &camera->right, &camera->bottom, &camera->top, &camera->distance);
		camera->up.normalize();
		camera->gaze.normalize();
		cameras.push_back(camera);
	}
}

int main()
{
	char temp[200];
	printf("Name of the scene file?\n");
	scanf(" %s",temp);
	sceneFileName = temp;
	printf("\nPreCalculating...\n");
	
	in = fopen(temp,"r");
	readScene();
	fclose(in);
	
	printf("PreCalculate complete!\nName of the camera file?\n");
	scanf(" %s",temp);
	
	in = fopen(temp,"r");
	readCamera();
	fclose(in);
	
	for(int c=0;c<cameras.size();c++)
	{
		Camera* curCamera = cameras[c];
		outputFileName = sceneFileName.substr(0, sceneFileName.size() - 4);
		outputFileName.append("_");
		char* hebele = new char[4];
		hebele[0] = (char) ((c + 1)%10 + '0');
		hebele[1] = (c+1)/10 == 0 ? 0 : (c+1)/10;
		hebele[2] = 0;
		outputFileName.append(hebele);
		outputFileName.append(".ppm");
		
		for(int i=0;i<imageWidth;i++)
		{
			for(int j=0;j<imageHeight;j++)
			{
				Ray* ray = new Ray();
				ray->origin = curCamera->pos;
				Vec3 p = curCamera->pos + (curCamera->gaze * curCamera->distance);
				float ununyataydakimiktari = (curCamera->left + ((curCamera->right - curCamera->left) / imageWidth) * (i + 0.5));
				Vec3 u = curCamera->gaze.cross(curCamera->up);
				u.normalize();
				float vnindikeydekimiktari = (curCamera->bottom + ((curCamera->top - curCamera->bottom) / imageHeight) * (j + 0.5));
				ray->destination = p + (u * ununyataydakimiktari) + (curCamera->up * vnindikeydekimiktari);
				float minDist = 10000000;
				Object* nearest = NULL;
				Vec3 nearestPoint;
				for(int o = 0; o < objects.size(); o++)
				{
					float dist;
					Vec3 point;
					if(objects[o]->intersects(*ray,dist,point))
					{
						if(dist < minDist)
						{
							minDist = dist;
							nearest = objects[o];
							nearestPoint = point;
						} 
					}
				}
				if(nearest)
				{
					Ray* lightRay;
					for(int l=0;l<lights.size();l++)
					{
						lightRay = new Ray();
						lightRay->origin = nearestPoint;
						lightRay->destination = lights[l]->position;
						Vec3 d;
						d.x = lightRay->destination.x - lightRay->origin.x;
						d.y = lightRay->destination.y - lightRay->origin.y;
						d.z = lightRay->destination.z - lightRay->origin.z;
						d.normalize();
						nearest->normal.normalize();
						float hebele = d.dot(nearest->normal);
						hebele = hebele < 0 ? 0 : hebele;
						
						float lol = hebele * lights[l]->intensity.x;
						screen[i][j].x += getMaterial(nearest->materialIndex)->diffuse.x * lol;
						
						lol = hebele * lights[l]->intensity.y;
						screen[i][j].y += getMaterial(nearest->materialIndex)->diffuse.y * lol;
						
						lol = hebele * lights[l]->intensity.x;
						screen[i][j].z += getMaterial(nearest->materialIndex)->diffuse.z * lol;
						
						Vec3 pointToCamera = nearestPoint - curCamera->pos;
						pointToCamera.normalize();
						Vec3 h = pointToCamera + d;
						h.normalize();
						float ndoth = nearest->normal.dot(h);
						if(ndoth < 0) ndoth = 0;
						pow(ndoth, getMaterial(nearest->materialIndex)->specExp);
						
						lol = getMaterial(nearest->materialIndex)->specular.x * lights[l]->intensity.x * ndoth;
						screen[i][j].x +=lol;
						
						lol = getMaterial(nearest->materialIndex)->specular.y * lights[l]->intensity.y * ndoth;
						screen[i][j].y +=lol;						
						
						lol = getMaterial(nearest->materialIndex)->specular.z * lights[l]->intensity.z * ndoth;
						screen[i][j].z +=lol;
												
						delete lightRay;
					}
					

					screen[i][j].x += getMaterial(nearest->materialIndex)->ambient.x * ambientLight.x;
					screen[i][j].y += getMaterial(nearest->materialIndex)->ambient.y * ambientLight.y;
					screen[i][j].z += getMaterial(nearest->materialIndex)->ambient.z * ambientLight.z;
				}
				else
				{
					screen[i][j] = bgColor;
				}
			}
		}

		int totalImageSize = imageWidth * imageHeight * 3;
		unsigned char* toPPM = new unsigned char[totalImageSize];
		for(int i = 0; i < imageHeight; i++)
		{
			for(int j = 0; j < imageWidth; j++)
			{
				toPPM[(imageWidth-j-1)*imageWidth*3 + i*3] = screen[i][j].x > 255 ? 255 : screen[i][j].x;
				toPPM[(imageWidth-j-1)*imageWidth*3 + i*3 + 1] = screen[i][j].y > 255 ? 255 : screen[i][j].y;
				toPPM[(imageWidth-j-1)*imageWidth*3 + i*3 + 2] = screen[i][j].z > 255 ? 255 : screen[i][j].z;
			}
		}
		out = fopen(outputFileName.c_str(), "wb");
		fprintf(out, "P6 %d %d %d\n", imageWidth, imageHeight, 255);
		fwrite(toPPM, totalImageSize, 1, out);
		fclose(out);
	}
	
	return 0;
}
