#include <toFile.h>

#include <Point.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void list2fileWindex(TAD_ARRAY_LIST points, int* indices, int tam, const char* path) {
	FILE *file = fopen(path, "w");
	
	if (file == NULL) {
		perror("Error => could not open file");
		exit(1);
	} 
	else {

		int i;

		fprintf(file, "%d\n", tam); // imprime número de indíces 

		for(i=0; i<tam-1; i++) { // imprime indíces
			fprintf(file, "%d, ", indices[i]);
		}

		fprintf(file, "%d", indices[i]); // último índice (para não ter vírgula)

		int dim = getArraySize(points);

		fprintf(file, "\n%d", dim); // imprime número de pontos

		for(i=0; i<dim; i++) { // imprime pontos
			TAD_POINT point = (TAD_POINT) getElem(points, i);
			fprintf(file, "\n%f, %f, %f", getX(point), getY(point), getZ(point));
		}
	}
}