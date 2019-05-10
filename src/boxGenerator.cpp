#define SIZE 50
#include <ArrayList.h>
#include <Point.h>

TAD_ARRAY_LIST getPointsOfBox(float x, float y, float z, int divisions, TAD_ARRAY_LIST *normals, TAD_ARRAY_LIST *texCoords) {

	if(divisions==0) divisions = 1;//avoid division by 0
	int triangles = 6 * divisions * divisions * 2;
	TAD_ARRAY_LIST points = ARRAY_LIST(triangles);
	*normals = ARRAY_LIST(triangles);
	*texCoords = ARRAY_LIST(triangles);

	float xmin = -x/2, ymin = -y/2, zmin = -z/2, xmax = x/2, ymax = y/2, zmax = z/2;//max and min values to x y z
	float dx = x/divisions, dy = y/divisions, dz = z/divisions;//size of divisions
	int i,j;//Variables to run faces

	/*
	Struct of the image
	|frontal face | rigth face | up face  |
	|back face    | left face  | down face|
	*/

	//frontal face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			//points
			addElem(points,POINT(xmin + (j + 1)*dx, ymin + i * dy, zmax));
			addElem(points,POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmax));
			addElem(points,POINT(xmin + j * dx, ymin + i * dy, zmax));
			//normals
			addElem(normals,POINT(0,0,1.0f));
			addElem(normals,POINT(0,0,1.0f));
			addElem(normals,POINT(0,0,1.0f));
			//texCoords
			addElem(texCoords,POINT(0.33f * (j+1) / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f * (j+1) / divisions,0.5f + 0.5f * (i+1) / divisions,0))			
			addElem(texCoords,POINT(0.33f * j / divisions,0.5f + 0.5f * i / divisions,0))

			//2º triangle
			//points
			addElem(points,POINT(xmin + j * dx, ymin + i * dy, zmax));
			addElem(points,POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmax));
			addElem(points,POINT(xmin + j * dx, ymin + (i + 1)*dy, zmax));
			//normals
			addElem(normals,POINT(0,0,1.0f));
			addElem(normals,POINT(0,0,1.0f));
			addElem(normals,POINT(0,0,1.0f));
			//texCoords
			addElem(texCoords,POINT(0.33f * j / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f * (j+1) / divisions,0.5f + 0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.33f * j / divisions,0.5f + 0.5f * (i+1) / divisions,0));
		}
	}
	//rigth face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			//points
			addElem(points,POINT(xmax, ymin + i * dy, zmin + (j + 1)*dz));
			addElem(points,POINT(xmax, ymin + i * dy, zmin + j * dz));
			addElem(points,POINT(xmax, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			//normals
			addElem(normals,POINT(1.0f,0,0));
			addElem(normals,POINT(1.0f,0,0));
			addElem(normals,POINT(1.0f,0,0));
			//texCoords
			addElem(texCoords,POINT(0.33f + 0.33f * (j+1) / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * j / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * (j+1) / divisions,0.5f + 0.5f * (i+1) / divisions,0));

			//2º triangle
			//points
			addElem(points,POINT(xmax, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			addElem(points,POINT(xmax, ymin + i * dy, zmin + j * dz));
			addElem(points,POINT(xmax, ymin + (i + 1)*dy, zmin + j * dz));
			//normals
			addElem(normals,POINT(1.0f,0,0));
			addElem(normals,POINT(1.0f,0,0));
			addElem(normals,POINT(1.0f,0,0));
			//texcoords
			addElem(texCoords,POINT(0.33f + 0.33f * (j+1) / divisions,0.5f + 0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * j / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * j / divisions,0.5f + 0.5f * (i+1) / divisions,0));
		}
	}
	//up face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			//points
			addElem(points,POINT(xmin + i * dx, ymax, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin + (i + 1)*dx, ymax, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin + i * dx, ymax, zmin + j * dz));
			//normals
			addElem(normals,POINT(0,1.0f,0));
			addElem(normals,POINT(0,1.0f,0));
			addElem(normals,POINT(0,1.0f,0));
			//texCoords
			addElem(texCoords,POINT(0.66f + 0.33f * (j+1) / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * (j+1) / divisions,0.5f + 0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * j / divisions,0.5f + 0.5f * i / divisions,0));
			
			//2º triangle
			//points
			addElem(points,POINT(xmin + i * dx, ymax, zmin + j * dz));
			addElem(points,POINT(xmin + (i + 1)*dx, ymax, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin + (i + 1)*dx, ymax, zmin + j * dz));
			//normals
			addElem(normals,POINT(0,1.0f,0));
			addElem(normals,POINT(0,1.0f,0));
			addElem(normals,POINT(0,1.0f,0));
			//texCoords
			addElem(texCoords,POINT(0.66f + 0.33f * j / divisions,0.5f + 0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * (j+1) / divisions,0.5f + 0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * j / divisions,0.5f + 0.5f * (i+1) / divisions,0));
		}
	}
	//back face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			//points
			addElem(points,POINT(xmin + (j + 1)*dx, ymin + i * dy, zmin));
			addElem(points,POINT(xmin + j * dz, ymin + i * dy, zmin));
			addElem(points,POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmin));
			//normals
			addElem(normals,POINT(0,0,-1.0f));
			addElem(normals,POINT(0,0,-1.0f));
			addElem(normals,POINT(0,0,-1.0f));
			//texCoords
			addElem(texCoords,POINT(0.33f * (j+1) / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f * j / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f * (j+1) / divisions,0.5f * (i+1) / divisions,0));

			//2º triangle
			//points
			addElem(points,POINT(xmin + (j + 1)*dx, ymin + (i + 1)*dy, zmin));
			addElem(points,POINT(xmin + j * dz, ymin + i * dy, zmin));
			addElem(points,POINT(xmin + j * dx, ymin + (i + 1)*dy, zmin));
			//normals
			addElem(normals,POINT(0,0,-1.0f));
			addElem(normals,POINT(0,0,-1.0f));
			addElem(normals,POINT(0,0,-1.0f));
			//texCoords
			addElem(texCoords,POINT(0.33f * (j+1) / divisions,0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.33f * j / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f * j / divisions,0.5f * (i+1) / divisions,0));
		}
	}
	//left face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			//points
			addElem(points,POINT(xmin, ymin + i * dy, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin, ymin + i * dy, zmin + j * dz));
			//normals
			addElem(normals,POINT(-1.0f,0,0));
			addElem(normals,POINT(-1.0f,0,0));
			addElem(normals,POINT(-1.0f,0,0));
			//texCoords
			addElem(texCoords,POINT(0.33f + 0.33f * (j+1) / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * (j+1) / divisions,0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * j / divisions,0.5f * i / divisions,0));

			//2º triangle
			//points
			addElem(points,POINT(xmin, ymin + i * dy, zmin + j * dz));
			addElem(points,POINT(xmin, ymin + (i + 1)*dy, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin, ymin + (i + 1)*dy, zmin + j * dz));
			//normals
			addElem(normals,POINT(-1.0f,0,0));
			addElem(normals,POINT(-1.0f,0,0));
			addElem(normals,POINT(-1.0f,0,0));
			//texCoords
			addElem(texCoords,POINT(0.33f + 0.33f * j / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * (j+1) / divisions,0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.33f + 0.33f * j / divisions,0.5f * (i+1) / divisions,0));
		}
	}
	//down face
	for (i = 0; i < divisions; i++) {
		for (j = 0; j < divisions; j++) {
			//1º triangle
			//points
			addElem(points,POINT(xmin + i * dx, ymin, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin + i * dx, ymin, zmin + j * dz));
			addElem(points,POINT(xmin + (i + 1)*dx, ymin, zmin + (j + 1)*dz));
			//normals
			addElem(normals,POINT(0,-1.0f,0));
			addElem(normals,POINT(0,-1.0f,0));
			addElem(normals,POINT(0,-1.0f,0));
			//texCoords
			addElem(texCoords,POINT(0.66f + 0.33f * (j+1) / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * j / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * (j+1) / divisions,0.5f * (i+1) / divisions,0));

			//2º triangle
			//points
			addElem(points,POINT(xmin + (i + 1)*dx, ymin, zmin + (j + 1)*dz));
			addElem(points,POINT(xmin + i * dx, ymin, zmin + j * dz));
			addElem(points,POINT(xmin + (i + 1)*dx, ymin, zmin + j * dz));
			//normals
			addElem(normals,POINT(0,-1.0f,0));
			addElem(normals,POINT(0,-1.0f,0));
			addElem(normals,POINT(0,-1.0f,0));
			//texCoords
			addElem(texCoords,POINT(0.66f + 0.33f * (j+1) / divisions,0.5f * (i+1) / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * j / divisions,0.5f * i / divisions,0));
			addElem(texCoords,POINT(0.66f + 0.33f * j / divisions,0.5f * (i+1) / divisions,0));
		}
	}
	return points;
}