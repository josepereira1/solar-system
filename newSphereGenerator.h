#ifndef SPHERE_H
#define SPHERE_H


#include "Point.h"
#include "ArrayList.h"

TAD_ARRAY_LIST design_sphere(float radius, int slices, int stacks, const char* patch);
void printer(TAD_ARRAY_LIST l1);

#endif