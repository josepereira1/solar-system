#include <operation.h>

 Operation::Operation(char flag, vector<TAD_POINT> point, float angulo, int time){
        this->flag = flag;
        this->point = point;
        this->ang = angulo;
        this->time = time;
    }