#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <group.h>
#include <map>
#include <Figura.h>

void parse(Group &group, map<string,Figura> &figuras, const char* path);

#endif