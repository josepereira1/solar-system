#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>	//	para ler os ficheiros patch
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

#include <fromFile.h>
#include <Point.h>

static void openError(const char* path) {
	char* errorMsg = (char*) malloc(sizeof(char)*(strlen(path)+21));
	sprintf(errorMsg, "ERROR => could not open file %s", path);
	perror(errorMsg);
	free(errorMsg);
	exit(EXIT_FAILURE);
}


void readPatchFile(string path, int*** arrayPatchs, vector<TAD_POINT> &pontos){

	string line;
	int numeroPatchs = 0, size = 0, i = 0, j = 0, numeroControlPoints = 0;
	char* ptr;

	ifstream infile(path);	//	abre o ficheiro
	getline(infile, line);	//	vais buscar a primeira linha

	numeroPatchs = atoi(line.c_str());

	//	numeroPatchs + 1, para colocar NULL na última linha
	*arrayPatchs = (int**)malloc((numeroPatchs+1)*sizeof(int*));	//	alocação da memória para o array que guarda os patchs

	(*arrayPatchs)[numeroPatchs] = (int*) NULL;	//	fim do array, para saber quando acaba

	for(i = 0; i < numeroPatchs; i++){
		getline(infile,line);
		size = count(line.begin(),line.end(), ',') + 1;
		//cout << i << "-" << line << " - size = " << size << "\n";

		(*arrayPatchs)[i] = (int*)malloc((size+1)*sizeof(int));	//	última posição vai ter um NULL para saber quando acaba
		(*arrayPatchs)[i][size] = -1;	//	para saber quando é a última linha

		char* init = (char*) line.c_str();	//	transforma a string num char*

		for(j = 0; (ptr = strstr(init, ",")) != NULL ; j++){	//	encontra o apontador da ","
			char* tmp = ptr + sizeof(char);		//	guarda temporariamente a posição a seguir à vírgula, isto é, o apontador para o próximo número
			*ptr = '\0';	//	fim da número, para o atoi saber onde termina a string
			(*arrayPatchs)[i][j] = atoi(init);	//	converte o char* num int
			init = tmp;	//	atribuí-se a init o ínicio do próximo número
		}

		(*arrayPatchs)[i][j] = atoi(init);	//	para o último indice, pq não tem vírgula
	}

	getline(infile,line);

	numeroControlPoints = atoi(line.c_str());

	float arr[3];

	for(i = 0; i < numeroControlPoints; i++){
		getline(infile,line);

		char* init = (char*) line.c_str();	//	transforma a string num char*

		for(j = 0; (ptr = strstr(init, ",")) != NULL ; j++){	//	encontra o apontador da ","
			char* tmp = ptr + sizeof(char);		//	guarda temporariamente a posição a seguir à vírgula, isto é, o apontador para o próximo número
			*ptr = '\0';	//	fim da número, para o atoi saber onde termina a string
			arr[j] = atof(init);	//	converte o char* num int
			init = tmp;	//	atribuí-se a init o ínicio do próximo número
		}

		arr[j] = atof(init);

		TAD_POINT ponto = POINT(arr[0],arr[1],arr[2]);

		pontos.push_back(ponto);
	}
}


void file2list(string path, unsigned int** indices, int* indicesTAM, float** vertexB, int* vertexBTAM) {
	string line;
	float x, y, z;
	char* ptr;
	int i, index=0;
	
	ifstream infile(path);	//	abre o ficheiro
	
	getline(infile, line);	//	vai buscar a primeira linha
	*indicesTAM = atoi(line.c_str()); 
    printf("indicesTAM=%d\n",*indicesTAM );
	getline(infile, line);	//	vai buscar a segunda linha
	char* init = (char*) line.c_str();
	*indices = (unsigned int*) malloc(sizeof(unsigned int) * (*indicesTAM));
	for(i = 0; (ptr = strstr(init, ",")) != NULL ; i++){	//	encontra o apontador da ","
		char* tmp = ptr + sizeof(char);		//	guarda temporariamente a posição a seguir à vírgula, isto é, o apontador para o próximo número
		*ptr = '\0';	//	fim da número, para o atoi saber onde termina a string
		printf("%s\n",init );
		(*indices)[i] = (atoi(init)-1);//	converte o char* num int
		init = tmp;	//	atribuí-se a init o ínicio do próximo número
	}
	(*indices)[i] = atoi(init); // por causa do último número não ter ','
	getline(infile, line);	
	*vertexBTAM = atoi(line.c_str()); 
	printf("vertexBTAM=%d\n",*vertexBTAM);
	*vertexB = (float*) malloc(sizeof(float) * (3*(*vertexBTAM)));
	for(int k=0; k < *vertexBTAM; k++) {
		getline(infile, line);	//	vai buscar a segunda linha
		init = (char*) line.c_str();
		for(i = 0; (ptr = strstr(init, ",")) != NULL ; i++){	//	encontra o apontador da ","
			char* tmp=init;		//	guarda temporariamente a posição a seguir à vírgula, isto é, o apontador para o próximo número
			(*ptr) = '\0';	        //	fim da número, para o atoi saber onde termina a string
			(*vertexB)[index++] = atof(tmp);//	converte o char* num int
			init = ptr+1;	//	atribuí-se a init o ínicio do próximo número
		}
		(*vertexB)[index++] = atof(init); // por causa do último número não ter ','
	}
	(*vertexBTAM) = index;
}









