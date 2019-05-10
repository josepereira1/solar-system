#include <Figura.h>

Figura :: Figura(int indicesTAM, unsigned int* indexPoints, float* points, int pointsTAM, float* normals, int normalsTAM, float* texCoords, int texCoordsTAM){
	this->indicesTAM = indicesTAM;
	this->indexPoints = indexPoints;
	this->points = points;
	this->pointsTAM = pointsTAM;
	this->normals = normals;
	this->normalsTAM = normalsTAM;
	this->texCoords = texCoords;
	this->texCoordsTAM =  texCoordsTAM;
}
