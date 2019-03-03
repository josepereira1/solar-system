#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include <ArrayList.h>
#include <file2list.h>
#include <Point.h>

#define INITIAL_DIM				50
#define 		  B			     1
#define 		 KB         1024*B
#define 		 MB		   1024*KB

static char* getfile(const char* path) {
	void* tmp = malloc(MB); // criar o buffer com 1 MB
	int fd = open(path, O_RDONLY); // abre o ficheiro para leitura apenas 
	read(fd, tmp, MB); // lê 1 MB do ficheiro e coloca no buffer
	char* res = malloc(sizeof(char) * strlen(tmp)); 
	strcpy(res,tmp);
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
	char* res = malloc(sizeof(char)*(len+1));
	memcpy(res, str + start, len);
	res[len] = '\0';
	return res;
}


static void indices2list(TAD_ARRAY_LIST arr, char* str){
	int start = 0;
	char* tmp;
	for(int i=0; ; i++) {
		if (str[i] == ',' || str[i] == '\0') {
			tmp = subStr(start, i, str);
			start = i + 2;
			int* n = malloc(sizeof(int));
			*n = atoi(tmp);
			addElem(arr, n);
			free(tmp);
			if (str[i] == '\0') break;
		}
	}
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


TAD_ARRAY_LIST file2list(const char* path) {
	
	char* buf = getfile(path), *tmp; // puxa a info do ficheiro para uma string
	int currentIndex = 0, i;

	i = readLn(buf);
	tmp = subStr(0, i, buf); 
	int n_patches = atoi(tmp); // número de patches
	currentIndex += i + 1; // i + '\n'
	free(tmp); 

	TAD_ARRAY_LIST indices = ARRAY_LIST(INITIAL_DIM);
	for(int k=0; k < n_patches; k++) { 
		i = readLn(buf + currentIndex); // lê a proxima linha
		tmp = subStr(currentIndex, currentIndex + i, buf); 
		currentIndex += i + 1;
		indices2list(indices, tmp);
		free(tmp);
	}

	i = readLn(buf + currentIndex); // lê a proxima linha
	tmp = subStr(currentIndex, currentIndex + i, buf); 
	int n_pontos = atoi(tmp); // número de patches
	currentIndex += i + 1;
	free(tmp); 

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

	TAD_ARRAY_LIST res = ARRAY_LIST(INITIAL_DIM);
	for(i=0; i < getArraySize(indices); i++){
    	int indice = *(int*) getElem(indices, i);
    	TAD_POINT ponto = (TAD_POINT) getElem(pontos, indice);
    	addElem(res, ponto);
  	}
  	for(i = 0; i < getArraySize(indices); i++){
    	int* n = (int*) getElem(indices, i);
    	free(n);
  	}
  	free_ARRAY_LIST(indices);
  	free_ARRAY_LIST(pontos);

	return res;
}