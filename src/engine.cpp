#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <xmlParser.h>
#include <fromFile.h>
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

float mygt = 0.0;

float px = 0.0;
float py = 0.0;
float pz = 0.0;
int mode = GL_FILL;
int face = GL_FRONT;
GLuint *buffers;
GLuint *indexes;

float** p;
int POINT_COUNT = 0;

Group group;
map<string,Figura> figuras;
map<string,Figura>::iterator it;
Figura f;

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
void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {
    // catmull-rom matrix
    float m[4][4] = {   {-0.5f,  1.5f, -1.5f,  0.5f},
                        { 1.0f, -2.5f,  2.0f, -0.5f},
                        {-0.5f,  0.0f,  0.5f,  0.0f},
                        { 0.0f,  1.0f,  0.0f,  0.0f}};
            
    // Compute A = M * P
    // for component x P is the vector (p0[0], p1[0], p2[0],p3[0]
    float a[3][4];
    float mt[4] = {t*t*t,t*t,t,1};
    float tl[4] = {t*t,t,1,0};
    float s[4];
    for(int i=0;i<3;i++){
        s[0] = p0[i];
        s[1] = p1[i];
        s[2] = p2[i];
        s[3] = p3[i];
        multMatrixVector((float*)m,s,a[i]);
    }
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
    indices[0] = (index + POINT_COUNT-1)%POINT_COUNT;   
    indices[1] = (indices[0]+1)%POINT_COUNT;
    indices[2] = (indices[1]+1)%POINT_COUNT; 
    indices[3] = (indices[2]+1)%POINT_COUNT;
    getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void renderCatmullRomCurve() {
// draw curve using line segments with GL_LINE_LOOP
    float pos[3];
    float deriv[3];// x[t]
    glBegin(GL_LINE_LOOP);
    for(float gt = 0.0;gt<1;gt += 0.01f){
        getGlobalCatmullRomPoint(gt,pos,deriv); // gera os pontos da curva (x,y,z)
        glVertex3f(pos[0],pos[1],pos[2]);
    }
    glEnd();
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

void initCatmullRom(vector<TAD_POINT> points) {
    POINT_COUNT = points.size();
    p = (float**) malloc(sizeof(float)*POINT_COUNT*3);
    for(unsigned i = 0 ; i<POINT_COUNT ; i++) {
        p[i][0] = getX(points[i]);
        p[i][1] = getY(points[i]);
        p[i][2] = getZ(points[i]);
    }
}

void design(Group g){
    int sphere;
    int count;
    static float t = 0;
    float pos[3];
    float deriv[3];
    glPushMatrix();

    for(unsigned i = 0; i<g.operacoes.size() ;i++) {
        Operation op = g.operacoes[i];

        switch(op.flag){
            case 't':
                initCatmullRom(op.points);
                renderCatmullRomCurve();
                mygt+=0.0001;
                if(mygt >= 1) mygt = 0.0f;
                getGlobalCatmullRomPoint(mygt,pos,deriv);
                glTranslatef(pos[0], pos[1] ,pos[2] );
                t+=0.00001;
                //glTranslatef( getX(op.point), getY(op.point), getZ(op.point));
                break;
            case 'r':
                glRotatef(op.ang, getX(op.points[0]), getY(op.points[0]), getZ(op.points[0]));
                break;
            case 's':
                glScalef( getX(op.points[0]), getY(op.points[0]), getZ(op.points[0]));
                break;
            default:
                perror("Modificação inexistente!\n");
                exit(1);
        }

    }

    for(unsigned i = 0,count=0; i<g.ficheiros.size() ;i++,count=0) {
        string nome_ficheiro = g.ficheiros[i];
        for(it=figuras.begin();it!=figuras.end();++it,count++){
            if(it->first.compare(nome_ficheiro) == 0) break; 
        }
        // count indica a posição no map que representa a posição no buffer e no index
        glBindBuffer(GL_ARRAY_BUFFER,buffers[2]); // paga no buffer sphere
        // nº de pontos para formar 1 vertice/ tipo da coordenada/ distancia entre indices dos vertices consecutivos / onde começa o array
        glVertexPointer(3,GL_FLOAT,0,0); // digo que 3 pontos formam 1 vertice
        // usa array de indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[2]);
        printf("rebenta aqui\n"); // (it->second.indicesTAM)
        glDrawElements(GL_TRIANGLES, 540 ,GL_UNSIGNED_INT, 0); // nº de vertices a desenhar
        //glEnable(GL_CULL_FACE);
    }

    for(unsigned i = 0; i < g.filhos.size();i++)
        design(g.filhos[i]);

    glPopMatrix(); 
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
    parse(group,figuras,"file.xml");
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

    
    int nFiguras = figuras.size();
    GLuint buf2[nFiguras];
    GLuint ind2[nFiguras];
    buffers = buf2;
    indexes = ind2;
    glGenBuffers(nFiguras, buffers);                                      // gera 3 buffers de coordenadas
    glGenBuffers(nFiguras, indexes);                                      // gera 3 buffers de indices
    for(it=figuras.begin(),nFiguras=0;it!=figuras.end();++it,nFiguras++){
        printf("nFig:%d\n",nFiguras );
        printf("(it->second.indicesTAM):%d\n",(it->second.indicesTAM) );
        printf("(it->second.vertexBTAM):%d\n",(it->second.vertexBTAM) );
        glBindBuffer(GL_ARRAY_BUFFER,buffers[nFiguras]);                                                          // pega no buffer[nFiguras]
        glBufferData(GL_ARRAY_BUFFER,sizeof(float)*(it->second.vertexBTAM), it->second.vertexB, GL_STATIC_DRAW);  // preenche buffer[nFiguras] 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes[nFiguras]);                                                                 // pega  indexes[nFiguras]
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*(it->second.indicesTAM), (it->second.indices), GL_STATIC_DRAW); // preenche indexes[nFiguras] 
        if(it->first.compare("sphere3.3d") == 0){
            for(int i=0;i<it->second.indicesTAM;i++){
                printf("%d\n",it->second.indices[i]);
            }

        }
    }
    spherical2Cartesian();
	
    // enter GLUT's main cycle
	glutMainLoop();
	
	return 1;
}
