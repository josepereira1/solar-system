#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <Point.h>
#include <vector>

using namespace std;


vector<TAD_POINT> removeRepeated(vector<TAD_POINT> points);
int contains(vector<TAD_POINT> points, TAD_POINT point);
int* getPositions(vector<TAD_POINT> all_points, vector<TAD_POINT> filtered_points);
int getPosition(vector<TAD_POINT> points, TAD_POINT point);

void filter(vector<TAD_POINT> points, vector<TAD_POINT> withoutRepeated, int** positions) {
	int size = points.size();
	*positions = (int*)malloc(sizeof(int)*size);
	withoutRepeated = removeRepeated(points);
	*positions = getPositions(points,withoutRepeated);
}

vector<TAD_POINT> removeRepeated(vector>TAD_POINT> points){
	int i , j, size;
	size = points.size();
	vector<TAD_POINT> res;
	
	for(j = 0, i = 0; i < size; i++){
		if(contains(res, points[i]) == 0){
			res.push_back(points[i]);
			j++;
		}
	}
	return res;
}

int contains(vector<TAD_POINT> points, TAD_POINT point){
	int i, size;
	size = points.size();

	for(i = 0; i < size; i++){
		if(equalsPoint(points[i], point)){
			return 1;
		}
	}

	return 0;	//	false
}

int* getPositions(vector<TAD_POINT> all_points, vector<TAD_POINT> filtered_points){
	int i, size;
	TAD_POINT point;
	size = all_points.size();
	int* res = (int*)malloc(size*sizeof(int));
	
	for(i = 0; i < size; i++){
		point = all_points[i];
		res[i] = getPosition(filtered_points, point);
	}
	return res;
}

int getPosition(vector<TAD_POINT> points, TAD_POINT point){
	int i, size = points.size();
	TAD_POINT aux_point;
	for(i = 0; i < size; i++){
		aux_point = points[i];
		if(equalsPoint(points[i], point))return i;
	}
	return -1;
}