#include <Figura.h>

Figura :: Figura(int indicesTAM, unsigned int* indexPoints, float* points, int pointsTAM, unsigned int* indexNormals, float* normals, int normalsTAM, unsigned int* indexTexCoords, float* texCoords, int texCoordsTAM){
	this->indicesTAM = indicesTAM;
	this->indexPoints = indexPoints;
	this->points = points;
	this->pointsTAM = pointsTAM;
	this->indexNormals = indexNormals;
	this->normals = normals;
	this->normalsTAM = normalsTAM;
	this->indexTexCoords = indexTexCoords;
	this->texCoords = texCoords;
	this->texCoordsTAM =  texCoordsTAM;
}
