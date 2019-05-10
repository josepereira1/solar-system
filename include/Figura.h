#ifndef FIGURA_H
#define FIGURA_H

class Figura{
public:
	Figura(int, unsigned int*, float*, int, unsigned int*, float*, int, unsigned int*, float*, int, GLuint,int);
	int indicesTAM;
	unsigned int* indexPoints;
	float* points;
	int pointsTAM;
	unsigned int* indexNormals;
	float* normals;
	int normalsTAM;
	GLuint texCoords;
	int texCoordsTAM;
};

#endif
