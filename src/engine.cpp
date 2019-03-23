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

float px = 0.0;
float py = 0.0;
float pz = 0.0;
int mode = GL_FILL;
int face = GL_FRONT;

Group group;
map<string,Figura> figuras;

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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void draw() {
    glBegin(GL_TRIANGLES);
	    //TODO
    glEnd();
	glEnable(GL_CULL_FACE);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(30.0, 30.0, 30.0,
		      px, py, pz,
			  0.0f,1.0f,0.0f);

	glColor3f(0,255,255);

	draw(); // imprime as figuras


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
}


// DEBUG
static void printGroup(Group g) {
    printf("GROUP:-----------------------------------------------\n");
    for(unsigned i = 0; i<g.operacoes.size() ;i++) {
        Operation op = g.operacoes[i];
        printf("Operacao: Flag=%c ,X=%f ,Y=%f ,Z=%f ,Angle=%f\n",op.flag,op.x,op.y,op.z,op.ang);
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
        vector<float> pontos = it->second.pontos;
        for(unsigned k=0; k<pontos.size(); k+=3) {
            printf("file:%s => X=%f, Y=%f, Z=%f\n", it->first.c_str(), pontos[k], pontos[k+1], pontos[k+2]);
        }
    }
}

int main(int argc, char** argv) {
    
    parse(group,figuras,"file.xml");
    printGroup(group);
    printFiguras(figuras);

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
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
