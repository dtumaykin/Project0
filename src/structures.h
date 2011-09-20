// strutture dati e relativi operatori utilizzati da programma

// basic structures
struct point_t {
	double x, y, z;
};

struct vector_t {
	double x, y, z;
};

struct ray_t {
	point_t src;
	vector_t dst;
};

struct color_t {
	double r, g, b;
};

struct pixel_t {
	double r, g, b;
	int i, j;
};

// primitives
enum PRIMITIVES
{
	SPHERE,
	POLIGON,
	CONSTRUCTOR
};

struct sphere_t {
	point_t center;
	double r;
};

struct poligon_t {
	point_t ptA, ptB, ptC; // poligon is defined by 3 points
};

struct prim_t {
	int type; //type from PRIMITIVES
	int mat; //material id

	union prim { //union with primitives
		sphere_t sphere;
		poligon_t poligon;
	};
};

struct light_t {
	point_t x, y, z;
};

struct material_t {
	color_t col;
	double coefDiffuse;
	double coefReflect;
	double coefRefract;
};



struct scene_t {

	int screenResX;
	int screenResY;
	double screenSizeX;
	double screemSizeY;

	//point_t cam; //camera position, now unused

	
	//scene content
	int primCount, lightCount, matCount;
	prim_t *prim;
	light_t *light;
	material_t *material;

};

vector_t& operator/ (vector_t &v, double d)
{
	v.x /= d;
	v.y /= d;
	v.z /= d;
	return v;
}

//used for debug print
std::ostream& operator<< (std::ostream &out, vector_t &vect)
{
	out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
	return out;
}
