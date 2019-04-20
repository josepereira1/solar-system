#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include <operation.h>

using namespace std;

class Group{
public:
	Group();
	vector<Operation> operacoes;
	vector<string> ficheiros;
	vector<Group> filhos;
};

#endif