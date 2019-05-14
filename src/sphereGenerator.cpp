#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>

#include <ArrayList.h>
#include <Point.h>

#define _USE_MATH_DEFINES
#include <cmath>

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
    TAD_POINT p,p1;
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
                p1 = POINT(0.0,y2,0.0);
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                addElem((*texCoords),POINT((float)(m2+0.5)/slices,1.0,0.0));

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                p1 = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                addElem((*texCoords),POINT((float)(m2+1)/slices,(float)1-(betaYoX*(m1+1))/M_PI,0.0));


                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                p1 = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                addElem((*texCoords),POINT((float)m2/slices,(float)1-(betaYoX*(m1+1))/M_PI,0.0));


            } else if(m1 == (stacks-1)){
                // pontos base
                p = POINT(0.0,y1,0.0);
                p1 = POINT(0.0,y1,0.0);
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                addElem((*texCoords),POINT(0.0,0.0,0.0));

                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                p1 = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                addElem((*texCoords),POINT((float)m2/slices,(float)1-(betaYoX*m1)/M_PI,0.0));

                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));
                p1 = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                addElem((*texCoords),POINT((float)(m2+1)/slices,(float)1-((betaYoX*m1)/M_PI),0.0));


            } else{
            //triangulo
                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                p1 = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));

                p = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                p1 = POINT(r1*cos(m2*alfa),y1,r1*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                p1 = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));
                
            // triangulo inverso
                p = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));// ^<
                p1 = POINT(r2*cos((m2+1)*alfa),y2,r2*sin((m2+1)*alfa));// ^<
                addElem(l2,p);
                addElem((*normals),normalize(p1));

                p = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));// <
                p1 = POINT(r2*cos(m2*alfa),y2,r2*sin(m2*alfa));
                addElem(l2,p);
                addElem((*normals),normalize(p1));

                p = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));// ^>
                p1 = POINT(r1*cos((m2+1)*alfa),y1,r1*sin((m2+1)*alfa));// ^>
                addElem(l2,p);
                addElem((*normals),normalize(p1));
            }
        }
    }/*
    for (int i = 0; i <= stacks; beta += angle_y, i++) {
        for (int slice = 0; slice < slices; slice++) {
            if (i == 0) {
                all_texture.push_back(TexturePoint((slice * slice_size_texture) + (slice_size_texture / 2), 0));
                continue;
            }
            if (i == stacks) {
                all_texture.push_back(TexturePoint((slice * slice_size_texture) + (slice_size_texture / 2), incStacks));
                continue;
            }

            alpha = ((2 * M_PI) / (slices)) * slice;
            float x = radius * cos(beta) * sin(alpha);
            float z = radius * cos(beta) * cos(alpha);
            float y = radius * sin(beta);
            all_coordinate.push_back(Point(x, y, z));
            all_normal.push_back(Point(x / radius, y / radius, z / radius));
            all_texture.push_back(TexturePoint((slice * slice_size_texture), incStacks));
        }

        if (i != 0 && i != stacks) {
            all_texture.push_back(TexturePoint(1, incStacks));
            incStacks += stack_size_texture;
        }
    }*/
    for(m1=0;m1<stacks;m1++){
        for(m2=0;m2<slices;m2++){
            if(m1 == 0){
                addElem(*texCoords,POINT((float)m2*slice_texture+(slice_texture/2),1.0,0.0));
                addElem(*texCoords,POINT((float)m2*slice_texture,(float)1-(stack_texture*m1+stack_texture),0.0));
                addElem(*texCoords,POINT((float)(m2*slice_texture+slice_texture),(float)1-(stack_texture*m1+stack_texture),0.0));
            }
            else if(m1 == (stacks-1)){
                addElem(*texCoords,POINT(m2*slice_texture+(slice_texture/2),0.0,0.0));
                addElem(*texCoords,POINT(m2*slice_texture+slice_texture,1-(stack_texture*m1),0.0));
                addElem(*texCoords,POINT(m2*slice_texture,1-(stack_texture*m1),0.0));

            } else{
                addElem(*texCoords,POINT(m2*slice_texture,1-(m1*stack_texture),0.0));
                addElem(*texCoords,POINT(m2*slice_texture,1-(m1*stack_texture+stack_texture),0.0));
                addElem(*texCoords,POINT(m2*slice_texture+slice_texture,1-(m1*stack_texture+stack_texture),0.0));

                addElem(*texCoords,POINT(m2*slice_texture+slice_texture,1-(m1*stack_texture),0.0));
                addElem(*texCoords,POINT(m2*slice_texture,1-(m1*stack_texture),0.0));
                addElem(*texCoords,POINT(m2*slice_texture+slice_texture,1-(m1*stack_texture+stack_texture),0.0));
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