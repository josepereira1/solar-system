#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include "Point.c"
//#include "ArrayList.c"
#include "newSphereGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

TAD_ARRAY_LIST design_sphere(float radius, int slices, int stacks, const char* patch) {
    printf("A começar esfera\n");
	float r = radius;
    float r1 = radius;
    float r2 = radius;
    float x,z;
    float alfa = (2*M_PI)/slices;
    float betaYoX = (2*radius)/stacks;
	float height = radius;
    float y1,y2;
    int max = slices*(stacks-1)+2;
    TAD_ARRAY_LIST l1 = ARRAY_LIST(max);
    TAD_ARRAY_LIST l2 = ARRAY_LIST(max);
    TAD_ARRAY_LIST l3;
    TAD_ARRAY_LIST l4;
    int m1,m2;
    //cria ponto superior
    TAD_POINT p;

    printf("alfa. = %f\n", alfa);

    p = POINT(0.0,radius,0.0);
    addElem(l1,p);
    //cria pontos intermédios
    for(m1=1;m1<stacks;m1++){ // itera circulos (muda o raio, alfaXoZ volta ao inicio)
    	height -= betaYoX; // calcula altura do circulo
        r = sqrt((radius*radius)-(height*height)); // muda o raio para o circulo correspondente
    	for(m2=0;m2<slices;m2++){ // itera vertices(muda o alfaXoZ)
            p = POINT(r*cos(m2*alfa),height,r*sin(m2*alfa));
            addElem(l1,p);
    	}
    }
    //cria ultimo ponto
    p = POINT(0.0,-radius,0.0);
    addElem(l1,p);
    height = radius;
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        y2= height;
        height -= betaYoX;
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
    printer(l2);
    printf("A devolver esfera\n");
    //filter(l2,l3,l4);
    return l2;
}



void printer(TAD_ARRAY_LIST l1){
    int x = getArraySize(l1);
    int i;
    for(i = 0;i<x;i++){
        printf("%f, %f, %f\n",getX(getElem(l1,i)),getY(getElem(l1,i)),getZ(getElem(l1,i)));
        if(((i+1)%3) == 0) printf("\n\n");
    }

}




