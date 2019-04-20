#include <operation.h>

#include <vector>
#include <Point.h>

using namespace std;

Operation::Operation(char flag, vector<TAD_POINT> points, int time){
	this->flag = flag;
	this->points = points;
	this->time = time;
}
