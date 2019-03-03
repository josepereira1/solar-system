#include <stdio.h>
#include <stdlib.h>

#include <ArrayList.h>
#include <Point.h>
#include <list2file.h>
#include <filterPoints.h>

//	generators:
#include <coneGenerator.h>
#include <boxGenerator.h>
#include <sphereGenerator.h>
#include <planeGenerator.h>


void write_on_file(const char* data, const char* path) {

	FILE *fp = fopen(path, "w");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}

void write_points_to_file(TAD_ARRAY_LIST points, const char* patch){
	TAD_ARRAY_LIST withoutRepeated;
	int *positions, size;

	filter(points, &withoutRepeated, &positions);

	size = getArraySize(withoutRepeated);

	list2file(withoutRepeated, positions, size , patch);
}

void design_sphere(float radius, int slices, int stacks, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfSphere(radius,slices,stacks);

	write_points_to_file(points,patch);
}

void design_plane(float side, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfPlane(side);

	write_points_to_file(points,patch);	
}

void design_box(float x, float y, float z, int divisions, const char* patch) {
	TAD_ARRAY_LIST points = getPointsOfBox(x, y, z, divisions);

	write_points_to_file(points,patch);
}

void design_cone(float radius, float height, int slices, int stacks, const char* patch) {

	TAD_ARRAY_LIST points = getPointsOfCone(radius, height, slices, stacks);
	
	write_points_to_file(points,patch);
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
	return 0;
}