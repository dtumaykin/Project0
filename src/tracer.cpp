#include "structures.h"
#include "util.h"
#include "tracer.h"

#include <cmath>
#include <math.h>

bool getIntersection(prim_t &p, ray_t &r, double &t)
{
	//sphere intersection
	point_t PoPc;
	double B, D, x1, x2;
	bool rval = false;

	//plane intersection
	double pN, pD, pT;

	//polygon intersection
	vector_t u, v, n, w0, w;
	prim_t pl;
	double plT, tS, tT, tD;
	point_t intrPoint;

	//algoritm depends on primitive type
	switch(p.type)
	{

	case SPHERE: //sfera

		PoPc = r.src - p.sphere.center;
		B = r.dst * PoPc; 
		D = B*B - PoPc*PoPc + p.sphere.r*p.sphere.r; 

		if(D < 0.0f) return 0;

		x1 = -B - sqrt(D);
		x2 = -B + sqrt(D);

		if(x1 > 0.1f && x1 < t)
		{
			t = x1;
			rval = true;
		}
		if(x2 > 0.1f && x2 < t)
		{
			t = x2;
			rval = true;
		}
		return rval;
		/*if(x1 < x2)
		{
			if(t > x1) 
			{
				t = x1;     
				return 1;
			}
		}
		else
		{
			if(t > x1)
			{
				t = x2;
				return 1;
			}
		}*/
		
		break;

	case POLYGON: //poligono

		//triangle vectors
		u = p.polygon.ptB-p.polygon.ptA;
		v = p.polygon.ptC-p.polygon.ptA;

		//plane normal
		n=cross(u,v);
		if(!length(n)) return false;
		norm(n); // normalize normal
		n = correctDir(n, r.dst); // normal pointing in right directions

		//plane intersection - using getIntersection()
		plT = 6000.0f;
		pl.type = PLANE;
		pl.plane.n = n;
		pl.plane.d = n * p.polygon.ptA * -1.0f;
		if(!getIntersection(pl, r, plT)) return false;


		/* old intersection
		w0 = r.src - p.polygon.ptA;
		norm(w0);
		if(n * r.dst == 0.0f) return false; // ray parallel to plane
		plT = (n * w0 * -1.0f)/(n * r.dst); // distance to intersection
		if(plT < 0.0 || plT > t) return false;
		*/

		intrPoint = r.src + r.dst * plT; // intersection point
		w = intrPoint - p.polygon.ptA;
		//norm(w); incorrect
		tD = (u*v)*(u*v)-(u*u)*(v*v);

		tS=((u*v)*(w*v)-(v*v)*(w*u))/tD;
		if(tS < 0.0f || tS > 1.0f) return false;
		tT=((u*v)*(w*u)-(u*u)*(w*v))/tD;
		if(tT < 0.0f || (tS+tT) > 1.0f) return false;

		t = plT; // new closest intersection
		return true;

		break;

	case PLANE:

		pN = -1.0f *(p.plane.d + p.plane.n * r.src); // d + N * Po
		pD = r.dst * p.plane.n; // vD * N

		if(!pD) return 0; // ray and norm parallel

		pT = pN / pD;

		if(pT <= 0.0f || pT > t) return 0; // if behind or there's another intersection before
		
		t = pT - 0.0001f; // fix for precision problems
		return true;

		break;

	case CONSTRUCTOR: //costrutto = cosa brutta e cattiva

		break;

	}

	return 0; // se arriva qui è un male!
}

color_t getColor(int x, int y, scene_t &scene)
{
	color_t cAcc = { 0.0f, 0.0f, 0.0f};

	double pixelSizeX = scene.screenSizeX/scene.screenResX;
	double pixelSizeY = scene.screenSizeY/scene.screenResY;

	double AAShiftX = pixelSizeX/scene.maxAA;
	double AAShiftY = pixelSizeY/scene.maxAA;

	for(double i = pixelSizeX * x; i < pixelSizeX * (x + 1); i += AAShiftX)
		for(double j = pixelSizeY * y; j < pixelSizeY * (y + 1); j += AAShiftY)
		{
			ray_t ray = { {i, j, -1000.0f}, {0.0f, 0.0f, 1.0f}};
			norm(ray.dst);

			cAcc += trace(ray, scene, 0);
		}

	cAcc /= scene.maxAA*scene.maxAA;

	return cAcc;
}

