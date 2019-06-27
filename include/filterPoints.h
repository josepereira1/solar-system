#ifndef FILTERPOINTS_H
#define FILTERPOINTS_H

#include <ArrayList.h>

/**
This function receive ARRAY_LIST with all points and filter de repeated points,
and return an array with positions.
input:
points = [(1,2,3),(2,3,1),(3,4,1),(2,3,1),(1,2,3)]
output:
withoutReapeated = [(1,2,3),(2,3,1),(3,4,1)]
positions = [0,1,2,1,0]
**/
void filter(TAD_ARRAY_LIST points, TAD_ARRAY_LIST* withoutRepeated, TAD_ARRAY_LIST normals, TAD_ARRAY_LIST* normalsWRepeat, TAD_ARRAY_LIST texCoords, TAD_ARRAY_LIST* texCoordsWRepeat, int** positions);

#endif