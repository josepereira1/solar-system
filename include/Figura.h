#ifndef FIGURA_H
#define FIGURA_H

class Figura{
public:
	Figura(float*, int, float*, int, float*, int);
	float* points;
	int pointsTAM;
	float* normals;
	int normalsTAM;
	float* texCoords;
	int texCoordsTAM;
};

#endif
