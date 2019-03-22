#include <group.h>
#include <operation.h>
#include <iostream>

using namespace std;

int main () {
	Group g;
	Operation op = Operation('1',0,0,0,0);
	cout << op.flag + "\n";
	g.operacoes.push_back(op);
	for(vector<Operation>::iterator it = g.operacoes.begin(); it!=g.operacoes.end() ; it++)
		cout << *it << "\n";
	cout << g.operacoes.back().flag + "\n";
	return 0;
}