#include <string>
#include <vector>
#include <group.h>
#include <operation.h>

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
