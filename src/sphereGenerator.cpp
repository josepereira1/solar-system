#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <ArrayList.h>
#include <Point.h>

#define _USE_MATH_DEFINES
#include <math.h>

TAD_ARRAY_LIST getPointsOfSphere(float radius, int slices, int stacks, TAD_ARRAY_LIST *normals, TAD_ARRAY_LIST *texCoords) {
    float r1 = radius;
    float r2 = radius;
    float alfa = (2*M_PI)/slices;
    float betaYoX = (M_PI)/stacks;
    float height = radius;
    float diametro = radius*2;
    float y1,y2;
    int max = slices*(stacks-1)+2;
    TAD_ARRAY_LIST l2 = ARRAY_LIST(max);
    (* normals) = ARRAY_LIST(max);
    (*texCoords) = ARRAY_LIST(max);
    int m1,m2;
    TAD_POINT p;
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        y2 = height;
        height = cos(betaYoX*(m1+1))*radius;
        y1 = height;
        r2 = sqrt((radius*radius)-(y2*y2));
        r1 = sqrt((radius*radius)-(y1*y1));
        for(m2=0;m2<slices;m2++){ //  vertices interiores = nº de slices * 2
            if(m1==0){
                // pontos topo
                p = POINT(0.0,y2,0.0);
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(0.0,1.0,0.0));

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(0.5,1.0,0.0));

                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(1.0,1.0,0.0));


            } else if(m1 == (stacks-1)){
                // pontos base
                p = POINT(0.0,y1,0.0);
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(0.0,0.0,0.0));
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(0.5,0.0,0.0));
                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(1.0,0.0,0.0));


            } else{
                //triangulo
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(m2/slices,(betaYoX*m1)/M_PI,0.0));

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(m2/slices,(betaYoX*(m1+1))/M_PI,0.0));

                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(m2/slices,(betaYoX*(m1+1))/M_PI,0.0));
                

                // triangulo inverso
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));// <
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(m2/slices,(betaYoX*m1)/M_PI,0.0));

                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));// ^<
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(m2/slices,(betaYoX*m1)/M_PI,0.0));

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));// ^>
                addElem(l2,p);
                addElem((*normals),normalize(p));
                addElem((*texCoords),POINT(m2/slices,(betaYoX*(m1+1))/M_PI,0.0));
            }
        }
    }
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