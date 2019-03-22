#include "../include/operation.h"

using namespace std;

 Operation::Operation(char flag, float x, float y, float z, float angulo){
        this->flag = flag;
        this->x = x;
        this->y = y;
        this->z = z;
        this->ang = angulo;
    }