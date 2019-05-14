#ifndef BEZIERCREATER_H
#define BEZIERCREATER_H

using namespace std;

#include <ArrayList.h>
#include <string>

TAD_ARRAY_LIST getPointsOfBezier(string patchFile, int tLevel, TAD_ARRAY_LIST *normals);

#endif