#include "structures.h"
#include "util.h"
#include "tracer.h"

#include <cmath>

bool getIntersection(prim_t &p, ray_t &r, double &t)
{
	point_t PoPc;
	double B, D, x1, x2;

	//algoritm depends on primitive type
	switch(p.type)
	{

	case SPHERE: //sfera

		PoPc = r.src - p.sphere.center;
		B = r.dst * PoPc; 
		D = B*B - PoPc*PoPc + p.sphere.r*p.sphere.r; 

		if(D<0)
			return 0;

		x1 = B + sqrt(D);
		x2 = B - sqrt(D);

		if(x1<x2)
		{
			t = x1;     
			return 1;
		}
		else
		{
			t = x2;
			return 1;
		}
		
		break;

	case POLIGON: //poligono

		break;

	case CONSTRUCTOR: //costrutto = cosa brutta e cattiva

		break;

	}

	return 0; // se arriva qui è un male!
}

color_t getColor(int x, int y, scene_t &scene)
{
	color_t c = { 0, 0, 0};
	prim_t p;
	material_t m;
	double t;

	double pixelSizeX = scene.screenSizeX/scene.screenResX;
	double pixelSizeY = scene.screenSizeY/scene.screenResY;

	ray_t ray = { {x * pixelSizeX, y * pixelSizeY, -1000.0f}, {0.0f, 0.0f, 1.0f}};
	norm(ray.dst);

	for(int i = 0; i < scene.primCount; i++)
		if(getIntersection(scene.prim[i], ray, t))
		{
			p = scene.prim[i];
			m = scene.material[p.mat];
			c = m.col;
		}
	
	return c;
}