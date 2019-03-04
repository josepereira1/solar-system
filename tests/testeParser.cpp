#include <xmlParser.h>
#include <Point.h>

// para DEBUG
static void printPointsArray(TAD_ARRAY_LIST pontos) {
	for(int i=0; i<getArraySize(pontos); i++) {
		point2string((TAD_POINT) getElem(pontos, i));
	} 
}

int main()
{
	TAD_ARRAY_LIST pontos = getPointsFromFiles((char*)"file.xml");
    printPointsArray(pontos);
	return 0;
}