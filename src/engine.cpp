#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "../toolkits/devil/IL/il.h"
#include <xmlParser.h>
#include <fromFile.h>
#include <string>
#include <iostream>
#include <group.h>
#include <operation.h>
#include <vector>
#include <Figura.h>
#include <Textura.h>
#include <map>

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.0f, radius = 100.0f;
float camX = 100.0f;
float camY = 0.0f;
float camZ = 150.0f;

float mygt = 0.0;

float px = 0.0;
float py = 0.0;
float pz = 0.0;
int mode = GL_FILL;
int face = GL_FRONT;
GLuint *buffers;
GLuint *indexesPoints;
GLuint *normals;
GLuint *texturas;

vector<TAD_POINT> p;
int POINT_COUNT = 0;
float *mygtArray;
float *myangArray;
int nextGt = 0;

int timebase = 0, frame = 0;

Group group;
vector<Light> luzes;
map<string, Textura> textures;
map<string, Figura> figuras;
map<string, Figura>::iterator it;
map<string, Textura>::iterator aux;



// DEBUG
static void printGroup(Group g) {
	for (int i = 0; i < g.operacoes.size(); i++) {
		Operation op = g.operacoes.at(i);
		printf("Operacao: flag=%c, time=%d\n", op.flag, op.time);
	}
	for (int i = 0; i < g.ficheiros.size(); i++) {
		string str = g.ficheiros.at(i);
		cout << "Ficheiro=" + str + "\n";
	}
	for (int i = 0; i < g.texturas.size(); i++) {
		string str = g.texturas.at(i);
		cout << "Textura=" + str + "\n";
	}
	for (int i = 0; i <g.materials.size(); i++) {
		TAD_POINT str = g.materials.at(i);
		point2string(str);
	}
	for (int i = 0; i < g.filhos.size(); i++) {
		Group a = g.filhos.at(i);
		printf("GROUP:-----------------------------------------------\n");
		printGroup(a);
	}
}

// DEBUG
static void printFiguras(map<string, Figura> figuras) {

	map<string, Figura> ::iterator it;
	int dim = 0;

	for (it = figuras.begin(); it != figuras.end(); it++, dim++) {
		Figura f = it->second;
		printf("indicesTAM=%d\n", f.indicesTAM);
		for (int i = 0; i < f.indicesTAM; i++) {
			printf("%d, ", f.indexPoints[i]);
		}
		printf("\npointsTAM=%d\n", f.pointsTAM);
		for (int i = 0; i < f.pointsTAM; i++) {
			printf("%.5f, ", f.points[i]);
		}/*
		printf("indicesNormaisTAM=%d\n", f.indicesTAM);
		for (int i = 0; i < f.indicesTAM; i++) {
			printf("%d, ", f.indexNormals[i]);
		}
		printf("\nnormalsTAM=%d\n", f.normalsTAM);
		for (int i = 0; i < f.normalsTAM; i++) {
			printf("%.5f, ", f.normals[i]);
		}
		printf("indicesTexturasTAM=%d\n", f.indicesTAM);
		for (int i = 0; i < f.indicesTAM; i++) {
			printf("%d, ", f.indexTexCoords[i]);
		}
		printf("\ntexCoordsTAM=%d\n", f.texCoordsTAM);
		for (int i = 0; i < f.texCoordsTAM; i++) {
			printf("%.5f, ", f.texCoords[i]);
		}*/
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // para separar as figuras de modo legível
	}

	printf("Numero de Figuras diferentes=%d\n", dim); // para saber quantas figuras existem
}

//DEBUG
static void printLights(vector<Light> lights) {
	int i = 0;
	for (; i < lights.size(); i++) {
		printf("tipo=%c\n", lights.at(i).tipo);
		printf("pos= %f , %f , %f , %f\n", lights.at(i).posX, lights.at(i).posY, lights.at(i).posZ, lights.at(i).posD);
		printf("diff= %f , %f , %f , %f\n", lights.at(i).diffX, lights.at(i).diffY, lights.at(i).diffZ, lights.at(i).diffD);
		printf("amb= %f , %f , %f , %f\n", lights.at(i).ambX, lights.at(i).ambY, lights.at(i).ambZ, lights.at(i).ambZ);
		printf("spot= %f , %f , %f\n", lights.at(i).spotX, lights.at(i).spotY, lights.at(i).spotZ);
	}
	printf("\nNumero de luzes=%d\n", i);
}

