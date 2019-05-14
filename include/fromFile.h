#ifndef FROMFILE_H
#define FROMFILE_H

#include <vector>
#include <Point.h>
#include <ArrayList.h>

using namespace std;

//void readPatchFile(string path, int*** arrayPatchs, vector<TAD_POINT> &pontos);
void readPatchFile(string path, int*** arrayPatchs, TAD_ARRAY_LIST *pontos);
void file2list(string path, int* indicesTAM, unsigned int** indexPoints, float** points, int* pointsTAM, int* indexNormalsTAM, unsigned int** indexNormals, float** normals, int* normalsTAM, int* indexTexCoordsTAM, unsigned int** indexTexCoords, float** texCoords, int* texCoordsTAM);

#endif