#include <stdio.h>
#include <ArrayList.h>
#include <Point.h>
#include <stdlib.h>

static void printPointsArray(TAD_ARRAY_LIST arr) {
	for(int i = 0; i < getArraySize(arr); i++){
    	point2string((TAD_POINT) getElem(arr, i));
  	}
}

int main(){

	// inicializar o TAD_ARRAY_LIST
	TAD_ARRAY_LIST arr = ARRAY_LIST(1);

	// adicionar TAD_POINT's ao TAD_ARRAY_LIST
	addElem(arr, POINT(1.0f, 2.0f, 3.0f));
	addElem(arr, POINT(4.0f, 5.0f, 6.0f));
	addElem(arr, POINT(7.0f, 8.0f, 9.0f));

	// imprimir o TAD_ARRAY_LIST
	printPointsArray(arr);
	
	// libertar a memória
	free_ARRAY_LIST(arr);

	return 0;
}