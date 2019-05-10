#ifndef SPHEREGENERATOR_H
#define SPHEREGENERATOR_H

#include <ArrayList.h>

TAD_ARRAY_LIST getPointsOfSphere(float radius, int slices, int stacks, TAD_ARRAY_LIST *normals, TAD_ARRAY_LIST *texCoords);

void printer(TAD_ARRAY_LIST l1);

#endif