#ifndef OPERATION_H
#define OPERATION_H

#include <Point.h>

using namespace std;

class Operation
 {
 public:
 	Operation(char , TAD_POINT, float, int);
 	char flag;
    TAD_POINT point;
    float ang;
    int time;
 };

#endif