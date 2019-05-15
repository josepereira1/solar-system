#define _USE_MATH_DEFINES 
#include <math.h>

#include <Point.h>
#include <ArrayList.h>

TAD_ARRAY_LIST getPointsOfCone(float radius, float height, int slices, int stacks, TAD_ARRAY_LIST *normals, TAD_ARRAY_LIST *texCoords) {
  
    float angle = (2*M_PI)/slices;
    TAD_POINT p1, p2, p3, p4, p5, p6, p7, p8, p9;
    TAD_ARRAY_LIST l = ARRAY_LIST(300);
	*normals = ARRAY_LIST(300);
	*texCoords = ARRAY_LIST(300);
	addElem(*texCoords, POINT(0, 0, 0));
    float tmp1, tmp2, fraction_height;

        for(int i = 0; i < stacks; i++){
            for(int j = 0; j < slices; j++){
                tmp1 = (radius - (radius/stacks)*i);
                tmp2 = (radius - (radius/stacks)*(i+1));
                fraction_height = (height/stacks)*i;

                if(i == 0){ //  a base tem que ser voltada para baixo
                    p1 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
                    p2 = POINT(0.0, fraction_height, 0.0);
                    p3 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));

					addElem(l, p1);
					addElem(l, p2);
					addElem(l, p3);

					addElem(*normals,POINT(0,-1,0));
					addElem(*normals,POINT(0,-1,0));
					addElem(*normals,POINT(0,-1,0));

					//addElem(*texCoords,POINT());
					//addElem(*texCoords,POINT());
					//addElem(*texCoords,POINT());
                }

                p4 = POINT(tmp1*sin(angle*(j+1)),  fraction_height, tmp1*cos(angle*(j+1)));
                p5 = POINT(tmp2*sin(angle*(j+1)), fraction_height+((height/stacks)), tmp2*cos(angle*(j+1)));
                p6 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));

                p7 = POINT(tmp2*sin(angle*(j+1)), fraction_height+((height/stacks)), tmp2*cos(angle*(j+1)));
                p8 = POINT(tmp2*sin(angle*j), fraction_height+((height/stacks)), tmp2*cos(angle*j));
                p9 = POINT(tmp1*sin(angle*j),  fraction_height, tmp1*cos(angle*j));
              
                addElem(l,p4);
                addElem(l,p5);
                addElem(l,p6);
                addElem(l,p7);
                addElem(l,p8);
                addElem(l,p9);
            }
        }
  return l;
}