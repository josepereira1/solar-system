#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ArrayList.h>
#include <Point.h>
#include <toFile.h>

//	generators
#include <coneGenerator.h>
#include <boxGenerator.h>
#include <sphereGenerator.h>
#include <planeGenerator.h>

// bezier
#include <bezierCreater.h>


static void printInstructions(){
	const char* str = "\nType the following commands on terminal to generate points to:\nplane -> generator plane side name_file.3d\nbox -> generator box x y z divisions name_file.3d\nsphere -> generator sphere radius slices stacks name_file.3d\ncone -> generator cone radius height slices stacks name_file.3d\n";
	puts(str);
}

void design_sphere(float radius, int slices, int stacks, const char* patch) {
	TAD_ARRAY_LIST normals;
	TAD_ARRAY_LIST texCoords;
	TAD_ARRAY_LIST points = getPointsOfSphere(radius,slices,stacks,&normals, &texCoords);
	list2file(points,normals,texCoords,patch);
}

void design_plane(float side, const char* patch) {
	TAD_ARRAY_LIST normals;
	TAD_ARRAY_LIST texCoords;
	TAD_ARRAY_LIST points = getPointsOfPlane(side, &normals, &texCoords);
	list2file(points,normals,texCoords,patch);	
}

void design_box(float x, float y, float z, int divisions, const char* patch) {
	TAD_ARRAY_LIST normals;
	TAD_ARRAY_LIST texCoords;
	TAD_ARRAY_LIST points = getPointsOfBox(x, y, z, divisions, &normals, &texCoords);
	list2file(points,normals,texCoords,patch);
}

void design_cone(float radius, float height, int slices, int stacks, const char* patch) {
	TAD_ARRAY_LIST normals;
	TAD_ARRAY_LIST texCoords;
	TAD_ARRAY_LIST points = getPointsOfCone(radius, height, slices, stacks,&normals,&texCoords);
	list2file(points,normals,texCoords,patch);
}

void create_bezier(const char* patch, const char* path, int tesselation) {
	TAD_ARRAY_LIST normals;
	TAD_ARRAY_LIST texCoords;
	TAD_ARRAY_LIST points = getPointsOfBezier(patch,tesselation,&normals,&texCoords);
	list2file(points,normals,texCoords,path);
}

int main(int argc, char** argv) {
	if(argc <= 1) {
		perror("Insufficient parameters!\n");
		exit(1);
	}
	if(strcmp(argv[1],"sphere")==0) {
		if(argc != 6) {
			perror("Invalid parameters to generate sphere!\n");
			exit(1);
		}
		design_sphere(atof(argv[2]),atoi(argv[3]),atoi(argv[4]),argv[5]);
	}
	else if(strcmp(argv[1],"plane")==0) {
		if(argc != 4) {
			perror("Invalid parameters to generate plane!\n");
			exit(1);
		}
		design_plane(atof(argv[2]),argv[3]);
	}
	else if(strcmp(argv[1],"box")==0) {
		if(argc < 6 || argc > 8) {
			perror("Invalid parameters to generate box!\n");
			exit(1);
		}
		if(argc == 6)
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),0,argv[5]);
		else 
			design_box(atof(argv[2]),atof(argv[3]),atof(argv[4]),atoi(argv[5]),argv[6]);
	}
	else if(strcmp(argv[1],"cone")==0) {
		if(argc != 7) {
			perror("Invalid parameters to generate cone!\n");
			exit(1);
		}
		design_cone(atof(argv[2]),atof(argv[3]),atoi(argv[4]),atoi(argv[5]),argv[6]);
	}
	else if(strcmp(argv[1],"help")==0) {
		if(argc != 2) {
			perror("Invalid parameters to help!\n");
			exit(1);
		}
		printInstructions();
	}
	else if(strcmp(argv[1],"bezier")==0) {

		//   0     1       2    3    4
		// argv0 bezier .patch .3d tLevel

		if(argc != 5) { 
 			perror("Invalid parameters to bezier!\n");
			exit(1);
		}
		//bexier2file(argv[2],argv[3],atoi(argv[4]));
		create_bezier(argv[2],argv[3],atoi(argv[4]));
	}
	else {
		perror("Invalid geometric figure!\n");
		exit(2);
	}
	return 0;
}