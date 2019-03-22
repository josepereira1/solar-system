#include <string>
#include <vector>
#include <iostream>
#include "operation.cpp"

using namespace std;


Group:: Group(){
	vector<Operation> operacoes;
	vector<string> ficheiros;
	vector<Group> filhos;
}

Group:: ~Group(){
	operacoes.clear();
	filhos.clear();
}
