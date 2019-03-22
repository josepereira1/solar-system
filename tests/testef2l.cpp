#include <file2list.h>
#include <vector>
#include <stdio.h>

int main() {
	vector<float> pontos = file2list("box.3d");
	for(unsigned i = 0 ; i<pontos.size() ; i+=3) {
		printf("X=%f , Y=%f , Z=%f\n",pontos[i],pontos[i+1],pontos[i+2]);
	}
	return 0;
}