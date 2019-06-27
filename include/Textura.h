#ifndef TEXTURA_H
#define TEXTURA_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Textura{
public:
	Textura(GLuint);
	GLuint tex;
};

#endif