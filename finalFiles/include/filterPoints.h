#ifndef FILTERPOINTS_H
#define FILTERPOINTS_H

#include <Point.h>
#include <vector>

using namespace std;

/**
This function receive vector<TAD_POINT> with all points and filter de repeated points,
and return an array with positions.
input:
points = [(1,2,3),(2,3,1),(3,4,1),(2,3,1),(1,2,3)]
output:
withoutReapeated = [(1,2,3),(2,3,1),(3,4,1)]
positions = [0,1,2,1,0]
**/
void filter(vector<TAD_POINT> points, vector<TAD_POINT> withoutRepeat, int** positions);

#endif