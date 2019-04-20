#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <group.h>
#include <map>
#include <Figura.h>

void parse(Group &group, map<string,Figura> &figuras,int* nGrupos, const char* path);

#endif