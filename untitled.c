#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



void design_sphere(float radius, int slices, int stacks, const char* patch) {
    printf("Aexecutar\n");
    float r = radius;
    float height = radius;
    int max = slices*(stacks-1)+2;
    float alfaXoZ = (2*M_PI)/slices;
    float betaYoX = (2*radius)/stacks;
    char* str = malloc(sizeof(char)*1024*1024);
    char* tmp = malloc(sizeof(char)*1024*1024);
    int m1,m2;
    printf("triangulos : %d\n",slices*(stacks-1)*2);
    // Inserir número de vertices desenhados 
    printf("%d\n",slices*(stacks-1)+2);
    //cria ponto superior
    printf("glVertex3f(%.5f, %.5f, %.5f);\n",0.0,radius,0.0);
    //cria pontos intermédios
    for(m1=1;m1<stacks;m1++){ // itera circulos (muda o raio, alfaXoZ volta ao inicio)
        printf("\n\n\n");
        height -= betaYoX; // calcula altura do circulo
        r = sqrt((radius*radius)-(height*height)); // muda o raio para o circulo correspondente
        for(m2=0;m2<slices;m2++){ // itera vertices(muda o alfaXoZ)
            printf("glVertex3f(%.5f, %.5f, %.5f);\n",r*cos(m2*alfaXoZ), height,r*sin(m2*alfaXoZ));
        }
    }
    printf("\n\n\n");
    //cria ultimo ponto
    printf("glVertex3f(%.5f, %.5f, %.5f);\n",0.0,radius,0.0);

    // nº de ligações de vertices
    printf("%d\n",slices*(stacks-1)*2);
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        for(m2=1;m2<=slices;m2++){ //  vertices interiores = nº de slices * 2
            if(m1==0){

                if(m2 == 1){printf("%d, %d, %d\n",1,slices+1,2);}
                else{printf("%d, %d, %d\n",1,m2,m2+1);}

            } else if(m1 == 3){
                
                if(m2 == 1){printf("\n\n");printf("%d, %d, %d\n",max,max-1,max-slices);}//contar todos para cima
                else{printf("%d, %d, %d\n",max,max-slices+m2-1,max-slices+m2-2);}

            } else{
                printf("\n\n");
                if(m2 == 1){printf("%d, %d, %d\n",m1*slices+m2,(m1+1)*slices+m2,m1*slices+m2+1);printf("%d, %d, %d\n",m1*slices+m2+1,(m1-1)*slices+m2+1,m1*slices+m2);}
                else{printf("%d, %d, %d\n",(m1-1)*slices+m2,m1*slices+m2,m1*slices+m2+1);printf("%d, %d, %d\n",m1*slices+m2+1,(m1-1)*slices+m2+1,(m1-1)*slices+m2);}

            }
        }
    }
}

int main(int argc, char const *argv[])
{
    design_sphere(atof(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
    return 0;
}