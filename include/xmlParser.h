#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <group.h>
#include <map>
#include <vector>
#include <string>
#include <Figura.h>

void parse(Group &group, map<string,Figura> &figuras, vector<string> textures, int* nGrupos, const char* path);

#endif