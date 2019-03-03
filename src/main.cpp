#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

extern "C"
{
    #include "ArrayList.h"
    #include "Point.h"
    #include "newSphereGenerator.h"
}

#define _USE_MATH_DEFINES
#include <math.h>

float px = 0.0;
float py = 0.0;
float pz = 0.0;
int mode = GL_FILL;
int face = GL_FRONT;
TAD_ARRAY_LIST l =  ARRAY_LIST(50);

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
    int i;
	int size = getArraySize(l);
    // put code to draw cylinder in here
    glBegin(GL_TRIANGLES);
    for(i=0;i<size;i++){
        glVertex3f((float) getX((TAD_POINT)getElem(l,i)),(float)getY((TAD_POINT)getElem(l,i)),(float)getZ((TAD_POINT)getElem(l,i)));
    }
    glEnd();
	glEnable(GL_CULL_FACE);
	
}


void renderScene(void) {


	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0,
		      px, py, pz,
			  0.0f,1.0f,0.0f);

  glColor3f(0,255,255);
	draw();

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


int main(int argc, char** argv) {
    // init GLUT and the window

	printf("passei aqui!\n");

    l = file2list("dados.txt");

    TAD_POINT point;

    printf("%d\n", getArraySize(l));

    for(int i = 0; i < getArraySize(l); i++){
    	point = getElem(l,i);
    	point2string(point);
    }

    //draw();

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
