#ifndef P0_TRACER_H
#define P0_TRACER_H

#include "structures.h"

bool getIntersection(prim_t &p, ray_t &r, double &t);

color_t getColor(int x, int y); // return pixel color, also calculater initial ray parameters

#endif