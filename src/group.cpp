#include <string>
#include <vector>
#include <group.h>
#include <operation.h>

using namespace std;

Group:: Group(){
	this->operacoes = vector<Operation>();
	this->ficheiros = vector<string>();
	this->texturas = vector<string>();
	this->filhos = vector<Group>();
}
