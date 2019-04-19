#include <filterPoints.h>
#include <ArrayList.h>
#include <Point.h>
#include <stdio.h>
	
void init(TAD_ARRAY_LIST arrayList){
	TAD_POINT point1, point2, point3, point4, point5, point6, point7, point8, point9;
	
	point1 = POINT(1,1,1);
	point2 = POINT(1,1,1);
	point3 = POINT(3,3,3);
	point4 = POINT(3,5,3);
	point5 = POINT(1,5,3);
	point6 = POINT(2,5,3);
	point7 = POINT(3,5,3);
	point8 = POINT(4,5,3);
	point9 = POINT(1,1,1);
	
	addElem(arrayList, point1);
	addElem(arrayList, point2);
	addElem(arrayList, point3);
	addElem(arrayList, point4);
	addElem(arrayList, point5);
	/*addElem(arrayList, point6);
	addElem(arrayList, point7);
	addElem(arrayList, point8);
	addElem(arrayList, point9);*/
}
	
void print(TAD_ARRAY_LIST arrayList){
	for(int i = 0; i < getArraySize(arrayList); i++){
		point2string((TAD_POINT) getElem(arrayList,i));
	}
		printf("\n\n");
}
	
void printPositions(int* positions, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", positions[i]);
	}
	printf("\n\n");
}
	
	
int main(void){
	
	TAD_ARRAY_LIST arrayList = ARRAY_LIST(50);
	
	init(arrayList);
	
	TAD_ARRAY_LIST res;
	
	int *positions;
	
	print(arrayList);

	filter(arrayList, &res, &positions);
	
	print(res);	//	print sem os repetidos
	
	int size1 = getArraySize(res);
	
	printPositions(positions,size1);	//	print dos índices
	
	return 0;
}