#ifndef OPERATION_H
#define OPERATION_H

#include <Point.h>
#include <vector>

class Operation
 {
 public:
 	Operation(char , vector<TAD_POINT> , float, int);
 	char flag;
    vector<TAD_POINT> point;
    float ang;
    int time;
 };

#endif