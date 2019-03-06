#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ArrayList.h>
#include <Point.h>
#include <filterPoints.h>

static TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points);
static int contains(TAD_ARRAY_LIST points, TAD_POINT point);
static int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points);
static int getPosition(TAD_ARRAY_LIST points, TAD_POINT point);

void filter(TAD_ARRAY_LIST points, TAD_ARRAY_LIST* withoutRepeated, int** positions){
	int size = getArraySize(points);
	*withoutRepeated = ARRAY_LIST(size);
	*positions = (int* )malloc(size*sizeof(int));

	*withoutRepeated = removeRepeated(points);
	*positions = getPositions(points, *withoutRepeated);
}

static int contains(TAD_ARRAY_LIST points, TAD_POINT point){
	int i, size;
	size = getArraySize(points);

	for(i = 0; i < size; i++){
		if(equalsPoint( (TAD_POINT) getElem(points, i), point)){
			return 1;
		}
	}

	return 0;	//	false
}

static TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points){
	int i , j, size;
	size = getArraySize(points);
	TAD_ARRAY_LIST res = ARRAY_LIST(size);
	
	for(j = 0, i = 0; i < size; i++){
		if(contains(res, (TAD_POINT) getElem(points,i)) == 0){
			addElem(res, getElem(points, i));
			j++;
		}
	}
	return res;
}


static int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points){
	int i, size;
	TAD_POINT point;
	size = getArraySize(all_points);
	int* res = (int*)malloc(size*sizeof(int));
	
	for(i = 0; i < size; i++){
		point = (TAD_POINT) getElem(all_points, i);
		res[i] = getPosition(filtered_points, point);
	}
	return res;
}

static int getPosition(TAD_ARRAY_LIST points, TAD_POINT point){
	int i, size = getArraySize(points);
	for(i = 0; i < size; i++){
		if(equalsPoint((TAD_POINT) getElem(points, i), point))return i;
	}
	return -1;
}
