#include "Light.h"


Light::Light() {
}

Light::Light(char tipo, float* pos, float* diff, float* amb, float* spot){
	this->tipo = tipo;
	this->pos = pos;
	this->diff = diff;
	this->amb = amb;
	this->spot = spot;
}
