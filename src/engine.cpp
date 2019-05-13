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
GLuint *indexes;
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
	int sphere;
	int count;
	static float t = 0;
	float pos[3];
	float deriv[3];
	float time;
	GLuint figTex;
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
		string nome_ficheiro = g.ficheiros[i];
		string nome_textura = g.texturas[i];
		int tam = 0;
		int j = 0;
		GLuint t;
		for (it = figuras.begin(); it != figuras.end(); ++it, count++) {
			if (it->first.compare(nome_ficheiro) == 0) {
				tam = it->second.indicesTAM;
				break;
			}
		}
		if (nome_textura.compare("SPEC") != 0 && nome_textura.compare("EMI") != 0 && nome_textura.compare("DIFF") != 0 && nome_textura.compare("AMB") != 0) {
			for (aux = textures.begin(); aux != textures.end(); ++it) {
				if (aux->first.compare(nome_textura) == 0) {
					figTex = aux->second.tex;
					break;
				}
			}
			// guardar a textura a ser usada neste desenho
			glBindTexture(GL_TEXTURE_2D, figTex);
		}
		else {
			TAD_POINT p = g.materials.at(j);
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

		// usa array de indices
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[count]);

		// usa array de normais 
		glBindBuffer(GL_ARRAY_BUFFER, normals[count]);
		glNormalPointer(GL_FLOAT, 0, 0);

		if (nome_textura.compare("SPEC") != 0 && nome_textura.compare("EMI") != 0 && nome_textura.compare("DIFF") != 0 && nome_textura.compare("AMB") != 0) {
			// usa array de coordenadas de imagem para aplicar textura
			glBindBuffer(GL_ARRAY_BUFFER, texturas[count]);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
		}

		glDrawElements(GL_TRIANGLES, tam, GL_UNSIGNED_INT, 0); // nº de vertices a desenhar

		if (nome_textura.compare("SPEC") != 0 && nome_textura.compare("EMI") != 0 && nome_textura.compare("DIFF") != 0 && nome_textura.compare("AMB") != 0) {
			// limpar textura usada
			glBindTexture(GL_TEXTURE_2D, 0);
		}
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
	glColor3f(0, 255, 255);
	for(int i = 0 ; i < luzes.size() ; i++)
		glLightfv(GL_LIGHT0 + 1, GL_POSITION, luzes.at(i).pos);
	design(group);
	nextGt = 0;

	//Print FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame * 1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		sprintf(s, "FPS: %f6.2", fps);
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
		}
		printf("\nnormalsTAM=%d\n", f.normalsTAM);
		for (int i = 0; i < f.normalsTAM; i++) {
			printf("%.5f, ", f.normals[i]);
		}
		printf("\ntexCoordsTAM=%d\n", f.texCoordsTAM);
		for (int i = 0; i < f.texCoordsTAM; i++) {
			printf("%.5f, ", f.texCoords[i]);
		}
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // para separar as figuras de modo legível
	}

	printf("DIM=%d\n", dim); // para saber quantas figuras existem
}

void initGL() {

    // alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	spherical2Cartesian();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glClearColor(0, 0, 0, 0);

	for (int i = 0; i < luzes.size(); i++) {
		Light light = luzes.at(i);
		glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, light.diff);
		if (light.tipo == 's') {
			glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, light.spot);
			glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, 45.0);
			glLightf(GL_LIGHT0 + i, GL_SPOT_EXPONENT, 0.0);
		}
		else glLightfv(GL_LIGHT0 + i, GL_AMBIENT, light.amb);
		glEnable(GL_LIGHT0 + i);
	}

	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
}

int main(int argc, char** argv) {
	int nGrupos = 0;
	//group = Group();

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
	parse(group, luzes, figuras, textures, &nGrupos, "file.xml");
	printf("Parse feito com sucesso");
	myangArray = (float*)malloc(sizeof(float)*nGrupos);
	mygtArray = (float*)malloc(sizeof(float)*nGrupos);
	for (int i = 0; i < nGrupos; i++) {
		myangArray[i] = 0;
		mygtArray[i] = 0;
	}
	//printGroup(group);    //  DEBUG
	//printFiguras(figuras); //  DEBUG

	int nFiguras = figuras.size();
	int nTexturas = textures.size();
	GLuint buf2[4];
	GLuint ind2[4];
	GLuint nor2[4];
	GLuint tex2[4];
	buffers = buf2;
	indexes = ind2;
	normals = nor2;
	texturas = tex2;
	glGenBuffers(nFiguras, buffers);                                      // gera 3 buffers de coordenadas
	glGenBuffers(nFiguras, indexes);                                      // gera 3 buffers de indices
	glGenBuffers(nFiguras, normals);
	glGenBuffers(nFiguras, texturas);
	for (it = figuras.begin(), nFiguras = 0; it != figuras.end(); ++it, nFiguras++) {
		glBindBuffer(GL_ARRAY_BUFFER, buffers[nFiguras]);                                                          // pega no buffer[nFiguras]
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(it->second.pointsTAM), it->second.points, GL_STATIC_DRAW);  // preenche buffer[nFiguras] 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[nFiguras]);                                                                 // pega  indexes[nFiguras]
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*(it->second.indicesTAM), (it->second.indexPoints), GL_STATIC_DRAW); // preenche indexes[nFiguras]
		glBindBuffer(GL_ARRAY_BUFFER, normals[nFiguras]);                                                        // pega  indexes[nFiguras]
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(it->second.normalsTAM), it->second.normals, GL_STATIC_DRAW); // preenche indexes[nFiguras] 
		glBindBuffer(GL_ARRAY_BUFFER, texturas[nFiguras]);                                                             // pega  indexes[nFiguras]
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(it->second.texCoordsTAM), it->second.texCoords, GL_STATIC_DRAW); // preenche indexes[nFiguras] 
	}
	printf("Chega aqui?");

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}