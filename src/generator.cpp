#include <stdio.h>
#include <stdlib.h>

#include <ArrayList.h>
#include <Point.h>
#include <list2file.h>

//	generators:
#include <coneGenerator.h>
#include <boxGenerator.h>
#include <sphereGenerator.h>
#include <planeGenerator.h>

#include <fstream>	//	para ler os ficheiros patch
#include <iostream>
#include <stdlib.h>

#include <vector>


//unsigned int** patches, float** controlPoints, char* path, int numberOfIndexes

using namespace std;

void readPatchFile(string path, int*** arrayPatchs, vector<TAD_POINT> &pontos){
	ifstream infile(path);	//	abre o ficheiro

	string line;
	int numeroPatchs = 0, size = 0, i = 0, j = 0, index = 0, numeroControlPoints = 0;
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


void write_on_file(const char* data, const char* path) {
	FILE *fp = fopen(path, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

void printInstructions(){
	const char* str = "\nType the following commands on terminal to generate points to:\nplane -> generator plane side name_file.3d\nbox -> generator box x y z divisions name_file.3d\nsphere -> generator sphere radius slices stacks name_file.3d\ncone -> generator cone radius height slices stacks name_file.3d\n";
	puts(str);
}

void write_points_to_file(TAD_ARRAY_LIST points, const char* path){
	list2file(points, path);
}

void design_sphere(float radius, int slices, int stacks, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfSphere(radius,slices,stacks);
	write_points_to_file(points,patch);
}

void design_plane(float side, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfPlane(side);
	write_points_to_file(points,patch);	
}

void design_box(float x, float y, float z, int divisions, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfBox(x, y, z, divisions);
	write_points_to_file(points,patch);
}

void design_cone(float radius, float height, int slices, int stacks, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfCone(radius, height, slices, stacks);
	write_points_to_file(points,patch);
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Insufficient parameters!\n");
		exit(1);
	}
	if(strcmp(argv[1],"sphere")==0) {
		if(argc != 6) {
			perror("Invalid parameters to generate sphere!\n");
			exit(1);
		}
		design_sphere(atof(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
	}
	else if(strcmp(argv[1],"plane")==0) {
		if(argc != 4) {
			perror("Invalid parameters to generate plane!\n");
			exit(1);
		}
		design_plane(atof(argv[2]),argv[3]);
	}
	else if(strcmp(argv[1],"box")==0) {
		if(argc < 7 || argc > 8) {
			perror("Invalid parameters to generate box!\n");
			exit(1);
		}
		if(argc < 6)
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),0,argv[5]);
		else 
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),atoi(argv[5]),argv[6]);
	}
	else if(strcmp(argv[1],"cone")==0) {
		if(argc < 7) {
			perror("Invalid parameters to generate cone!\n");
			exit(1);
		}
		design_cone(atof(argv[2]),atof(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
	}else if(strcmp(argv[1],"help")==0) {
		if(argc != 2) {
			perror("Invalid parameters to help!\n");
			exit(1);
		}
		printInstructions();
	}else {
		readPatchFile();
		perror("Invalid geometric figure!\n");
		exit(2);
	}

	/*int** arrayPatchs = NULL;
	vector<TAD_POINT> pontos;

	readPatchFile("teapot.patch", &arrayPatchs, pontos);

	int size = pontos.size();

	for(int i = 0; arrayPatchs[i] != (int*) NULL; i++){	//	DEBUG
		for (int j = 0; arrayPatchs[i][j] != -1; j++)
		{
			cout << arrayPatchs[i][j] << " ";
		}

		cout << "\n";
	}

	for(int i = 0; i < size; i++){
		TAD_POINT ponto = pontos.at(i);
		printf("%.2f %.2f %.2f\n", getX(ponto), getY(ponto), getZ(ponto));
	}*/
	
	return 0;
}












