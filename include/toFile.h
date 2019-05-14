#ifndef TOFILE_H
#define TOFILE_H

#include <ArrayList.h>
#include <string>

using namespace std;

void list2fileWindex(TAD_ARRAY_LIST points, TAD_ARRAY_LIST normals, TAD_ARRAY_LIST texCoords, const char* path);

#endif