#include <fromFile.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	unsigned int* indices;
	float* vertexB;
	int tam1 = 0, tam2 = 0;

	std::string str = std::string("exemplo.patch");

	file2list(str,&indices,&tam1,&vertexB,&tam2);

	printf("TAMANHO DO indices=%d\n", tam1);

	printf("TAMANHO DO vertexB=%d\n", tam2);

	printf("INDICES:\n");

	for(int i = 0; i < tam1; i++)
		printf("%d ", indices[i]);

	printf("\n");

	printf("CONTROL POINTS:\n");

	for(int j = 0; j < tam2; ){
		printf("%.2f %.2f %.2f\n", vertexB[j+0], vertexB[j+1], vertexB[j+2]);
		j += 3;
	}

	return 0;
}