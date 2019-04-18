#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <Point.h>
#include <ArrayList.h>



TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points);
int contains(TAD_ARRAY_LIST points, TAD_POINT point);
int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points);
int getPosition(TAD_ARRAY_LIST points, TAD_POINT point);

void filter(TAD_ARRAY_LIST* points, TAD_ARRAY_LIST* withoutRepeated, int** positions) {
	int size = getArraySize(points);
	*positions = (int*)malloc(sizeof(int)*size);
	*withoutRepeated = removeRepeated(points);
	*positions = getPositions(points,withoutRepeated);
}

TAD_ARRAY_LIST removeRepeated(TAD_ARRAY_LIST points){
	int i , j, size;
	size = getArraySize(points);
	TAD_ARRAY_LIST res = malloc(sizeof(TCD_ARRAY_LIST)*size);
	
	for(j = 0, i = 0; i < size; i++){
		TAD_POINT point = getElem(points,i);
		if(contains(res, point) == 0){
			addElem(res, point);
			j++;
		}
	}
	return res;
}

int contains(TAD_ARRAY_LIST points, TAD_POINT point){
	int i, size;
	size = getArraySize(points);

	for(i = 0; i < size; i++){
		if(equalsPoint(getElem(points,i), point)){
			return 1;
		}
	}

	return 0;	//	false
}

int* getPositions(TAD_ARRAY_LIST all_points, TAD_ARRAY_LIST filtered_points){
	int i, size;
	TAD_POINT point;
	size = getArraySize(all_points);
	int* res = (int*)malloc(size*sizeof(int));
	
	for(i = 0; i < size; i++){
		point = getElem(all_points,i);
		res[i] = getPosition(filtered_points, point);
	}
	return res;
}

int getPosition(TAD_ARRAY_LIST points, TAD_POINT point){
	int i, size = getArraySize(points);
	TAD_POINT aux_point;
	for(i = 0; i < size; i++){
		aux_point = getElem(points,i);
		if(equalsPoint(aux_point, point))return i;
	}
	return -1;
}