#ifndef FROMFILE_H
#define FROMFILE_H

#include <vector>
#include <Point.h>
#include <ArrayList.h>

//void readPatchFile(string path, int*** arrayPatchs, vector<TAD_POINT> &pontos);
void readPatchFile(string path, int*** arrayPatchs, TAD_ARRAY_LIST *pontos);
void file2list(string path, unsigned int** indices, int* indicesTAM, float** vertexB, int* vertexBTAM);

#endif