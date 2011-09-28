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
