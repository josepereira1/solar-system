#define SIZE 50

#include <Point.h>
#include <vector>

using namespace std;

vector<TAD_POINT> getPointsOfBox(float x, float y, float z, int divisions) {
	vector<TAD_POINT> points;

	if(divisions==0) divisions = 1;//avoid division by 0
	float xmin = -x/2, ymin = -y/2, zmin = -z/2, xmax = x/2, ymax = y/2, zmax = z/2;//max and min values to x y z
	float dx = x/divisions, dy = y/divisions, dz = z/divisions;//size of divisions
	int i,j;//Variables to run faces
	//frontal face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			points.push_back(POINT(xmin + (j + 1)*dx, ymin + i * dy, zmax));
			points.push_back(POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmax));
			points.push_back(POINT(xmin + j * dx, ymin + i * dy, zmax));
			//2º triangle
			points.push_back(POINT(xmin + j * dx, ymin + i * dy, zmax));
			points.push_back(POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmax));
			points.push_back(POINT(xmin + j * dx, ymin + (i + 1)*dy, zmax));
		}
	}
	//rigth face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			points.push_back(POINT(xmax, ymin + i * dy, zmin + (j + 1)*dz));
			points.push_back(POINT(xmax, ymin + i * dy, zmin + j * dz));
			points.push_back(POINT(xmax, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			//2º triangle
			points.push_back(POINT(xmax, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			points.push_back(POINT(xmax, ymin + i * dy, zmin + j * dz));
			points.push_back(POINT(xmax, ymin + (i + 1)*dy, zmin + j * dz));
		}
	}
	//up face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			points.push_back(POINT(xmin + i * dx, ymax, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin + (i + 1)*dx, ymax, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin + i * dx, ymax, zmin + j * dz));
			//2º triangle
			points.push_back(POINT(xmin + i * dx, ymax, zmin + j * dz));
			points.push_back(POINT(xmin + (i + 1)*dx, ymax, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin + (i + 1)*dx, ymax, zmin + j * dz));
		}
	}
	//back face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			points.push_back(POINT(xmin + (j + 1)*dx, ymin + i * dy, zmin));
			points.push_back(POINT(xmin + j * dz, ymin + i * dy, zmin));
			points.push_back(POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmin));
			//2º triangle
			points.push_back(POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmin));
			points.push_back(POINT(xmin + j * dz, ymin + i * dy, zmin));
			points.push_back(POINT(xmin + j * dx, ymin + (i + 1)*dy, zmin));
		}
	}
	//left face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			points.push_back(POINT(xmin, ymin + i * dy, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin, ymin + i * dy, zmin + j * dz));
			//2º triangle
			points.push_back(POINT(xmin, ymin + i * dy, zmin + j * dz));
			points.push_back(POINT(xmin, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin, ymin + (i + 1)*dy, zmin + j * dz));
		}
	}
	//down face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			points.push_back(POINT(xmin + i * dx, ymin, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin + i * dx, ymin, zmin + j * dz));
			points.push_back(POINT(xmin + (i + 1)*dx, ymin, zmin + (j + 1)*dz));
			//2º triangle
			points.push_back(POINT(xmin + (i + 1)*dx, ymin, zmin + (j + 1)*dz));
			points.push_back(POINT(xmin + i * dx, ymin, zmin + j * dz));
			points.push_back(POINT(xmin + (i + 1)*dx, ymin, zmin + j * dz));
		}
	}
	return points;
}