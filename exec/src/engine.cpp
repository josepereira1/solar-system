#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <xmlParser.h>
#include <string>
#include <iostream>
#include <group.h>
#include <operation.h>
#include <vector>
#include <Figura.h>
#include <map>

#define _USE_MATH_DEFINES
#include <math.h>

float alfa = 0.0f, beta = 0.0f, radius = 100.0f;
float camX = 100.0f;
float camY = 0.0f;
float camZ = 150.0f;

float px = 0.0;
float py = 0.0;
float pz = 0.0;
int mode = GL_FILL;
int face = GL_FRONT;
GLuint buffers[3];
GLuint indexes[3];
float* vertexB1;
float* vertexB2;
float* vertexB3;
unsigned int *indices1;
unsigned int *indices2;
unsigned int *indices3;
int tam1;
int tam2[3];

Group group;
map<string,Figura> figuras;
Figura f;

void design(Group g){
    int sphere;
    int count;
    glPushMatrix();

    for(unsigned i = 0; i<g.operacoes.size() ;i++) {
        Operation op = g.operacoes[i];

        switch(op.flag){
            case 't':
                glTranslatef( getX(op.point), getY(op.point), getZ(op.point));
                break;
            case 'r':
                glRotatef(op.ang, getX(op.point), getY(op.point), getZ(op.point));
                break;
            case 's':
                glScalef( getX(op.point), getY(op.point), getZ(op.point));
                break;
            default:
                perror("Modificação inexistente!\n");
				exit(1);
        }

    }

    for(unsigned i = 0; i<g.ficheiros.size() ;i++) {
        string nome_ficheiro = g.ficheiros[i];
        if(nome_ficheiro.compare("sphere1.3d")) {sphere = 0; count=tam2[0];}
        else if(nome_ficheiro.compare("sphere2.3d")) {sphere = 1; count=tam2[1];}
        else {sphere=2; count=tam2[2];}

        glBindBuffer(GL_ARRAY_BUFFER,buffers[sphere]); // paga no buffer sphere
        // nº de pontos para formar 1 vertice/ tipo da coordenada/ distancia entre indices dos vertices consecutivos / onde começa o array
        glVertexPointer(3,GL_FLOAT,0,0);
        // usa array de indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[sphere]);
        glDrawElements(GL_TRIANGLES, count ,GL_UNSIGNED_INT, NULL);
        //glEnable(GL_CULL_FACE);
    }

    for(unsigned i = 0; i < g.filhos.size();i++)
        design(g.filhos[i]);

    glPopMatrix(); 
}

void spherical2Cartesian() {

    camX = radius * cos(beta) * sin(alfa);
    camY = radius * sin(beta);
    camZ = radius * cos(beta) * cos(alfa);
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
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
	gluPerspective(45.0f ,ratio, 1.0f ,10000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		      px, py, pz,
			  0.0f,1.0f,0.0f);

	glColor3f(0,255,255);

	design(group);


	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	// put code to process regular keys in here
     if(c == 'q'){ mode = GL_FILL;}
     if(c == 'w'){ mode = GL_LINE;}
     if(c == 'e'){ mode = GL_POINT;}
     if(c == 'a'){ face = GL_FRONT;}
     if(c == 's'){ face = GL_BACK;}
     if(c == 'd'){ face = GL_FRONT_AND_BACK;}
     glPolygonMode(face,mode);
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
    printf("GROUP:-----------------------------------------------\n");
    for(unsigned i = 0; i<g.operacoes.size() ;i++) {
        Operation op = g.operacoes[i];
        //printf("Operacao: Flag=%c ,X=%f ,Y=%f ,Z=%f ,Angle=%f\n",op.flag,op.x,op.y,op.z,op.ang);
    }
    for(unsigned i = 0; i<g.ficheiros.size() ;i++) {
        string str = g.ficheiros[i];
        cout << "Ficheiro=" + str +"\n";
    }
    for(unsigned i = 0; i<g.filhos.size() ;i++) {
        Group a = g.filhos[i];
        printGroup(a);
    }
}

// DEBUG
static void printFiguras(map<string,Figura> figuras) {
    map<string, Figura>::iterator it;
    for (it = figuras.begin(); it != figuras.end(); it++) {
        float* pontos = it->second.vertexB;
        for(int k=0; k<it->second.vertexBTAM; k+=3) {
            printf("file:%s => X=%f, Y=%f, Z=%f\n", it->first.c_str(), pontos[k], pontos[k+1], pontos[k+2]);
        }
    }
}

int main(int argc, char** argv) {
    
    parse(group,figuras,"teapot.xml");
    // parse(group,figuras,"file.xml");
    // printGroup(group);    //  DEBUG
    // printFiguras(figuras); //  DEBUG

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
	glutCreateWindow("CG@DI-UM");

    // Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	
    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    glGenBuffers(3, buffers);                                                      // gera 3 buffers de coordenadas
    glGenBuffers(3, indexes);                                                      // gera 3 buffers de indices

    // encontra arrays a copiar para buffer[0] e idexes[0]
    file2list("sphere1.3d",&indices1,&(tam2),&vertexB1,&tam1);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);                                                     // pega no buffer 0
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*tam1, vertexB1, GL_STATIC_DRAW);                   // preenche buffer 0

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[0]);                                            // pega  indexes[2]
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*tam2[0], indices1, GL_STATIC_DRAW); // preenche indexes[0]

    // encontra arrays a copiar para buffer[1] e idexes[1]
    file2list("sphere2.3d",&indices2,&(tam2[1]),&vertexB2,&tam1);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);                                                     // pega no buffer 1
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*tam1, vertexB2, GL_STATIC_DRAW);                   // preenche buffer 1

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[1]);                                            // pega  indexes[2]
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*tam2[1], indices2, GL_STATIC_DRAW); // preenche indexes[1]

    // encontra arrays a copiar para buffer[2] e idexes[2]
    file2list("sphere2.3d",&indices3,&(tam2[2]),&vertexB3,&tam1);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);                                                     // pega no buffer[2]
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*tam1, vertexB3, GL_STATIC_DRAW);                   // preenche buffer[2]

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[2]);                                            // pega  indexes[2]
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*tam2[2], indices3, GL_STATIC_DRAW); // preenche indexes[2]

    spherical2Cartesian();
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
