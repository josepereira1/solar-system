#include <toFile.h>

#include <Point.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void list2fileWindex(TAD_ARRAY_LIST points, int* indexPoints, TAD_ARRAY_LIST normals, int* indexNormals, TAD_ARRAY_LIST texCoords, int* indexTexCoords, int tam1, int tam2, int tam3, const char* path) {
	FILE *file = fopen(path, "w");
	
	if (file == NULL) {
		perror("Error => could not open file");
		exit(1);
	} 
	else {

		int i;

		//pontos

		fprintf(file, "%d\n", tam1); // imprime número de triangulos

		for(i=0; i<tam1-1; i++) { // imprime indíces
			fprintf(file, "%d, ", indexPoints[i]);
		}

		fprintf(file, "%d", indexPoints[i]); // último índice (para não ter vírgula)

		int dim = getArraySize(points);

		fprintf(file, "\n%d", dim); // imprime número de pontos

		for(i=0; i<dim; i++) { // imprime pontos
			TAD_POINT point = (TAD_POINT) getElem(points, i);
			fprintf(file, "\n%f, %f, %f", getX(point), getY(point), getZ(point));
		}

		//normais
		fprintf(file, "\n%d\n", tam2); // imprime número de triangulos

		for(i=0; i<tam2-1; i++) { // imprime indíces
			fprintf(file, "%d, ", indexNormals[i]);
		}

		fprintf(file, "%d", indexNormals[i]); // último índice (para não ter vírgula)

		dim = getArraySize(normals);

		fprintf(file, "\n%d", dim); // imprime número de normais

		for(i=0; i<dim; i++) { // imprime normais
			TAD_POINT point = (TAD_POINT) getElem(normals, i);
			fprintf(file, "\n%f, %f, %f", getX(point), getY(point), getZ(point));
		}

		//Coordenadas de textura
		fprintf(file, "\n%d\n", tam3); // imprime número de triangulos

		for(i=0; i<tam3-1; i++) { // imprime indíces
			fprintf(file, "%d, ", indexTexCoords[i]);
		}

		fprintf(file, "%d", indexTexCoords[i]); // último índice (para não ter vírgula)

		dim = getArraySize(texCoords);

		fprintf(file, "\n%d", dim); // imprime número de coordenadas de textura

		for(i=0; i<dim; i++) { // imprime coordenadas de textura
			TAD_POINT point = (TAD_POINT) getElem(texCoords, i);
			fprintf(file, "\n%f, %f", getX(point), getY(point));
		}
	}
}