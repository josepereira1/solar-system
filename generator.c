<<<<<<< HEAD
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
=======
>>>>>>> a82a83077c39d7483459c55869a2ceb5ac8e19fd

void write_on_file(const char* data, const char* path) {

	FILE *fp = fopen(path, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

void design_sphere(float radius, int slices, int stacks, const char* patch) {

}

void design_plane(float side, const char* patch) {
	float c = side / 2.0;
    char* str = malloc(sizeof(char)*1024*1024);
    sprintf(str,"2\n1 2 3\n1 3 4\n4\n %.5f, 0.0, -%.5f\n-%.5f, 0.0, -%.5f\n-%.5f, 0.0,  %.5f\n %.5f, 0.0,  %.5f \n",c,c,c,c,c,c,c,c);
    write_on_file(str,patch);
}

void design_box(float x, float y, float z, int divisions, const char* patch) {
	if(divisions == 0) {

	}
	else {
		
	}
}

void design_cone(float radius, float height, int slices, int stacks, const char* patch) {
	float angle = (2*M_PI)/slices;
	int i, j;
	for(j = 0, i = 0; i < slices; i++){

		//	APENAS PARA DEBUG!!!
		printf("Ponto %d: x = %f | y = %f | z = %f\n\n", j++, radius*sin(angle*i), 0.0, radius*cos(angle*i));
		printf("Ponto %d: x = %f | y = %f | z = %f\n\n", j++, 0.0, 0.0, 0.0);
		printf("Ponto %d: x = %f | y = %f | z = %f\n\n", j++, radius*sin(angle*(i+1)), 0.0, radius*cos(angle*(i+1)));
		//	--------------------------------------------------------------------------------------------
		printf("Ponto %d: x = %f | y = %f | z = %f\n\n", j++, radius*sin(angle*(i+1)), 0.0, radius*cos(angle*(i+1)));
		printf("Ponto %d: x = %f | y = %f | z = %f\n\n", j++, 0.0, height, 0.0);
		printf("Ponto %d: x = %f | y = %f | z = %f\n\n", j++, radius*sin(angle*i), 0.0, radius*cos(angle*i));
	}
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Insufficient parameters!\n");
		exit(1);
	}
	if(strcmp(argv[1],"sphere")==0) {
		if(argc < 6) {
			perror("Insufficient parameters to generate sphere!\n");
			exit(1);
		}
		design_sphere(atof(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
	}
	else if(strcmp(argv[1],"plane")==0) {
		if(argc < 4) {
			perror("Insufficient parameters to generate plane!\n");
			exit(1);
		}
		design_plane(atof(argv[2]),argv[3]);
	}
	else if(strcmp(argv[1],"box")==0) {
		if(argc < 7) {
			perror("Insufficient parameters to generate box!\n");
			exit(1);
		}
		if(argc < 6)
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),0,argv[5]);
		else 
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),atoi(argv[5]),argv[6]);
	}
	else if(strcmp(argv[1],"cone")==0) {
		if(argc < 7) {
			perror("Insufficient parameters to generate cone!\n");
			exit(1);
		}
		design_cone(atof(argv[2]),atof(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
	}
	else {
		perror("Invalid geometric figure!\n");
		exit(2);
	}
	design_cone(3,3,10,0,"");
	return 0;
}