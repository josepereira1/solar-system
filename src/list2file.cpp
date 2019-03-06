#include "list2file.h"

int save_coordinates(TAD_POINT point, char* str, int deslocamento) {
	char* tmp = (char*) malloc(256);
	sprintf(tmp,"%.5f, %.5f, %.5f\n", getX(point),getY(point),getZ(point));
	len = strlen(tmp);
	sprintf(str+deslocamento,"%s",tmp);
	deslocamento+=len;
	free(tmp);
	return deslocamento;
}

void list2file(TAD_ARRAY_LIST points, const char* path) {
	FILE *file = fopen(path,"w");
	if (file != NULL) {
		char* str = (char*) malloc(1024*1024*10);//alloc memory to final string
		int deslocamento = 0;//displacement
		//put number of points
		int size = getArraySize(points);
		char* tmp = (char*) malloc(256);
		sprintf(tmp,"%d\n",size);
		int len = strlen(tmp);
		sprintf(str+deslocamento,"%s",tmp);
		deslocamento+=len;
		free(tmp);
		//put the points (x,y,z)
		for(int i=0 ; i<size ; i++) {
			TAD_POINT point = (TAD_POINT) getElem(points,i);
			deslocamento = save_coordinates(point,str,deslocamento);
		}
		deslocamento--;
		sprintf(str+deslocamento,"\0");
		//save on file
        fputs(str,file);
        //close the file
        fclose(file);
        //free the final string
		free(str);
	}
}