void spherical2Cartesian() {
	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void multMatrixVector(float *m, float *v, float *res) {
	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

// calcular *pos && *deriv
void getCatmullRomPoint(float t, TAD_POINT p0, TAD_POINT p1, TAD_POINT p2, TAD_POINT p3, float *pos, float *deriv) {
	// catmull-rom matrix
	float m[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f} };
	// Compute A = M * P
	// for component x P is the vector (p0[0], p1[0], p2[0],p3[0]
	float a[3][4];
	float mt[4] = { t*t*t,t*t,t,1 };
	float tl[4] = { t*t,t,1,0 };
	float s[4];
	s[0] = getX(p0);
	s[1] = getX(p1);
	s[2] = getX(p2);
	s[3] = getX(p3);
	multMatrixVector((float*)m, s, a[0]);
	s[0] = getY(p0);
	s[1] = getY(p1);
	s[2] = getY(p2);
	s[3] = getY(p3);
	multMatrixVector((float*)m, s, a[1]);
	s[0] = getZ(p0);
	s[1] = getZ(p1);
	s[2] = getZ(p2);
	s[3] = getZ(p3);
	multMatrixVector((float*)m, s, a[2]);
	// Compute pos = T * A
	for (int j = 0; j < 3; ++j) {
		pos[j] = 0;
		for (int k = 0; k < 4; ++k) {
			pos[j] += mt[k] * a[j][k];
		}
	}
	// compute deriv = T' * A
	for (int j = 0; j < 3; ++j) {
		deriv[j] = 0;
		for (int k = 0; k < 4; ++k) {
			deriv[j] += tl[k] * a[j][k];
		}
	}
}

// given  global t, returns the point in the curve
void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {
	float t = gt * POINT_COUNT; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment
	// indices store the points
	int indices[4];
	indices[0] = (index + POINT_COUNT - 1) % POINT_COUNT;
	indices[1] = (indices[0] + 1) % POINT_COUNT;
	indices[2] = (indices[1] + 1) % POINT_COUNT;
	indices[3] = (indices[2] + 1) % POINT_COUNT;
	getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void renderCatmullRomCurve() {
	// draw curve using line segments with GL_LINE_LOOP
	float pos[3];
	float deriv[3];// x[t]
	glBegin(GL_LINE_LOOP);
	for (float gt = 0.0; gt < 1; gt += 0.01f) {
		getGlobalCatmullRomPoint(gt, pos, deriv); // gera os pontos da curva (x,y,z)
		glVertex3f(pos[0], pos[1], pos[2]);
	}
	glEnd();
}

void changeSize(int w, int h) {
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 10000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void design(Group g) {
	static float t = 0;
	float pos[3];
	float deriv[3];
	float time;
	GLuint figTex;
	string nome_textura, nome_ficheiro;
	glPushMatrix();
	for (unsigned i = 0; i < g.operacoes.size(); i++) {
		Operation op = g.operacoes.at(i);
		time = op.time;
		switch (op.flag) {
		case 't':
			POINT_COUNT = op.points.size();
			p = op.points;
			renderCatmullRomCurve();
			mygtArray[nextGt] += (float)(1.0f / time)*0.001;
			mygt = mygtArray[nextGt];
			if (mygt >= 1) {
				mygt = 0.0;
				mygtArray[nextGt] = 0.0;
			}
			getGlobalCatmullRomPoint(mygt, pos, deriv);
			glTranslatef(pos[0], pos[1], pos[2]);
			break;
		case 'r':
			myangArray[nextGt] += (float)(2 * M_PI / time) * 0.001;
			glRotatef(myangArray[nextGt], getX(op.points[0]), getY(op.points[0]), getZ(op.points[0]));
			break;
		case 's':
			glScalef(getX(op.points[0]), getY(op.points[0]), getZ(op.points[0]));
			break;
		default:
			perror("Modificação inexistente!\n");
			exit(1);
		}

	}
	for (unsigned i = 0, count = 0; i < g.ficheiros.size(); i++, count = 0) {
		nome_ficheiro = g.ficheiros[i];
		if(i < g.texturas.size()) nome_textura = g.texturas[i];
		int tam = 0;
		int j = 0;
		for (it = figuras.begin(); it != figuras.end(); ++it, count++) {
			if (it->first.compare(nome_ficheiro) == 0) {
				//printf("%s,%d\n",nome_ficheiro.c_str(),count );
				tam = it->second.indicesTAM;
				break;
			}
		}
		if (nome_textura.compare("SPEC") != 0 && nome_textura.compare("EMI") != 0 && nome_textura.compare("DIFF") != 0 && nome_textura.compare("AMB") != 0) {
			for (aux = textures.begin(); aux != textures.end(); ++aux) {
				if (aux->first.compare(nome_textura) == 0) {
					//printf("%s\n",nome_textura.c_str());
					figTex = aux->second.tex;
					glBindTexture(GL_TEXTURE_2D, figTex);
					break;
				}
			}
		}
		else {
			TAD_POINT p = g.materials.at(0);
			float arr[4] = {getX(p) ,getY(p),getZ(p),1.0f };
			if (nome_textura.compare("SPEC") == 0) glMaterialfv(GL_FRONT, GL_SPECULAR, arr);
			else if (nome_textura.compare("EMI") == 0) glMaterialfv(GL_FRONT, GL_EMISSION, arr);
			else if (nome_textura.compare("DIFF") == 0) glMaterialfv(GL_FRONT, GL_DIFFUSE, arr);
			else glMaterialfv(GL_FRONT, GL_AMBIENT, arr);
			j += 1;
		}
		// count indica a posição no map que representa a posição no buffer e no index
		glBindBuffer(GL_ARRAY_BUFFER, buffers[count]); // paga no buffer sphere
		// nº de pontos para formar 1 vertice/ tipo da coordenada/ distancia entre indices dos vertices consecutivos / onde começa o array
		glVertexPointer(3, GL_FLOAT, 0, 0); // digo que 3 pontos formam 1 vertice
		// usa array de normais 
		glBindBuffer(GL_ARRAY_BUFFER, normals[count]);
		glNormalPointer(GL_FLOAT, 0, 0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesNormals[count]);
		if (nome_textura.compare("SPEC") != 0 && nome_textura.compare("EMI") != 0 && nome_textura.compare("DIFF") != 0 && nome_textura.compare("AMB") != 0) {
			// usa array de coordenadas de imagem para aplicar textura
			glBindBuffer(GL_ARRAY_BUFFER, texturas[count]);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesTexCoords[count]);
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesPoints[count]);
		glDrawElements(GL_TRIANGLES, tam, GL_UNSIGNED_INT, 0); // nº de vertices a desenhar
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}
	nextGt += 1;
	for (unsigned i = 0; i < g.filhos.size(); i++)
		design(g.filhos[i]);

	glPopMatrix();
}

void renderScene(void) {
	float fps;
	int time;
	char s[64];
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		px, py, pz,
		0.0f, 1.0f, 0.0f);
	for (int i = 0; i < luzes.size(); i++) {
		float pos[4] = { luzes.at(i).posX,luzes.at(i).posY,luzes.at(i).posZ,luzes.at(i).posD };
		glLightfv(GL_LIGHT0 + i, GL_POSITION, pos);
	}
	design(group);
	nextGt = 0;

	//Print FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame * 1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		sprintf(s, "FPS: %6.2f", fps);
		glutSetWindowTitle(s);
	}

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int xx, int yy) {
	// put code to process regular keys in here
	if (c == 'q') { mode = GL_FILL; }
	if (c == 'w') { mode = GL_LINE; }
	if (c == 'e') { mode = GL_POINT; }
	if (c == 'a') { face = GL_FRONT; }
	if (c == 's') { face = GL_BACK; }
	if (c == 'd') { face = GL_FRONT_AND_BACK; }
	glPolygonMode(face, mode);
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
	// put code to process special keys in here
	switch (key) {
	case GLUT_KEY_RIGHT:
		alfa -= 0.1f;
		break;
	case GLUT_KEY_LEFT:
		alfa += 0.1f;
		break;
	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;
	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;
	case GLUT_KEY_PAGE_DOWN:
		radius -= 50.0f;
		if (radius < 1.0f) {
			//radius = 50.0f;
			radius = 10.0f;
		}
		break;
	case GLUT_KEY_PAGE_UP:
		radius += 50.0f;
		break;
	}
	spherical2Cartesian();
	glutPostRedisplay();
}

