#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int n = 0;

void design_sphere(int radius, int slices, int stacks, const char* patch) {

}

void design_plane(int side, const char* patch) {

}

void design_box(int x, int y, int z, int divisions, const char* patch) {
	if(divisions == 0) {

	}
	else {
		
	}
}

void design_cone(int radius, int height, int slices, int stacks, const char* patch) {

}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Insufficient parameters!\n");
		exit(1);
	}
	if(strcmp(argv[1],"sphere")==0) {
		if(argc < 6) {
			perror("Insufficient parameters to generate %s!\n",argv[1]);
			exit(1);
		}
		design_sphere(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
	}
	else if(strcmp(argv[1],"plane")==0) {
		if(argc < 4) {
			perror("Insufficient parameters to generate %s!\n",argv[1]);
			exit(1);
		}
		design_plane(atoi(argv[2]),argv[3]);
	}
	else if(strcmp(argv[1],"box")==0) {
		if(argc < 7) {
			perror("Insufficient parameters to generate %s!\n",argv[1]);
			exit(1);
		}
		if(argc < 6)
			design_box(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),0,argv[5]);
		else 
			design_box(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
	}
	else if(strcmp(argv[1],"cone")==0) {
		if(argc < 7) {
			perror("Insufficient parameters to generate %s!\n",argv[1]);
			exit(1);
		}
		design_cone(atoi(argv[2]),atoi(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
	}
	else {
		perror("Invalid geometric figure!\n");
		exit(2);
	}
	return 0;
}