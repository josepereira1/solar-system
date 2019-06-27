#include <ArrayList.h>
#include <Point.h>


TAD_ARRAY_LIST getPointsOfPlane(int side, TAD_ARRAY_LIST *normals, TAD_ARRAY_LIST *texCoords){
    float c = side / 2.0;
    *normals = ARRAY_LIST(6);
    *texCoords = ARRAY_LIST(6);
    TAD_ARRAY_LIST l = ARRAY_LIST(50);
    
    //points
    addElem(l,POINT(c,0.0,-c));
    addElem(l,POINT(-c,0.0,-c));
    addElem(l,POINT(-c,0.0,c));
    addElem(l,POINT(-c,0.0,c));
    addElem(l,POINT(c,0.0,c));
    addElem(l,POINT(c,0.0,-c));

    //normals
    addElem(*normals,POINT(0,1.0f,0));
    addElem(*normals,POINT(0,1.0f,0));
    addElem(*normals,POINT(0,1.0f,0));
    addElem(*normals,POINT(0,1.0f,0));
    addElem(*normals,POINT(0,1.0f,0));
    addElem(*normals,POINT(0,1.0f,0));

    //texCoords
    addElem(*texCoords,POINT(1.0f,1.0f,0));
    addElem(*texCoords,POINT(0,1.0f,0));
    addElem(*texCoords,POINT(0,0,0));
    addElem(*texCoords,POINT(0,0,0));
    addElem(*texCoords,POINT(1.0f,0,0));
    addElem(*texCoords,POINT(1.0f,1.0f,0));

    return l;
}
