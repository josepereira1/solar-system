#ifndef OPERATION_H
#define OPERATION_H

#include <Point.h>
#include <vector>

using namespace std;

class Operation{
public:
	Operation(char , vector<TAD_POINT>, int);
	char flag;
	vector<TAD_POINT> points;
	int time;
 };

#endif