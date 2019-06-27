#include <group.h>

using namespace std;

Group:: Group(){
	this->operacoes = vector<Operation>();
	this->ficheiros = vector<string>();
	this->texturas = vector<string>();
	this->materials = vector<TAD_POINT>();
	this->filhos = vector<Group>();
}
