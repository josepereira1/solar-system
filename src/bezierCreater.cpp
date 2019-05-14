#include <fromFile.h>
// c 
#include <math.h> 
// c++ 
#include <string>
#include <fstream>

using namespace std;

static TAD_POINT cross(float *a, float *b) {

	float x = a[1] * b[2] - a[2] * b[1];
	float y = a[2] * b[0] - a[0] * b[2];
	float z = a[0] * b[1] - a[1] * b[0];
	return POINT(x,y,z);
}

static float* createDerivBernstein(float p) {
	float* b = (float*) malloc(sizeof(float)*4);
	b[0] = -3 * (1-p) * (1-p);
	b[1] = 3 * (1-p) * (1-p) - 6 * p * (1-p);
	b[2] = 6 * p * (1-p) - 3 * p * p;
	b[3] = 3 * p * p;
	return b;
}

static float* createPolyBernstein(float p) {
	/* usamos a fórmula que está na BB */
	float* b = (float*) malloc(sizeof(float) * 4);
	b[0] = powf(1 - p, 3);
    b[1] = 3 * p * powf(1 - p, 2);
    b[2] = 3 * powf(p, 2) * (1 - p);
	b[3] = powf(p, 3);
	return b;
}

static TAD_POINT getBezierNormal(int** arrayPatchs, TAD_ARRAY_LIST cps, int numeroDoPatch, float u, float v) {

	float* bu = createPolyBernstein(u); // gerar o polinómio de Bernstein para o ponto U
    float* bv = createPolyBernstein(v); // gerar o polinómio de Bernstein para o ponto V
	float* dbu = createDerivBernstein(u); // gerar a derivada de Bernstein para o ponto U
    float* dbv = createDerivBernstein(v); // gerar a derivada de Bernstein para o ponto V

    float v1[3], v2[3];
    v1[0] = v1[1] = v1[2] = v2[0] = v2[1] = v2[2] = 0;

    /* fórmula usada:
     * B(lu,v) = dBi(u) * Pij * Bj(v)
     */
    for(int i = 0 ; i < 4 ; i++) {
    	for(int j = 0 ; j < 4 ; j++) {
    		int indiceNoPatch = i * 4 + j;
    		int indice_pc = arrayPatchs[numeroDoPatch][indiceNoPatch];
    		TAD_POINT p = (TAD_POINT) getElem(cps,indice_pc);
    		v1[0] += dbu[i] * getX(p) * bv[j];
            v1[1] += dbu[i] * getY(p) * bv[j];
            v1[2] += dbu[i] * getZ(p) * bv[j];
    	}
    }
    /* fórmula usada:
     * B(u,lv) = Bi(u) * Pij * dBj(v)
     */
    for(int i = 0 ; i < 4 ; i++) {
    	for(int j = 0 ; j < 4 ; j++) {
    		int indiceNoPatch = i * 4 + j;
    		int indice_pc = arrayPatchs[numeroDoPatch][indiceNoPatch];
    		TAD_POINT p = (TAD_POINT) getElem(cps,indice_pc);
    		v2[0] += bu[i] * getX(p) * dbv[j];
            v2[1] += bu[i] * getY(p) * dbv[j];
            v2[2] += bu[i] * getZ(p) * dbv[j];
    	}
    }
    return normalize(cross(v1, v2));
}

static TAD_POINT getBezierPoint(int** arrayPatchs, TAD_ARRAY_LIST cps, int numeroDoPatch, float u, float v) {
    
    float* bu = createPolyBernstein(u); // gerar o polinómio de Bernstein para o ponto U
    float* bv = createPolyBernstein(v); // gerar o polinómio de Bernstein para o ponto V

    float x = 0.0f, y = 0.0f, z = 0.0f; // ponto inicial

    /* fórmula usada:
     * B(u,v) = Bi(u) * Pij * Bj(v)
     */
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

        	int indiceNoPatch = i * 4 + j; 
            
            int indice_pc = arrayPatchs[numeroDoPatch][indiceNoPatch]; // indice do ponto de controlo
            TAD_POINT p = (TAD_POINT) getElem(cps,indice_pc);
            x += bu[i] * getX(p) * bv[j];
            y += bu[i] * getY(p) * bv[j];
            z += bu[i] * getZ(p) * bv[j];
        }
    }

    return POINT(x, y, z);
}

TAD_ARRAY_LIST getPointsOfBezier(string patchFile, int tLevel, TAD_ARRAY_LIST *normals) {

	int** arrayPatchs = NULL;
	TAD_ARRAY_LIST cps = ARRAY_LIST(25);
	readPatchFile(patchFile, &arrayPatchs, &cps);

	TAD_ARRAY_LIST pontos = ARRAY_LIST(10000);
	*normals = ARRAY_LIST(10000);

	for (int i = 0; arrayPatchs[i] != (int*) NULL; i++) { // para cada patch
		
		for (int k = 0; k < tLevel; k++) { // k = tesselation V
			
			float v = (float)k / tLevel;
			
			for (int w = 0; w < tLevel; w++) { // w = tesselation U
				
				float u = (float)w / tLevel;
				//points
				TAD_POINT p1 = getBezierPoint(arrayPatchs, cps, i, u, v);
				TAD_POINT p2 = getBezierPoint(arrayPatchs, cps, i, (u + (1.0f / tLevel)), v);
				TAD_POINT p3 = getBezierPoint(arrayPatchs, cps, i, (u + (1.0f / tLevel)), (v + (1.0f / tLevel)));

				TAD_POINT p4 = getBezierPoint(arrayPatchs, cps, i, (u + (1.0f / tLevel)), (v + (1.0f / tLevel)));
				TAD_POINT p5 = getBezierPoint(arrayPatchs, cps, i, u, (v + (1.0f / tLevel)));
				TAD_POINT p6 = getBezierPoint(arrayPatchs, cps, i, u, v);

				addElem(pontos,p1);
				addElem(pontos,p2);
				addElem(pontos,p3);

				addElem(pontos,p4);
				addElem(pontos,p5);
				addElem(pontos,p6);

				//normals
				TAD_POINT pl1 = getBezierNormal(arrayPatchs, cps, i, u, v);
				TAD_POINT pl2 = getBezierNormal(arrayPatchs, cps, i, (u + (1.0f / tLevel)), v);
				TAD_POINT pl3 = getBezierNormal(arrayPatchs, cps, i, (u + (1.0f / tLevel)), (v + (1.0f / tLevel)));

				TAD_POINT pl4 = getBezierNormal(arrayPatchs, cps, i, (u + (1.0f / tLevel)), (v + (1.0f / tLevel)));
				TAD_POINT pl5 = getBezierNormal(arrayPatchs, cps, i, u, (v + (1.0f / tLevel)));
				TAD_POINT pl6 = getBezierNormal(arrayPatchs, cps, i, u, v);

				addElem(*normals,pl1);
				addElem(*normals,pl2);
				addElem(*normals,pl3);

				addElem(*normals,pl4);
				addElem(*normals,pl5);
				addElem(*normals,pl6);
			}
		}
	}

	return pontos;
}