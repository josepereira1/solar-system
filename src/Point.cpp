#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <Point.h>


typedef struct TCD_Point{
	float x;
	float y;
	float z;	
} TCD_Point;


// CONSTRUTOR
TAD_POINT POINT(float x, float y, float z) {
	TAD_POINT point = (TAD_POINT) malloc(sizeof(TCD_Point));
	point->x = x;
	point->y = y;
	point->z = z;
	return point;
}


// GETERS
float getX(TAD_POINT point) {
	return point->x;
}

float getY(TAD_POINT point) {
	return point->y;
}

float getZ(TAD_POINT point) {
	return point->z;
}


// SETTERS
void setX(TAD_POINT point, float x) {
	point->x = x;
}

void setY(TAD_POINT point, float y) {
	point->y = y;
}

void setZ(TAD_POINT point, float z) {
	point->z = z;
}


int equalsPoint(TAD_POINT point1, TAD_POINT point2){
	return getX(point1) == getX(point2)
		&& getY(point1) == getY(point2)
		&& getZ(point1) == getZ(point2);
}


TAD_POINT normalize(TAD_POINT point) {

	float l = sqrt((point->x)*(point->x) + (point->y)*(point->y) + (point->z)*(point->z));
	if (l == 0.0f || l == -0.0f) l = 1.0f;
	point->x = (point->x)/l;
	point->y = (point->y)/l;
	point->z = (point->z)/l;
	return point;
}


void cross(TAD_POINT a, TAD_POINT b, TAD_POINT res) {

	res->x = getY(a)*getZ(b) - getZ(a)*getY(b);
	res->y = getZ(a)*getX(b) - getX(a)*getZ(b);
	res->z = getX(a)*getY(b) - getY(a)*getX(b);
}

void point2string(TAD_POINT point) {
	printf("TAD_POINT{x=%.5f, y=%.5f, z=%.5f}\n", point->x, point->y, point->z);
}
