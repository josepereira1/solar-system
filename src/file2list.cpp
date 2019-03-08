#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <ArrayList.h>
#include <file2list.h>
#include <Point.h>


static void openError(char* path) {
	char* errorMsg = (char*) malloc(sizeof(char)*(strlen(path)+21));
	sprintf(errorMsg, "could not open file %s", path);
	perror(errorMsg);
	free(errorMsg);
	exit(EXIT_FAILURE);
}


TAD_ARRAY_LIST file2list(char* path) {

	FILE* fd;
	if ( (fd = fopen(path, "r")) == NULL) { // abre o ficheiro para leitura apenas 
		openError(path);
	}
	
	int n_pontos;
	fscanf(fd, "%d\n", &n_pontos);

	TAD_ARRAY_LIST pontos = ARRAY_LIST(n_pontos);
	float x, y, z;
	for(int i=0; i < n_pontos; i++) { 
		fscanf(fd, "%f, %f, %f\n", &x, &y, &z);
		addElem(pontos, POINT(x, y, z));
	}

	return pontos;
}