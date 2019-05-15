#include <toFile.h>

#include <Point.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void list2file(TAD_ARRAY_LIST points, TAD_ARRAY_LIST normals, TAD_ARRAY_LIST texCoords, const char* path) {
	FILE *file = fopen(path, "w");
	
	if (file == NULL) {
		perror("Error => could not open file");
		exit(1);
	} 
	else {
		int dim = getArraySize(points);

		fprintf(file, "%d", dim); // imprime número de pontos

		for(i=0; i<dim; i++) { // imprime pontos
			TAD_POINT point = (TAD_POINT) getElem(points, i);
			fprintf(file, "\n%f, %f, %f", getX(point), getY(point), getZ(point));
		}

		//normais
		dim = getArraySize(normals);

		fprintf(file, "\n%d", dim); // imprime número de normais

		for(i=0; i<tam; i++) { // imprime normais
			TAD_POINT point = (TAD_POINT) getElem(normals, i);
			fprintf(file, "\n%f, %f, %f", getX(point), getY(point), getZ(point));
		}

		//Coordenadas de textura
		dim = getArraySize(texCoords);

		fprintf(file, "\n%d", dim); // imprime número de coordenadas de textura

		for(i=0; i<dim; i++) { // imprime coordenadas de textura
			TAD_POINT point = (TAD_POINT) getElem(texCoords, i);
			fprintf(file, "\n%f, %f", getX(point), getY(point));
		}
	}
}