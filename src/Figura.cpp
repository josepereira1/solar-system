#include <Figura.h>

Figura :: Figura (float* points, int pointsTAM, float* normals, int normalsTAM, float* texCoords, int texCoordsTAM){
	this->points = points;
	this->pointsTAM = pointsTAM;
	this->normals = normals;
	this->normalsTAM = normalsTAM;
	this->texCoords = texCoords;
	this->texCoordsTAM =  texCoordsTAM;
}
