#include "Light.h"


Light::Light() {
}

Light::Light(char tipo, float posX, float posY, float posZ, float posD, float diffX, float diffY, float diffZ, float diffD, float ambX, float ambY, float ambZ, float ambD, float spotX, float spotY, float spotZ){
	this->tipo = tipo;
	this->posX = posX;
	this->posY = posY;
	this->posZ = posZ;
	this->posD = posD;
	this->diffX = diffX;
	this->diffY = diffY;
	this->diffZ = diffZ;
	this->diffD = diffD;
	this->ambX = ambX;
	this->ambY = ambY;
	this->ambZ = ambZ;
	this->ambD = ambD;
	this->spotX = spotX;
	this->spotY = spotY;
	this->spotZ = spotZ;
}
