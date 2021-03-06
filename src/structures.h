#ifndef P0_STRUCT_H
#define P0_STRUCT_H
// strutture dati e relativi operatori utilizzati da programma
#include <iostream>

// basic structures
struct vector_t {
	double x, y, z;
};

typedef vector_t point_t; // conceptually different, but have same implementation
typedef vector_t light_t;

struct ray_t {
	point_t src;
	vector_t dst;
};

struct color_t {
	double r, g, b;
};

//don't need this
/*struct pixel_t {
	double r, g, b;
	int i, j;
};*/

// primitives
enum PRIMITIVES
{
	SPHERE,
	POLYGON,
	PLANE,
	CONSTRUCTOR
};

struct sphere_t {
	point_t center;
	double r;
};

struct polygon_t {
	point_t ptA, ptB, ptC; // polygon is defined by 3 points
};

struct plane_t {
	vector_t n;
	double d;
};

struct prim_t {
	int type; //type from PRIMITIVES
	int mat; //material id

	//memory inefficent, but working solution
	sphere_t sphere;
	polygon_t polygon;
	plane_t plane;
};

//struct light_t {
//	double x, y, z;
//};

struct material_t {
	int mId;
	color_t col;
	double coefDiffuse;
	double coefReflect;
	double coefRefract;
	double refrIndex;
};

struct scene_t {

	int screenResX;
	int screenResY;
	double screenSizeX;
	double screenSizeY;

	int maxAA; // antialias

	double maxT; // max render distance

	point_t cam; //camera position, now unused

	
	//scene content
	int primCount, lightCount, matCount;
	prim_t *prim;
	light_t *light;
	material_t *material;

};

inline vector_t& operator/ (vector_t &v, double d)
{
	v.x /= d;
	v.y /= d;
	v.z /= d;
	return v;
}

//used for debug print
inline std::ostream& operator<< (std::ostream &out, vector_t &vect)
{
	out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
	return out;
}

inline std::ostream& operator<< (std::ostream &out, sphere_t &s)
{
	out << s.center.x << " " << s.center.y << " " << s.center.z << "   "<< s.r;
	return out;
}

#endif
