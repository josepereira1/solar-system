#ifndef FIGURA_H
#define FIGURA_H

class Figura{
public:
	Figura(int, unsigned int*, float*, int, float*, int, float*, int);
	int indicesTAM;
	unsigned int* indexPoints;
	float* points;
	int pointsTAM;
	float* normals;
	int normalsTAM;
	float* texCoords; // GLuint*
	int texCoordsTAM;
};

#endif
