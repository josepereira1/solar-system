#include <ArrayList.h>
#include <Point.h>


TAD_ARRAY_LIST getPointsOfPlane(int side){
    float c = side / 2.0;
    TAD_ARRAY_LIST l = ARRAY_LIST(50);
    
    addElem(l,POINT(c,0.0,-c));
    addElem(l,POINT(-c,0.0,-c));
    addElem(l,POINT(-c,0.0,c));
    addElem(l,POINT(-c,0.0,c));
    addElem(l,POINT(c,0.0,c));
    addElem(l,POINT(c,0.0,-c));

    return l;
}
