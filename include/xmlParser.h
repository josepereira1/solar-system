#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <group.h>
#include <map>
#include <vector>
#include <string>
#include <Figura.h>
#include <Textura.h>
#include <Light.h>

void parse(Group &group, vector<Light> &light, map<string,Figura> &figuras, map<string,Textura> &textures, int* nGrupos, const char* path);

#endif