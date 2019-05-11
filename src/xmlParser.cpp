#include <tinyxml.h>
#include <stdio.h>
#include <iostream>
#include <group.h>
#include <operation.h>
#include <vector>
#include <Figura.h>
#include <Textura.h>
#include <map>
#include <fromFile.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include "../toolkits/devil/IL/il.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif



using namespace std;


int loadTexture(std::string s) {

    unsigned int t,tw,th;
    unsigned char *texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1,&t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1,&texID);
    
    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,      GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER,      GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

}

static Group searchRec(map<string,Figura> &figuras, map<string,Textura> &texturas, int *nGrupos, TiXmlElement *pRoot) {
    
    bool t = false, r = false, s = false, m = false;
    pRoot = pRoot->FirstChildElement();
    TiXmlElement *pChild;
    
    Group group = Group();
    
    while(pRoot) {
        string name = (string)pRoot->Value();
        string textura = (string)pRoot->Value();

        float x=0.0f,y=0.0f,z=0.0f;
        int time=0;
        const char *sx, *sy, *sz, *stime;
        
        if(name.compare("translate")==0) {
            
            if(!t) {
                
                stime = pRoot->Attribute("time");

                if(stime) time = atoi(stime);

                vector<TAD_POINT> points;
                pChild = pRoot->FirstChildElement("point");
                if (pChild) {
                    
                    name = (string)pChild->Value();
                    
                    if (name.compare("") != 0) {
                        while(pChild) {
                            if(name.compare("point")==0) {
                                sx = pChild->Attribute("X");
                                if(sx) x = atof(sx);
                                
                                sy = pChild->Attribute("Y");
                                if(sy) y = atof(sy);
                                
                                sz = pChild->Attribute("Z");
                                if(sz) z = atof(sz);
                                
                                TAD_POINT coords = POINT(x,y,z); //vector de coordenadas
                                points.push_back(coords);
                            }
                            pChild = pChild->NextSiblingElement("point");
                        }
                    }
                }

                Operation op = Operation('t', points, time);
                t = true;
                group.operacoes.push_back(op);
            }

            else {
                perror("2 or more translation in same GROUP!\n");
                exit(1);
            }
        }
        
        else if(name.compare("rotate")==0) {
            
            if(!r) {
                
                sx = pRoot->Attribute("axisX");
                if(sx) x = atof(sx);
                
                sy = pRoot->Attribute("axisY");
                if(sy) y = atof(sy);
                
                sz = pRoot->Attribute("axisZ");
                if(sz) z = atof(sz);
                
                stime = pRoot->Attribute("time");
                if(stime) time = atoi(stime);
                
                vector<TAD_POINT> points;
                points.push_back(POINT(x,y,z));
                Operation op = Operation('r', points, time);
                r = true;
                group.operacoes.push_back(op);
            }

            else {
                perror("2 or more rotate in same GROUP!\n");
                exit(2);
            }
        }

        else if(name.compare("scale")==0) {
            
            if(!s) {
                sx = pRoot->Attribute("X");
                if(sx) x = atof(sx);
                
                sy = pRoot->Attribute("Y");
                if(sy) y = atof(sy);
                
                sz = pRoot->Attribute("Z");
                if(sz) z = atof(sz);
                
                vector<TAD_POINT> points;
                points.push_back(POINT(x,y,z));
                Operation op = Operation('s', points, time);
                s = true;
                group.operacoes.push_back(op);
            }
            else {
                perror("2 or more scale in same GROUP!\n");
                exit(3);
            }
        }

        else if(name.compare("models")==0) {
            
            if(!m) {
               
                pChild = pRoot->FirstChildElement("model");
                
                while(pChild) {
                    
                    name = (string)pChild->Attribute("file");
                    textura = (string)pChild->Attribute("texture");

                    if (name.compare("") != 0) {

                        (*nGrupos) += 1;
                        if(figuras.find(name) == figuras.end()) { // se não  existir 
                            //Tamanho dos indices iguais para todos
                            int indicesTAM; 

                            //points
                            unsigned int* indexPoints; 
                            float* points;   
                            int pointsTAM;

                            //normals
                            float* normals;
                            int normalsTAM;

                            //texCoords
                            float* texCoords; 
                            int texCoordsTAM;
                            
                            file2list(name, &indicesTAM, &indexPoints, &points, &pointsTAM, &normals, &normalsTAM, &texCoords, &texCoordsTAM);
                            
                            Figura f = Figura(indicesTAM, indexPoints, points, pointsTAM, normals, normalsTAM, texCoords, texCoordsTAM);
                            figuras.insert( std::pair<string,Figura>(name,f));
							if (textura.compare("") != 0) {
								texturas.insert(std::pair<string, Textura>(textura, loadTexture(textura)));
							}
                        }
                        
                        group.ficheiros.push_back(name);
						group.texturas.push_back(textura);
                    }

                    pChild = pChild->NextSiblingElement("model");
                }

                m = true;
            }
            else {
                perror("2 or more models in same GROUP!\n");
                exit(4);
            }
        }

        else if(name.compare("group")==0) {
            group.filhos.push_back( searchRec(figuras,texturas, nGrupos, pRoot));
        }

        pRoot = pRoot->NextSiblingElement(); // grupos encadeados
    }

    return group;
}

/*static Ligths searchLigths() {

}*/

void parse(Group &group, map<string,Figura> &figuras, map<string,Textura> textures, int *nGrupos, const char* path){
    TiXmlDocument doc(path);
    if(doc.LoadFile()) {
        TiXmlElement *pRoot,*pChild;
        pRoot = doc.FirstChildElement("scene");
        if(pRoot) {
            pChild = pRoot->FirstChildElement("ligths");
            if(pChild) {
                //ligths = searchLigths(pRoot);
            }

            pChild = pRoot->FirstChildElement("group");
            if(pChild) {
                group = searchRec(figuras, textures, nGrupos, pRoot);
            }
        }
    }
    else {
        perror("ERROR => Could not load XML File!\n");
        exit(1);
    }
}
