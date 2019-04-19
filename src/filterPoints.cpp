#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ArrayList.h>
#include <Point.h>

#include <iostream>
#include <cstdlib>

using namespace std;

TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points);
int contains(TAD_ARRAY_LIST points, TAD_POINT point);
int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points);
int getPosition(TAD_ARRAY_LIST points, TAD_POINT point);

void filter(TAD_ARRAY_LIST points, TAD_ARRAY_LIST* withoutRepeated, int** positions){
	int size = getArraySize(points);
	*withoutRepeated = ARRAY_LIST(size);
	//printf("Chega aqui\n");
	//morre no malloc..
	//*positions = (int* )malloc(size*sizeof(int));
	//printf("Chega aqui\n");
	*withoutRepeated = removeRepeated(points);
	*positions = getPositions(points, *withoutRepeated);
}

TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points){
	int i , j, size;
	size = getArraySize(points);
	TAD_ARRAY_LIST res = ARRAY_LIST(size);
	for(j = 0, i = 0; i < size; i++){
		TAD_POINT point = (TAD_POINT) getElem(points,i);
		if(contains(res, point) == 0){
			addElem(res, point);
			j++;
		}
	}
	return res;
}
int contains(TAD_ARRAY_LIST points, TAD_POINT point){
	int size = getArraySize(points);
	for(int i = 0; i < size; i++){
		if(equalsPoint((TAD_POINT) getElem(points, i), point)){
			return 1;
		}
	}
	return 0;	//	false
}
int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points){
	int size = getArraySize(all_points);
	int* res = (int*)malloc(size*sizeof(int));
	for(int i = 0; i < size; i++){
		res[i] = getPosition(filtered_points, (TAD_POINT) getElem(all_points, i));
	}
	return res;
}

int getPosition(TAD_ARRAY_LIST points, TAD_POINT point){
	int size = getArraySize(points);
	TAD_POINT aux_point;
	for(int i = 0; i < size; i++){
		aux_point = (TAD_POINT) getElem(points, i);
		if(equalsPoint(aux_point , point))return i;
	}
	return -1;
}