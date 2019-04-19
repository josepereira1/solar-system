#ifndef FIGURA_H
#define FIGURA_H
#include <vector>
#include <cstdlib>

using namespace std;

class Figura{
public:
	unsigned int* indices;
	int indicesTAM;

	float* vertexB;
	int vertexBTAM;
	
	Figura();
	~Figura();
};

#endif
