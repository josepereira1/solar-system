#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>	//	para ler os ficheiros patch
#include <iostream>
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
	ifstream infile(path);	//	abre o ficheiro

	string line;
	int numeroPatchs = 0, size = 0, i = 0, j = 0, numeroControlPoints = 0;
	char* ptr;

	getline(infile, line);	//	vais buscar a primeira linha

	numeroPatchs = atoi(line.c_str());

	//	numeroPatchs + 1, para colocar NULL na última linha
	*arrayPatchs = (int**)malloc((numeroPatchs+1)*sizeof(int*));	//	alocação da memória para o array que guarda os patchs

	(*arrayPatchs)[numeroPatchs] = (int*) NULL;	//	fim do array, para saber quando acaba

	//cout << "número de patchs = " << numeroPatchs << "\n";

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

	/*for(int i = 0; (*arrayPatchs)[i] != (int*) NULL; i++){	//	DEBUG
		for (int j = 0; (*arrayPatchs)[i][j] != -1; j++)
		{
			cout << (*arrayPatchs)[i][j] << " ";
		}

		cout << "\n";
	}*/

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