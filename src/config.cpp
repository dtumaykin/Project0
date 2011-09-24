#include <iostream>
#include <stdlib.h>

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
