#include <toFile.h>

#include <Point.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int save_indices(int indice, char* str, int deslocamento) {
	char* tmp = (char*) malloc(256);
	sprintf(tmp,"%d, ",indice);
	int len = strlen(tmp);
	sprintf(str+deslocamento,"%s",tmp);
	deslocamento += len;
	free(tmp);
	return deslocamento;
}

static int save_coordinates(TAD_POINT point, char* str, int deslocamento) {
	char* tmp = (char*) malloc(256);
	sprintf(tmp,"%.5f, %.5f, %.5f\n", getX(point), getY(point), getZ(point));
	int len = strlen(tmp);
	sprintf(str+deslocamento,"%s",tmp);
	deslocamento+=len;
	free(tmp);
	return deslocamento;
}

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

/*
void list2file(TAD_ARRAY_LIST points, const char* path) {
	FILE *file = fopen(path,"w");
	if (file != NULL) {
		int size = getArraySize(points);
		char* str = (char*) malloc(140 * size);//alloc memory to final string
		int deslocamento = 0;//displacement
		//put number of points
		char* tmp = (char*) malloc(256);
		sprintf(tmp,"%d\n",size);
		int len = strlen(tmp);
		sprintf(str+deslocamento,"%s",tmp);
		deslocamento+=len;
		free(tmp);
		//put the points (x,y,z)
		printf("%d\n", size);
		for(int i=0 ; i<size ; i++) {
			TAD_POINT point = (TAD_POINT) getElem(points,i);
			deslocamento = save_coordinates(point,str,deslocamento);
		}
		deslocamento--;
		sprintf(str+deslocamento,"%s","\0");
		//save on file
        fputs(str,file);
        //close the file
        fclose(file);
        //free the final string
		free(str);
	}
}
*/


#include <fromFile.h>

// c 
#include <math.h> 
// c++ 
#include <vector> 
#include <string>
#include <fstream>

using namespace std;


static float* createPolyBernstein(float p) {
	/* usamos a fórmula que está na BB */
	float* b = (float*) malloc(sizeof(float) * 4);
	b[0] = powf(1 - p, 3);
    b[1] = 3 * p * powf(1 - p, 2);
    b[2] = 3 * powf(p, 2) * (1 - p);
	b[3] = powf(p, 3);
	return b;
}


static TAD_POINT getBezierPoint(int** arrayPatchs, vector<TAD_POINT> cps, int numeroDoPatch, float u, float v) {
    
    float* bu = createPolyBernstein(u); // gerar o polinómio de Bernstein para o ponto U
    float* bv = createPolyBernstein(v); // gerar o polinómio de Bernstein para o ponto V

    float x = 0.0f, y = 0.0f, z = 0.0f; // ponto inicial

    /* fórmula usada:
     * B(u,v) = Bi(u) * Pij * Bj(v)
     */
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

        	int indiceNoPatch = i * 4 + j; 
            
            int indice_pc = arrayPatchs[numeroDoPatch][indiceNoPatch]; // indice do ponto de controlo
            TAD_POINT p = cps.at(indice_pc);
            x += bu[i] * getX(p) * bv[j];
            y += bu[i] * getY(p) * bv[j];
            z += bu[i] * getZ(p) * bv[j];
        }
    }

    return POINT(x, y, z);
}


void bezier2file(string patchFile, string outputFile, int tLevel) {

	int** arrayPatchs = NULL;
	vector<TAD_POINT> cps;
	readPatchFile(patchFile, &arrayPatchs, cps);

	vector<TAD_POINT> pontos;

	for (int i = 0; arrayPatchs[i] != (int*) NULL; i++) { // para cada patch
		
		for (int k = 0; k < tLevel; k++) { // k = tesselation V
			
			float v = (float)k / tLevel;
			
			for (int w = 0; w < tLevel; w++) { // w = tesselation U
				
				float u = (float)w / tLevel;

				TAD_POINT p1 = getBezierPoint(arrayPatchs, cps, i, u, v);
				TAD_POINT p2 = getBezierPoint(arrayPatchs, cps, i, (u + (1.0f / tLevel)), v);
				TAD_POINT p3 = getBezierPoint(arrayPatchs, cps, i, (u + (1.0f / tLevel)), (v + (1.0f / tLevel)));

				TAD_POINT p4 = getBezierPoint(arrayPatchs, cps, i, (u + (1.0f / tLevel)), (v + (1.0f / tLevel)));
				TAD_POINT p5 = getBezierPoint(arrayPatchs, cps, i, u, (v + (1.0f / tLevel)));
				TAD_POINT p6 = getBezierPoint(arrayPatchs, cps, i, u, v);

				pontos.push_back(p1);
				pontos.push_back(p2);
				pontos.push_back(p3);

				pontos.push_back(p4);
				pontos.push_back(p5);
				pontos.push_back(p6);
			}
		}
	}

	ofstream file (outputFile);
	if (file.is_open())
	{
		int len = pontos.size();
		file << len; // primeira linha do ficheiro
		
		for(int i=0; i<len; i++) {
			TAD_POINT p = pontos.at(i);
			file << "\n" << getX(p) << ", " << getY(p) << ", " << getZ(p); 
		}
		
		
		file.close();
	}
	else {
		perror("ERROR => could not open file!");
		exit(1);
	}
}
