#include <string>
#include <vector>
#include <iostream>
#include "operation.cpp"

using namespace std;

class Group{
public:
	Group();
	~Group();
	vector<OPERATION> operacoes;
	vector<string> ficheiros;
	vector<GROUP> filhos;
};