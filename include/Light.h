#pragma once
class Light
{
public:
	Light();
	Light(char,float*,float*,float*,float*);
	char tipo;
	float* pos;
	float* diff;
	float* amb;
	float* spot;
};