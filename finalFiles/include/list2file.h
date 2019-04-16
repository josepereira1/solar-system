#ifndef LIST2FILE_H
#define LIST2FILE_H

#include <Point.h>
#include <string.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void list2file(vector<TAD_POINT> points, int positions[], int tam, const char* path);

#endif 