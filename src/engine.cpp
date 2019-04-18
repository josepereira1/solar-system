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
GLuint buffers[4];
float* vertexB1 = (float*) malloc(59400*3*sizeof(float));
float* vertexB2 = (float*) malloc(5220*3*sizeof(float));
float* vertexB3 = (float*) malloc(540*3*sizeof(float));

Group group;
map<string,Figura> figuras;

void design(Group g){
    int sphere;
    int vertices;
    glPushMatrix();

    for(unsigned i = 0; i<g.operacoes.size() ;i++) {
        Operation op = g.operacoes[i];

        switch(op.flag){
            case 't':
                glTranslatef(op.x,op.y,op.z);
                break;
            case 'r':
                glRotatef(op.ang, op.x,op.y,op.z);
                break;
            case 's':
                glScalef(op.x,op.y,op.z);
                break;
            default:
                perror("Modificação inexistente!\n");
				exit(1);
        }

    }

    for(unsigned i = 0; i<g.ficheiros.size() ;i++) {
        string nome_ficheiro = g.ficheiros[i];
        if(nome_ficheiro.compare("sphere1.3d")) {sphere = 0; vertices=59400;}
        else if(nome_ficheiro.compare("sphere2.3d")) {sphere = 1; vertices=5220;}
        else {sphere=2; vertices=540;}

        glBindBuffer(GL_ARRAY_BUFFER,buffers[sphere]); // paga no buffer sphere
        // nº de pontos para formar 1 vertice/ tipo da coordenada/ distancia entre indices dos vertices consecutivos / onde começa o array
        glVertexPointer(3,GL_FLOAT,0,0);
         // ultima variavel -> número de vertices não de triangulos
        glDrawArrays(GL_TRIANGLES,0,vertices);
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

// preenche VBO
void getPointsOfSphere(float radius, int slices, int stacks) {
    float* thisVector;
    if(radius == 50) thisVector = vertexB1;
    else if(radius == 10) thisVector = vertexB2;
    else  thisVector = vertexB3;
    float r1 = radius;
    float r2 = radius;
    float alfa = (2*M_PI)/slices;
    float betaYoX = (M_PI)/stacks;
    float height = radius;
    float y1,y2;
    int i;
    int max = slices*(stacks-1)+2;
    int m1,m2;
    // tenho stack + 1 camadas para ligar, a 1ª e a ultima têm 1 vertice
    for(m1=0,i=0;m1<stacks;m1++){ // vertices nas pontas = nº de slices
        y2= height;
        height = cos(betaYoX*(m1+1))*radius;
        y1 = height;
        r2 = sqrt((radius*radius)-(y2*y2));
        r1 = sqrt((radius*radius)-(y1*y1));
        for(m2=0;m2<slices;m2++,i+=9){ //  vertices interiores = nº de slices * 2
            if(m1==0){
                thisVector[i] = 0.0;
                thisVector[i+1] = y2;
                thisVector[i+2] = 0.0;
                thisVector[i+3] = r1*cos((m2+1)*alfa;
                thisVector[i+4] = y1;
                thisVector[i+5] = r1*sin((m2+1)*alfa);
                thisVector[i+6] = r1*cos(m2*alfa);
                thisVector[i+7] = y1;
                thisVector[i+8] = r1*sin(m2*alfa));

            } else if(m1 == (stacks-1)){
                thisVector[i] = 0.0;
                thisVector[i+1] = y1;
                thisVector[i+2] = 0.0;
                thisVector[i+3] = r2*cos(m2*alfa);
                thisVector[i+4] = y2;
                thisVector[i+5] = r2*sin(m2*alfa);
                thisVector[i+6] = r2*cos((m2+1)*alfa);
                thisVector[i+7] = y2;
                thisVector[i+8] = r2*sin((m2+1)*alfa);

            } else{
                thisVector[i] = r2*cos(m2*alfa);
                thisVector[i+1] = y2;
                thisVector[i+2] = r2*sin(m2*alfa);
                thisVector[i+3] = r1*cos((m2+1)*alfa);
                thisVector[i+4] = y1;
                thisVector[i+5] = r1*sin((m2+1)*alfa);
                thisVector[i+6] = r1*cos(m2*alfa);
                thisVector[i+7] = y1;
                thisVector[i+8] = r1*sin(m2*alfa);
                i+=9;

                // triangulo inverso
                thisVector[i] = r2*cos(m2*alfa);
                thisVector[i+1] = y2;
                thisVector[i+2] = r2*sin(m2*alfa);
                thisVector[i+3] = r2*cos((m2+1)*alfa);
                thisVector[i+4] = y2;
                thisVector[i+5] = r2*sin((m2+1)*alfa);
                thisVector[i+6] = r1*cos((m2+1)*alfa);
                thisVector[i+7] = y1;
                thisVector[i+8] = r1*sin((m2+1)*alfa);
            }
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
    
    glGenBuffers(3, buffers);                 // gera-me 3 buffers
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // pega no buffer 0
    getPointsOfSphere(50,100,100);            // preeche array a copiar para buffer 0
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*59400, vertexB1, GL_STATIC_DRAW); // preenche buffer 0
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]); // pega no buffer 1
    getPointsOfSphere(10,30,30);              // preeche array a copiar para buffer 1
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*5220, vertexB2, GL_STATIC_DRAW); // preenche buffer 1
    glBindBuffer(GL_ARRAY_BUFFER,buffers[2]); // pega no buffer 2
    getPointsOfSphere(2,10,10);               // preeche array a copiar para buffer 2
    glBufferData(GL_ARRAY_BUFFER,sizeof(float)*3*540, vertexB3, GL_STATIC_DRAW); // preenche buffer 2

    spherical2Cartesian();
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