color_t trace(ray_t &ray, scene_t &scene, int depth)
{
	color_t background = { 0.15f, 0.15f, 0.15f};
	color_t c = { 0.0f, 0.0f, 0.0f };
	prim_t *p = NULL;
	material_t *m = NULL;
	double t = scene.maxT;
	double temp;

	if(depth > 3) return c; //if we reach max depth of recursion

	//get nearest intersection
	for(int i = 0; i < scene.primCount; i++)
		if(getIntersection(scene.prim[i], ray, t))
			p = &scene.prim[i];
			
	if(!p) return background; // no intersections

	//find material for primitive
	for(int i = 0; i < scene.matCount; i++)
		if(scene.material[i].mId == p->mat)
			m = &scene.material[i];

	if(!m) return background; // non existant material

	
	//calculating shadows/lighting
	vector_t intrPoint = ray.src + ray.dst * t;
	ray_t lightRay;
	bool inShadow;

	lightRay.src = intrPoint;
	
	vector_t normal = getNormal(*p, intrPoint); // normalized normal in intersection point

	//temp = -1.0f;
	//if(ray.dst * normal > 0.0f)
		//normal = normal * temp;
	normal = correctDir(normal, ray.dst);

	for(int i = 0; i < scene.lightCount; i++)
	{
		inShadow = false;
		lightRay.dst = scene.light[i] - intrPoint;
		
		if(normal * lightRay.dst <= 0.0f) continue; // pointing in opposite directions
		temp = sqrt(lightRay.dst*lightRay.dst);
		
		norm(lightRay.dst);

		for(int j = 0; j < scene.primCount; j++)
			if(getIntersection(scene.prim[j], lightRay, temp))
			{
				inShadow = true;
				break;
			}

		if(!inShadow)
		{
			//lambert
			double lambert = (lightRay.dst * normal);
			//c.r += m->col.r * m->coefDiffuse;// * lambert;
			//c.g += m->col.g * m->coefDiffuse;// * lambert;
			//c.b += m->col.b * m->coefDiffuse;// * lambert;
			c += m->col * m->coefDiffuse * lambert;

			//blinn
			vector_t blinnDst = lightRay.dst - ray.dst;
			norm(blinnDst);

			double blinn = blinnDst * normal;
			blinn = m->coefReflect * pow(blinn, (double)100.0f);

			c += m->col * blinn;
		}
	}

	//calculating reflections
	ray_t reflRay;
	double refl = ray.dst * normal * 2.0f;

	reflRay.src = intrPoint;
	reflRay.dst = ray.dst - normal * refl;

	c += trace(reflRay, scene, depth + 1) * m->coefReflect;

	return c;
}

vector_t getNormal(prim_t &p, point_t &intrPoint)
{
	vector_t normal, u, v;
	switch(p.type)
	{
	case SPHERE:
		normal = intrPoint - p.sphere.center;
		norm(normal);
		break;
	case POLYGON:
		//triangle vectors
		u=p.polygon.ptB-p.polygon.ptA;
		v=p.polygon.ptC-p.polygon.ptA;

		//plane normal
		normal=cross(u,v);
		norm(normal); // normalize normal
		break;
	case PLANE:
		normal = p.plane.n; // already normalized
		// particularity of our implementation
		//normal.x = - normal.x; 
		//normal.y = - normal.y;
		//normal.z = - normal.z;
		break;
	case CONSTRUCTOR:
		break;
	}
	return normal;
}

vector_t correctDir(vector_t &normal, vector_t &dir)
{
	double temp = -1.0f;
	if(normal * dir > 0.0f)
		normal = normal * temp;

	return normal;
}