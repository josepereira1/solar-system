#include <Figura.h>
#include <string>
#include <map>


int main(void){

	std::map<std::string,Figura> figuras;

	Figura cone = Figura(),sphere = Figura();

	std::vector<float> pontos;

	pontos.push_back(1.0);
	pontos.push_back(2.0);
	pontos.push_back(3.0);
	pontos.push_back(4.0);

	cone.pontos = pontos;
	sphere.pontos = pontos;

	figuras["cone.3d"] = cone;
	figuras["sphere.3d"] = sphere;

	printf("teste\n");

	for(unsigned i = 0; i < figuras["cone.3d"].pontos.size() ; i++){
		printf("%.2f\n",figuras["cone.3d"].pontos[i]);
		printf("%.2f\n",figuras["sphere.3d"].pontos[i]);
	}



	return 0;
}