void initGL() {
	int nGrupos = 0;
	parse(group, luzes, figuras, textures, &nGrupos, "file.xml");

	myangArray = (float*)malloc(sizeof(float)*nGrupos);
	mygtArray = (float*)malloc(sizeof(float)*nGrupos);
	for (int i = 0; i < nGrupos; i++) {
		myangArray[i] = 0;
		mygtArray[i] = 0;
	}

    // alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);

	spherical2Cartesian();

	glEnable(GL_LIGHTING);
	for (int i = 0; i < luzes.size(); i++) {
		glEnable(GL_LIGHT0 + i);
		Light light = luzes.at(i);
		float diff[4] = { light.diffX,light.diffY,light.diffZ,light.diffD};
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diff);
		if (light.tipo == 's') {
			float spot[3] = { light.spotX ,light.spotY,light.spotZ };
			glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, spot);
			glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 45.0);
			glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0.0);
		}
		else {
			float amb[4] = { light.ambX,light.ambY,light.ambZ,light.ambD };
			glLightfv(GL_LIGHT0 + i, GL_AMBIENT, amb);
		}
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put here the registration of the keyboard callbacks
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);


#ifndef __APPLE__
	glewInit();
#endif
	
	//  OpenGL settings
	
	initGL();
	
	//printGroup(group);    //  DEBUG
	//sprintFiguras(figuras); //  DEBUG
	//printLights(luzes); // DEBUG

	int nFiguras = figuras.size();
	GLuint buf2[3];
	GLuint indp[3];
	GLuint nor2[3];
	GLuint indn[3];
	GLuint tex2[3];
	GLuint indt[3];
	buffers = buf2;
	indexesPoints = indp;
	normals = nor2;
	texturas = tex2;
	glGenBuffers(nFiguras, buffers);                                      // gera 3 buffers de coordenadas
	glGenBuffers(nFiguras, indexesPoints);                                // gera 3 buffers de indices
	glGenBuffers(nFiguras, normals);
	glGenBuffers(nFiguras, texturas);
	for (it = figuras.begin(), nFiguras = 0; it != figuras.end(); ++it, nFiguras++) {
		//points
		glBindBuffer(GL_ARRAY_BUFFER, buffers[nFiguras]);                                                          // pega no buffer[nFiguras]
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(it->second.pointsTAM), it->second.points, GL_STATIC_DRAW);  // preenche buffer[nFiguras] 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexesPoints[nFiguras]);                                                                 // pega  indexesPoints[nFiguras]
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*(it->second.indicesTAM), (it->second.indexPoints), GL_STATIC_DRAW); // preenche indexesPoints[nFiguras]
		//normals
		glBindBuffer(GL_ARRAY_BUFFER, normals[nFiguras]);                                                        // pega  normals[nFiguras]
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(it->second.normalsTAM), it->second.normals, GL_STATIC_DRAW); // preenche normals[nFiguras] 
		//texture
		glBindBuffer(GL_ARRAY_BUFFER, texturas[nFiguras]);                                                             // pega  texCoords[nFiguras]
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(it->second.texCoordsTAM), it->second.texCoords, GL_STATIC_DRAW); // preenche texCoords[nFiguras] 
		}
	// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}