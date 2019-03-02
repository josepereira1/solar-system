#ifndef POINT_H
#define POINT_H

typedef struct TCD_Point* TAD_POINT;

// CONSTRUTOR
TAD_POINT POINT(float x, float y, float z);

//GETERS
float getX(TAD_POINT point);
float getY(TAD_POINT point);
float getZ(TAD_POINT point);
void getXYZ(TAD_POINT point, float* x, float* y, float* z);

//equals
int equalsPoint(TAD_POINT point1, TAD_POINT point2);

//toString()
void point2string(TAD_POINT point);

#endif