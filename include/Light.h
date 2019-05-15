#ifndef LIGHT_H
#define LIGHT_H

class Light
{
public:
	Light();
	Light(char,float,float,float,float, float, float, float, float, float, float, float, float, float, float, float);
	char tipo;
	float posX;
	float posY;
	float posZ;
	float posD;
	float diffX;
	float diffY;
	float diffZ;
	float diffD;
	float ambX;
	float ambY;
	float ambZ;
	float ambD;
	float spotX;
	float spotY;
	float spotZ;
};

#endif