#define _USE_MATH_DEFINES 
#include <math.h>
#include <vector>

#include <Point.h>

using namespace std;

vector<TAD_POINT> getPointsOfCone(float radius, float height, int slices, int stacks) {
  
    float angle = (2*M_PI)/slices;
    TAD_POINT p1, p2, p3, p4, p5, p6, p7, p8, p9;
    vector<TAD_POINT> l
    float tmp1, tmp2, fraction_height;

    for(int i = 0; i < stacks; i++){
        for(int j = 0; j < slices; j++){
            tmp1 = (radius - (radius/stacks)*i);
            tmp2 = (radius - (radius/stacks)*(i+1));
            fraction_height = (height/stacks)*i;

            if(i == 0){ //  a base tem que ser voltada para baixo
                p1 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
                p2 = POINT(0.0,  (height/stacks)*i, 0.0);
                p3 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
            }/*else{
                p1 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
                p2 = POINT(0.0,  (height/stacks)*i, 0.0);
                p3 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
            }*/
            //  para não desenhar os triângulos interiores basta comentar as 3 linhas acima do else
            p4 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
            p5 = POINT(tmp2*sin(angle*(j+1)), fraction_height+((height/stacks)), tmp2*cos(angle*(j+1)));
            p6 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));

            p7 = POINT(tmp2*sin(angle*(j+1)), fraction_height+((height/stacks)), tmp2*cos(angle*(j+1)));
            p8 = POINT(tmp2*sin(angle*j), fraction_height+((height/stacks)), tmp2*cos(angle*j));
            p9 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
             
            l.push_back(p1);
            l.push_back(p2);
            l.push_back(p3);
            l.push_back(p4);
            l.push_back(p5);
            l.push_back(p6);
            l.push_back(p7);
            l.push_back(p8);
            l.push_back(p9);
        }
    }
    return l;
}