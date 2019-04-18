#include <stdio.h>
#include <fromFile.h>
#include <string>

int main()
{
	unsigned int* indices;
	int indicesTAM;  
	float* vertexB;   
	int vertexBTAM;  

	file2list("teste.3d", &indices, &indicesTAM, &vertexB, &vertexBTAM);

	for(int i=0; i<indicesTAM; i++) {
		printf("%d ", indices[i]);
	}

	putchar('\n');

	for(int i=0; i<vertexBTAM; i++) {
		printf("%.2f ", vertexB[i]);
	}

	putchar('\n');

	return 0;
}