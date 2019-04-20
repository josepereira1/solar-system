#include <fromFile.h>
// c 
#include <math.h> 
// c++ 
#include <string>
#include <fstream>

using namespace std;

static float* createPolyBernstein(float p) {
	/* usamos a fórmula que está na BB */
	float* b = (float*) malloc(sizeof(float) * 4);
	b[0] = powf(1 - p, 3);
    b[1] = 3 * p * powf(1 - p, 2);
    b[2] = 3 * powf(p, 2) * (1 - p);
	b[3] = powf(p, 3);
	return b;
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

TAD_ARRAY_LIST getPointsOfBezier(string patchFile, int tLevel) {

	int** arrayPatchs = NULL;
	TAD_ARRAY_LIST cps = ARRAY_LIST(25);
	readPatchFile(patchFile, &arrayPatchs, &cps);

	TAD_ARRAY_LIST pontos = ARRAY_LIST(10000);

	for (int i = 0; arrayPatchs[i] != (int*) NULL; i++) { // para cada patch
		
		for (int k = 0; k < tLevel; k++) { // k = tesselation V
			
			float v = (float)k / tLevel;
			
			for (int w = 0; w < tLevel; w++) { // w = tesselation U
				
				float u = (float)w / tLevel;

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
			}
		}
	}

	return pontos;
}