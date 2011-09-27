#ifndef P0_UTIL_H
#define P0_UTIL_H

#include "structures.h"
#include <cmath>

// funzioni utili per semplificarci la vita

inline double dot(vector_t &vect1, vector_t &vect2)
{
	return (vect1.x * vect2.x + vect1.y * vect2.y + vect1.z * vect2.z);
}

inline double length(vector_t &vect)
{
	return sqrt(dot(vect, vect));
}

inline vector_t &norm(vector_t &vect)
{
	vect = vect/length(vect);
	return vect;
}

#endif
