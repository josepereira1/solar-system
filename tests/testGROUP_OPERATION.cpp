#include <group.h>
#include <operation.h>
#include <iostream>

using namespace std;

int main () {
	Group g;
	Operation op = Operation('1',0,0,0,0);
	printf("%c\n", op.flag);
	g.operacoes.push_back(op);
	printf("%c\n", g.operacoes.back().flag);
	return 0;
}