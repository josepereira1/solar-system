#ifndef TOFILE_H
#define TOFILE_H

#include <ArrayList.h>
#include <string>

using namespace std;

void list2fileWindex(TAD_ARRAY_LIST points, int* indices, int tam, const char* path);
// void list2file(TAD_ARRAY_LIST points, const char* path);
// void bezier2file(string patchFile, string outputFile, int tLevel);
TAD_ARRAY_LIST bezier2file(string patchFile, int tLevel);

#endif