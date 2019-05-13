#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include <operation.h>
#include <Point.h>

using namespace std;

class Group{
public:
	Group();
	vector<Operation> operacoes;
	vector<string> ficheiros;
	vector<string> texturas;
	vector<TAD_POINT> materials;
	vector<Group> filhos;
};

#endif