#include <Figura.h>

Figura :: Figura(int indicesTAM, unsigned int* indexPoints, float* points, int pointsTAM, int indexNormalsTAM, unsigned int* indexNormals, float* normals, int normalsTAM,int indexTexCoordsTAM, unsigned int* indexTexCoords, float* texCoords, int texCoordsTAM){
	this->indicesTAM = indicesTAM;
	this->indexPoints = indexPoints;
	this->points = points;
	this->pointsTAM = pointsTAM;
	this->indexNormalsTAM = indexNormalsTAM;
	this->indexNormals = indexNormals;
	this->normals = normals;
	this->normalsTAM = normalsTAM;
	this->indexTexCoordsTAM = indexTexCoordsTAM;
	this->indexTexCoords = indexTexCoords;
	this->texCoords = texCoords;
	this->texCoordsTAM =  texCoordsTAM;
}
