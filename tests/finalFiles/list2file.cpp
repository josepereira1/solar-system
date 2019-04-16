#include "list2file.h"

void list2file(TAD_ARRAY_LIST points, int positions[], int tam, const char* path) {
	FILE *file = fopen(path,"ab");
	if (file != NULL) {
		char* str = malloc(1024*1024*10);//alloc memory to final string
		int deslocamento = 0;//displacement
		//put number of triangles
		char* tmp = malloc(256);
		sprintf(tmp,"%d\n",tam/3);
		int len = strlen(tmp);
		sprintf(str,"%s",tmp);
		deslocamento += len;
		free(tmp);
		//put the positions
		for(int i=0 ; i<tam ; i+=3) {
			char* tmp2 = malloc(256);
			sprintf(tmp2,"%d, %d, %d\n",positions[i],positions[i+1],positions[i+2]);
			len = strlen(tmp2);
			sprintf(str+deslocamento,"%s",tmp2);
			deslocamento+=len;
			free(tmp2);
		}
		int size = getArraySize(points);
		//put number of points
		char* tmp3 = malloc(256);
		sprintf(tmp3,"%d\n",size);
		len = strlen(tmp3);
		sprintf(str+deslocamento,"%s",tmp3);
		deslocamento+=len;
		free(tmp3);
		//put the points (x,y,z)
		for(int i=0 ; i<size ; i++) {
			TAD_POINT point = getElem(points,i);
			char* tmp4 = malloc(256);
			sprintf(tmp4,"%.5f, %.5f, %.5f\n",getX(point),getY(point),getZ(point));
			len = strlen(tmp4);
			sprintf(str+deslocamento,"%s",tmp4);
			deslocamento+=len;
			free(tmp4);
		}
		//save on file
        fputs(str,file);
        //close the file
        fclose(file);
        //free the final string
		free(str);
	}
} 