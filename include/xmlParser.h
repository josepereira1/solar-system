#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "../toolkits/devil/IL/il.h"
#include "../devil/IL/il.h"
#include <group.h>
#include <map>
#include <vector>
#include <string>
#include <Figura.h>
#include <Textura.h>
#include <OpenGL/gl.h>
#include <Light.h>

int loadTexture(string s);
void parse(Group &group, map<string,Figura> &figuras, map<string,Textura> &textures, int* nGrupos, const char* path);

#endif
