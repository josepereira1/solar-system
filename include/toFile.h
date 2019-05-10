#ifndef TOFILE_H
#define TOFILE_H

#include <ArrayList.h>
#include <string>

using namespace std;

void list2fileWindex(TAD_ARRAY_LIST points, int* indexPoints, TAD_ARRAY_LIST normals, int* indexNormals, TAD_ARRAY_LIST texCoords, int* indexTexCoords, int tam, const char* path);

#endif