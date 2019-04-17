#ifndef FROMFILE_H
#define FROMFILE_H

#include <vector>
#include <Point.h>

using namespace std;

void readPatchFile(string path, int*** arrayPatchs, vector<TAD_POINT> &pontos);
vector<float> file2list(const char*);

#endif