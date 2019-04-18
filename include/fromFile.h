#ifndef FROMFILE_H
#define FROMFILE_H

#include <vector>
#include <Point.h>

using namespace std;

void readPatchFile(string path, int*** arrayPatchs, vector<TAD_POINT> &pontos);
void file2list(string path, unsigned int** indices, int* indicesTAM, float** vertexB, int* vertexBTAM);

#endif