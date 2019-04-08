#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <file2list.h>

static void openError(const char* path) {
	char* errorMsg = (char*) malloc(sizeof(char)*(strlen(path)+21));
	sprintf(errorMsg, "ERROR => could not open file %s", path);
	perror(errorMsg);
	free(errorMsg);
	exit(EXIT_FAILURE);
}


vector<float> file2list(const char* path) {

	FILE* fd;
	if((fd = fopen(path,"r")) == NULL) { // abre o ficheiro para leitura apenas 
		openError(path);
	}
	int n_pontos;
	fscanf(fd,"%d\n",&n_pontos);

	vector<float> pontos;
	float x, y, z;
	for(int i=0; i < n_pontos; i++) { 
		fscanf(fd, "%f, %f, %f\n", &x, &y, &z);
		pontos.push_back(x);
		pontos.push_back(y);
		pontos.push_back(z);
	}

	return pontos;
}