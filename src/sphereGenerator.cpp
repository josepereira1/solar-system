#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <ArrayList.h>
#include <Point.h>

#define _USE_MATH_DEFINES
#include <math.h>

TAD_ARRAY_LIST getPointsOfSphere(float radius, int slices, int stacks) {
	float r = radius;
    float r1 = radius;
    float r2 = radius;
    float alfa = (2*M_PI)/slices;
    float betaYoX = (M_PI)/stacks;
	float height = radius;
    float y1,y2;
    int max = slices*(stacks-1)+2;
    TAD_ARRAY_LIST l1 = ARRAY_LIST(max);
    TAD_ARRAY_LIST l2 = ARRAY_LIST(max);
    int m1,m2;
    TAD_POINT p;
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
                addElem(l2,p);
                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p);
                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                addElem(l2,p);

            } else if(m1 == (stacks-1)){
                p = POINT(0.0,y1,0.0);
                addElem(l2,p);
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));
                addElem(l2,p);


            } else{
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p);
                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                addElem(l2,p);

                // triangulo inverso
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));// <
                addElem(l2,p);
                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));// ^<
                addElem(l2,p);
                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));// ^>
                addElem(l2,p);
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
