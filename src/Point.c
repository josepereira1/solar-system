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
	TAD_POINT point = malloc(sizeof(TCD_Point));
	point->x = x;
	point->y = y;
	point->z = z;
	return point;
}

//GETERS
float getX(TAD_POINT point) {
	return point->x;
}

float getY(TAD_POINT point) {
	return point->y;
}

float getZ(TAD_POINT point) {
	return point->z;
}

void getXYZ(TAD_POINT point, float* x, float* y, float* z) {
	*x = point->x;
	*y = point->y;
	*z = point->z;
}

int equalsPoint(TAD_POINT point1, TAD_POINT point2){
	return getX(point1) == getX(point2)
		&& getY(point1) == getY(point2)
		&& getZ(point1) == getZ(point2);
}

void point2string(TAD_POINT point) {
	printf("TAD_POINT{x=%.5f, y=%.5f, z=%.5f}\n", point->x, point->y, point->z);
}
