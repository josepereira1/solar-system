#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ArrayList.h>
#include <Point.h>

#include <iostream>
#include <cstdlib>

using namespace std;

static TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points, TAD_ARRAY_LIST normals, TAD_ARRAY_LIST texCoords, TAD_ARRAY_LIST* normalsWRepeat, TAD_ARRAY_LIST* texCoordsWRepeat);
static int contains(TAD_ARRAY_LIST points, TAD_POINT point);
static int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points);
static int getPosition(TAD_ARRAY_LIST points, TAD_POINT point);

void filter(TAD_ARRAY_LIST points, TAD_ARRAY_LIST* withoutRepeated, TAD_ARRAY_LIST normals, TAD_ARRAY_LIST* normalsWRepeat, TAD_ARRAY_LIST texCoords, TAD_ARRAY_LIST* texCoordsWRepeat, int** positions){
	int size = getArraySize(points);
	*withoutRepeated = ARRAY_LIST(size);
	*normalsWRepeat = ARRAY_LIST(size);
	*texCoordsWRepeat = ARRAY_LIST(size);
	*positions = (int* )malloc(size*sizeof(int));
	*withoutRepeated = removeRepeated(points,normals,texCoords,normalsWRepeat,texCoordsWRepeat);
	*positions = getPositions(points, *withoutRepeated);
}

static TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points, TAD_ARRAY_LIST normals, TAD_ARRAY_LIST texCoords, TAD_ARRAY_LIST* normalsWRepeat, TAD_ARRAY_LIST* texCoordsWRepeat){
	int size = getArraySize(points);
	TAD_ARRAY_LIST res = ARRAY_LIST(size);
	for(int i = 0; i < size; i++){
		TAD_POINT point = (TAD_POINT) getElem(points,i);
		if(contains(res, point) == 0){
			addElem(res, point);
			addElem(*normalsWRepeat, getElem(normals,i));
			addElem(*texCoordsWRepeat, getElem(texCoords,i));	
		}
	}
	return res;
}

static int contains(TAD_ARRAY_LIST points, TAD_POINT point){
	int size = getArraySize(points);
	for(int i = 0; i < size; i++)
		if(equalsPoint((TAD_POINT) getElem(points, i), point)) return 1;
	return 0;
}

static int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points){
	int size = getArraySize(all_points);
	int* res = (int*)malloc(size*sizeof(int));
	for(int i = 0; i < size; i++)
		res[i] = getPosition(filtered_points, (TAD_POINT) getElem(all_points, i));
	return res;
}

static int getPosition(TAD_ARRAY_LIST points, TAD_POINT point){
	int size = getArraySize(points);
	for(int i = 0; i < size; i++)
		if(equalsPoint((TAD_POINT) getElem(points, i), point)) return i;
	return -1;
}