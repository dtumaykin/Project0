#ifndef P0_TRACER_H
#define P0_TRACER_H

#define ANTIALIAS_MAX 2

#include "structures.h"

bool getIntersection(prim_t &p, ray_t &r, double &t);

color_t getColor(int x, int y, scene_t &scene); // return pixel color, also calculates initial ray parameters

color_t trace(ray_t &ray, scene_t &scene, int depth); // traces a ray

vector_t getNormal(prim_t &p, point_t &intrPoint); // returns normal in intersection point

#endif