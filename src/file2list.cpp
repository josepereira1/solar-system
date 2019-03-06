#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <ArrayList.h>
#include <file2list.h>
#include <Point.h>

#define INITIAL_DIM			  1024


static int readLn(char* str);
static char* subStr(int start, int end, char* str);


static char* getfile(char* path, int* n_pontos) {
	int dim = 64;
	char* line = (char*) malloc(sizeof(char)*dim); // 64 bytes para o buffer inicial
	
	int fd;
	if ( (fd = open(path, O_RDONLY)) == -1) { // abre o ficheiro para leitura apenas 
		char* errorMsg = (char*) malloc(sizeof(char)*(strlen(path)+21));
		sprintf(errorMsg, "could not open file %s", path);
		perror(errorMsg);
		free(errorMsg);
		exit(1);
	}

	// lê a linha
	read(fd, line, dim); // lê 64 bytes
	int i = readLn(line); // dá o index do '\n'
	char* tmp = subStr(0, i, line); // saca o número de linhas
	free(line); 
	*n_pontos = atoi(tmp);
	free(tmp); 

	dim = 140 * (*n_pontos);
	tmp = (char*) malloc(sizeof(char) * dim); // criar o buffer com X bytes
	lseek(fd,0,SEEK_SET);
	read(fd, tmp, dim); // lê X bytes do ficheiro e coloca no buffer
	close(fd);
	
	// alocar apenas o que é necessário
	char* res = (char*) malloc( sizeof(char) * (strlen((char*)tmp)-i) ); 
	strcpy(res,(char*)tmp + i + 1);
	free(tmp);

	return res;
}


static int readLn(char* str) {
	int i;
	for(i=0; str[i] != '\0'; i++) {
		if (str[i] == '\n') break;
	}
	return i;
}


static char* subStr(int start, int end, char* str) {
	int len = end - start;
	char* res = (char*) malloc(sizeof(char)*(len+1));
	memcpy(res, str + start, len);
	res[len] = '\0';
	return res;
}


static void pontos2list(TAD_ARRAY_LIST arr, char* str){
	int start = 0, count = 1;
	float x, y, z;
	char* tmp;
	for(int i=0; ; i++) {
		if (str[i] == ',' || str[i] == '\0') {
			tmp = subStr(start, i, str);
			start = i + 2;
			if (count == 1) x = atof(tmp);
			else if (count == 2) y = atof(tmp);
			else if (count == 3) z = atof(tmp);
			free(tmp);
			if (str[i] == '\0') break;
			count++;
		}
	}
	addElem(arr, POINT(x, y, z));
}


TAD_ARRAY_LIST file2list(char* path) {

	int n_pontos = 0;
	char* buf = getfile(path, &n_pontos), *tmp; // puxa a info do ficheiro para uma string
	int currentIndex = 0, i;

	TAD_ARRAY_LIST pontos = ARRAY_LIST(INITIAL_DIM);
	for(int k=0; k < n_pontos; k++) { 
		i = readLn(buf + currentIndex); // lê a proxima linha
		tmp = subStr(currentIndex, currentIndex + i, buf); 
		//printf("%s\n", tmp);
		pontos2list(pontos, tmp);
		currentIndex += i + 1;
		free(tmp);
	}
	free(buf);

	return pontos;
}