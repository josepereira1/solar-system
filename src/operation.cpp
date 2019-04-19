#include <operation.h>

#include <vector>
#include <Point.h>

using namespace std;

Operation::Operation(char flag, vector<TAD_POINT> points, float angulo, int time){
	this->flag = flag;
	this->points = points;
	this->ang = angulo;
	this->time = time;
}
