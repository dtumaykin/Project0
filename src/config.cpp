#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>

#include "structures.h"
#include "config.h"


scene_t config()
{
	FILE *src;
	scene_t temp;
	prim_t *vet;
	int ctr=0,i=0,car;
	char str[20];
	src=fopen("config.cfg","rt");
	if(src)
	{
		temp.primCount=0;
		while(fscanf(src,"%s",str)!=EOF)
		{
			if(strcmp(str,"sphere")==0 || strcmp(str,"poligon")==0) ctr++;
		}
		//cout << ctr;
		//getchar();
		rewind(src);
		vet=(prim_t *)malloc(ctr*sizeof(struct prim_t));
		while(fscanf(src,"%s",str)!=EOF)
		{
			if(strcmp(str,"sphere")==0)
			{
				fscanf(src,"%d",&car);
				vet[temp.primCount].sphere.center.x=car;
				fscanf(src,"%d",&car);
				vet[temp.primCount].sphere.center.y=car;
				fscanf(src,"%d",&car);
				vet[temp.primCount].sphere.center.z=car;
				fscanf(src,"%d",&car);
				vet[temp.primCount].sphere.r=car;
				//cout << vet[temp.primCount].sphere << endl;
				temp.primCount++;
			}
		}
		fclose(src);
		temp.prim=vet;
	}  
	return temp;      
}

int loadConfig(char * path, scene_t &scene)
{
	std::ifstream ifs(path);

	if(ifs.bad()) return 0;

	//it's cpp implementation, i'm sorry for following code
	std::vector<prim_t> tempPrim;
	std::vector<light_t> tempLight;
	std::vector<material_t> tempMat;
	
	while(!ifs.eof())
	{
		switch(getOpcode(ifs))
		{
		case RESO:
			ifs >> scene.screenResX;
			ifs >> scene.screenResY;
			break;
		case SIZE:
			ifs >> scene.screenSizeX;
			ifs >> scene.screemSizeY;
			break;
		case SPHR:
			prim_t s;
			s.type = SPHERE;
			ifs >> s.sphere.center.x;
			ifs >> s.sphere.center.y;
			ifs >> s.sphere.center.z;
			ifs >> s.sphere.r;
			ifs >> s.mat;
			tempPrim.push_back(s);
			break;
		case POLI:
			prim_t p;
			p.type = POLIGON;
			ifs >> p.poligon.ptA.x >> p.poligon.ptA.y >> p.poligon.ptA.z;
			ifs >> p.poligon.ptB.x >> p.poligon.ptB.y >> p.poligon.ptB.z;
			ifs >> p.poligon.ptC.x >> p.poligon.ptC.y >> p.poligon.ptC.z;
			ifs >> p.mat;
			tempPrim.push_back(p);
			break;
		case LGHT:
			light_t l;
			ifs >> l.x;
			ifs >> l.y;
			ifs >> l.z;
			tempLight.push_back(l);
			break;
		case MATR:
			material_t m;
			ifs >> m.mId;
			ifs >> m.col.r >> m.col.b >> m.col.g;
			ifs >> m.coefDiffuse;
			ifs >> m.coefReflect;
			ifs >> m.coefRefract;
			tempMat.push_back(m);
			break;
		case UNKN:
			return 0;
			break;
		}
	}

	// now we need to push elements into scene
	scene.primCount = tempPrim.size();
	scene.lightCount = tempLight.size();
	scene.matCount = tempMat.size();

	// allocate memory for scene
	scene.prim = (prim_t *) malloc(sizeof(prim_t) * scene.primCount);
	scene.light = (light_t *) malloc(sizeof(light_t) * scene.lightCount);
	scene.material = (material_t *) malloc(sizeof(material_t) * scene.matCount);

	// copy from temp
	for(int i = 0; i < scene.primCount; i++)
		scene.prim[i] = tempPrim[i];

	for(int i = 0; i < scene.lightCount; i++)
		scene.light[i] = tempLight[i];

	for(int i = 0; i < scene.matCount; i++)
		scene.material[i] = tempMat[i];

	return 1;
}

int getOpcode(std::ifstream &ifs)
{
	std::string opcode;

	ifs >> opcode;

	//testing opcodes
	if(opcode == "reso") return RESO;
	if(opcode == "size") return SIZE;
	if(opcode == "sphr") return SPHR;
	if(opcode == "poli") return POLI;
	if(opcode == "lght") return LGHT;
	if(opcode == "matr") return MATR;

	return UNKN;
}
