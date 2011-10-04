#ifndef P0_UTIL_H
#define P0_UTIL_H

#include "structures.h"
#include <cmath>

// funzioni utili per semplificarci la vita

inline vector_t operator+ (vector_t &v1, vector_t &v2)
{
	vector_t v = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return v;
}

inline vector_t operator- (vector_t &v1, vector_t &v2)
{
	vector_t v = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

inline double operator* (vector_t &vect1, vector_t &vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z);
}

inline vector_t operator* (vector_t &v, double &t)
{
	vector_t vt = { v.x * t, v.y * t, v.z * t };
	return vt;
}

inline void operator+= (color_t &c, double &i)
{
	c.b += i;
	c.g += i;
	c.r += i;
}

inline color_t operator* (color_t &c, double &i)
{
	color_t cl = { c.r * i, c.g * i, c.b * i };
	return cl;
}

inline color_t operator* (color_t &c1, color_t &c2)
{
	color_t cl = { c1.r * c2.r, c1.g * c2.g, c1.b * c2.b };
	return cl;
}

inline double length(vector_t &vect)
{
	return sqrt(vect*vect);
}

inline vector_t &norm(vector_t &vect)
{
	vect = vect/length(vect);
	return vect;
}

#endif
