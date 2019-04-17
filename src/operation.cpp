#include <operation.h>

#include <vector>
#include <Point.h>

using namespace std;

Operation::Operation(char flag, vector<TAD_POINT> point, float angulo, int time){
	this->flag = flag;
	this->point = point;
	this->ang = angulo;
	this->time = time;
}
