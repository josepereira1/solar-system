#include <vector>
#include <Figura.h>

using namespace std;

Figura:: Figura(){
	this->indices = NULL;
	this->indicesTAM = 0;

	this->vertexB = NULL;
	this->vertexBTAM = 0;
}

Figura:: ~Figura(){
	free(indices);
	free(vertexB);
}