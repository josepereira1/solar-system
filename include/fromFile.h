#ifndef FROMFILE_H
#define FROMFILE_H

#include <vector>
#include <Point.h>
#include <ArrayList.h>

using namespace std;

void readPatchFile(string path, int*** arrayPatchs, TAD_ARRAY_LIST *pontos);
void file2list(string path, float** points, int* pointsTAM, float** normals, int* normalsTAM, float** texCoords, int* texCoordsTAM);

#endif