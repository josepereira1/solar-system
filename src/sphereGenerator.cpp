#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <ArrayList.h>
#include <Point.h>

#define _USE_MATH_DEFINES
#include <math.h>

TAD_ARRAY_LIST getPointsOfSphere(float radius, int slices, int stacks) {
    float alpha1;
    float alpha2;
    float beta1;
    float beta2;
    TAD_ARRAY_LIST l = ARRAY_LIST(max);
    //std::vector<Point> vertices; //Vector que guarda os vertices
    for (int slice = 0; slice < slices; slice++) {
        for (int stack = 0; stack <= stacks; stack++) {
            float alpha1 = (2 * M_PI / slices) * slice;
            float alpha2 = (2 * M_PI / slices) * (slice + 1);
            float beta1 = (2 * M_PI / stacks) * stack;
            float beta2 = (2 * M_PI / stacks) * (stack + 1);

            addElem(l,Point(r*cos(beta2)*sin(alpha1), r*sin(beta2), r*cos(beta2)*cos(alpha1)));
            addElem(l,Point(r*cos(beta1)*sin(alpha1), r*sin(beta1), r*cos(beta1)*cos(alpha1)));
            addElem(l,Point(r*cos(beta2)*sin(alpha2), r*sin(beta2), r*cos(beta2)*cos(alpha2)));

            addElem(l,Point(r*cos(beta2)*sin(alpha2), r*sin(beta2), r*cos(beta2)*cos(alpha2)));
            addElem(l,Point(r*cos(beta1)*sin(alpha1), r*sin(beta1), r*cos(beta1)*cos(alpha1)));
            addElem(l,Point(r*cos(beta1)*sin(alpha2), r*sin(beta1), r*cos(beta1)*cos(alpha2)));
        }
    }
    printer(l);
    return l;
}


// debug
void printer(TAD_ARRAY_LIST l1){
    int x = getArraySize(l1);
    int i;
    for(i = 0;i<x;i++){
        TAD_POINT point = (TAD_POINT) getElem(l1,i);
        printf("%f, %f, %f\n",getX(point),getY(point),getZ(point));
        if(((i+1)%3) == 0) printf("\n\n");
    }

}