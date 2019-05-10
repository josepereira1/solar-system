#ifndef FIGURA_H
#define FIGURA_H

class Figura{
public:
	Figura(int, unsigned int*, float*, int, unsigned int*, float*, int, unsigned int*, float*, int);
	int indicesTAM;
	unsigned int* indexPoints;
	float* points;
	int pointsTAM;
	unsigned int* indexNormals;
	float* normals;
	int normalsTAM;
	unsigned int* indexTexCoords;
	float* texCoords;
	int texCoordsTAM;
};

#endif
