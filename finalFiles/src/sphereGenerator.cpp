#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>

#include <Point.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

vector<TAD_POINT> getPointsOfSphere(float radius, int slices, int stacks) {
	float r = radius;
    float r1 = radius;
    float r2 = radius;
    float alfa = (2*M_PI)/slices;
    float betaYoX = (2*M_PI)/stacks;
	float height = radius;
    float y1,y2;
    int max = slices*(stacks-1)+2;
    vector<TAD_POINT> l1, l2;
    int m1,m2;
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        y2= height;
        height = cos(betaYoX*(m1+1))*radius;
        y1 = height;
        r2 = sqrt((radius*radius)-(y2*y2));
        r1 = sqrt((radius*radius)-(y1*y1));
        for(m2=0;m2<slices;m2++){ //  vertices interiores = nº de slices * 2
            if(m1==0){
                p = POINT(0.0,y2,0.0);
                l2.push_back(p);
                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                l2.push_back(p);
                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                l2.push_back(p);
            } else if(m1 == (stacks-1)){
                p = POINT(0.0,y1,0.0);
                l2.push_back(p);
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                l2.push_back(p);
                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));
                l2.push_back(p);


            } else{
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                l2.push_back(p);
                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                l2.push_back(p);
                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                l2.push_back(p);

                // triangulo inverso
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));// <
                l2.push_back(p);
                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));// ^<
                l2.push_back(p);
                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));// ^>
                l2.push_back(p);
            }
        }
    }
    //filter(l2);
    return l2;
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