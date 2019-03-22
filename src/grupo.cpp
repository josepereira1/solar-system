#include <string>
#include <vector>
#include <iostream>
#include "operacao.cpp"

using namespace std;

class GROUP{
public:
	GROUP();
	~GROUP();
	vector<OPERATION> operacoes;
	vector<string> ficheiros;
	vector<GROUP> filhos;
};

GROUP:: GROUP(){
	vector<OPERATION> operacoes;
	vector<string> ficheiros;
	vector<GROUP> filhos;
}

GROUP:: ~GROUP(){
	operacoes.clear();
	filhos.clear();
}
/*
int main (){
	GROUP g;
	OPERATION o('t',1.0,1.0,1.0,1.0);
	g.operacoes.push_back(o);
	char t = g.operacoes.back().flag;
	printf("%c\n",t );
}*/
