#include <stdio.h>
#include <stdlib.h>
#include <cmath>
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
    float y1,y2;
    float slice_texture = 1.0f / slices;
    float stack_texture = 1.0f / stacks;
    int max = slices*(stacks-1)+2;
    TAD_ARRAY_LIST l2 = ARRAY_LIST(max);
    (* normals) = ARRAY_LIST(max);
    (*texCoords) = ARRAY_LIST(max);
    float m1,m2;
    TAD_POINT p0,p1,p2,p3,p4,p5;
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
                p0 = POINT(0.0,y2,0.0);
                p1 = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                p2 = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p0);
                addElem(l2,p1);
                addElem(l2,p2);

                //normal topo

                // p1-p0
                p3 = POINT(getX(p1)-getX(p0),getY(p1)-getY(p0),getZ(p1)-getZ(p0));
                //p2-p0
                p4 = POINT(getX(p2)-getX(p0),getY(p2)-getY(p0),getZ(p2)-getZ(p0));
                // p5 = p3*p4/|p3*p4|;
                cross(p3,p4,p5);

                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));

                // coordenadas textura topo

                p0 = POINT((float)m2*slice_texture+(slice_texture/2),1.0,0.0);
                p1 = POINT((float)m2*slice_texture,(float)1-(stack_texture*m1+stack_texture),0.0);
                p2 = POINT((float)(m2*slice_texture+slice_texture),(float)1-(stack_texture*m1+stack_texture),0.0);

                addElem(*texCoords,p0);
                addElem(*texCoords,p1);
                addElem(*texCoords,p2);

            } else if(m1 == (stacks-1)){
                // pontos base
                p0 = POINT(0.0,y1,0.0);
				p1 = POINT(r2*cos((m2 + 1)*alfa), y2, r2*sin((m2 + 1)*alfa));
                p2 = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p0);
                addElem(l2,p1);
                addElem(l2,p2);

                //normal base
                // p1-p0
                p3 = POINT(getX(p1)-getX(p0),getY(p1)-getY(p0),getZ(p1)-getZ(p0));
                //p2-p0
                p4 = POINT(getX(p2)-getX(p0),getY(p2)-getY(p0),getZ(p2)-getZ(p0));
                // p5 = p3*p4/|p3*p4|;
                cross(p3,p4,p5);

                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));

                // coordenadas textura base

                p0 = POINT(m2*slice_texture+(slice_texture/2),0.0,0.0);
                p1 = POINT(m2*slice_texture+slice_texture,1-(stack_texture*m1),0.0);
                p2 = POINT(m2*slice_texture,1-(stack_texture*m1),0.0);

                addElem(*texCoords,p0);
                addElem(*texCoords,p1);
                addElem(*texCoords,p2);


            } else{

                //triangulo
                p0 = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                p1 = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                p2 = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));

                addElem(l2,p0);
                addElem(l2,p1);
                addElem(l2,p2);

                //normal triangulo topo
                // p1-p0
                p3 = POINT(getX(p1)-getX(p0),getY(p1)-getY(p0),getZ(p1)-getZ(p0));
                //p2-p0
                p4 = POINT(getX(p2)-getX(p0),getY(p2)-getY(p0),getZ(p2)-getZ(p0));
                // p5 = p3*p4/|p3*p4|;
                cross(p3,p4,p5);

                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));

                // coordenadas textura triangulo topo lateral

                p0 = POINT(m2*slice_texture,1-(m1*stack_texture),0.0);
                p1 = POINT(m2*slice_texture,1-(m1*stack_texture+stack_texture),0.0);
                p2 = POINT(m2*slice_texture+slice_texture,1-(m1*stack_texture+stack_texture),0.0);

                addElem(*texCoords,p0);
                addElem(*texCoords,p1);
                addElem(*texCoords,p2);
                
                // triangulo inverso
                p0 = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));// ^<
                addElem(l2,p);

                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));// <
                addElem(l2,p);

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));// ^>
                addElem(l2,p);

                //normal triangulo base
                // p1-p0
                p3 = POINT(getX(p1)-getX(p0),getY(p1)-getY(p0),getZ(p1)-getZ(p0));
                //p2-p0
                p4 = POINT(getX(p2)-getX(p0),getY(p2)-getY(p0),getZ(p2)-getZ(p0));
                cross(p3,p4,p5);

                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));
                addElem((*normals),normalize(p5));

                // coodenadas textura triangulo base lateral

                p0 = POINT(m2*slice_texture+slice_texture,1-(m1*stack_texture),0.0);
                p1 = POINT(m2*slice_texture,1-(m1*stack_texture),0.0);
                p2 = POINT(m2*slice_texture+slice_texture,1-(m1*stack_texture+stack_texture),0.0);

                addElem(*texCoords,p0);
                addElem(*texCoords,p1);
                addElem(*texCoords,p2);
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