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
GLuint *buffers;
GLuint *indexes;

Group group;
map<string,Figura> figuras;
map<string,Figura>::iterator it;
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

    for(unsigned i = 0; i<g.ficheiros.size() ;i++,count=0) {
        string nome_ficheiro = g.ficheiros[i];
         for(it=figuras.begin();it!=mymap.end();++it,count++){
            if(it->first.compare(nome_ficheiro) == 0) break; 
         }
         // count indica a posição no map que representa a posição no buffer e no index

        glBindBuffer(GL_ARRAY_BUFFER,buffers[count]); // paga no buffer sphere
        // nº de pontos para formar 1 vertice/ tipo da coordenada/ distancia entre indices dos vertices consecutivos / onde começa o array
        glVertexPointer(3,GL_FLOAT,0,0);
        // usa array de indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[count]);
        glDrawElements(GL_TRIANGLES, (it->secound->vertexBTAM/3) ,GL_UNSIGNED_INT, NULL);
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

    int nFiguras = 0;

    glGenBuffers(nFiguras, buffers);                                                      // gera 3 buffers de coordenadas
    glGenBuffers(nFiguras, indexes);                                                      // gera 3 buffers de indices

    for(it=figuras.begin();it!=mymap.end();++it,nFiguras++){
        glBindBuffer(GL_ARRAY_BUFFER,buffers[nFiguras]);                                                            // pega no buffer[nFiguras]
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*(it->second->vertexBTAM), it->second->vertexB, GL_STATIC_DRAW);  // preenche buffer[nFiguras] 

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[nFiguras]);                                                                   // pega  indexes[nFiguras]
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*(it->second->indicesTAM), (it->second->indices), GL_STATIC_DRAW); // preenche indexes[nFiguras] 
    }

    spherical2Cartesian();
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
