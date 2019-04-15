#include <tinyxml.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <group.h>
#include <operation.h>
#include <vector>
#include <Figura.h>
#include <map>
#include <file2list.h>

using namespace std;

static Group searchRec(map<string,Figura> &figuras, TiXmlElement *pRoot) {
    bool t = false, r = false, s = false, m = false;
    pRoot = pRoot->FirstChildElement();
    //Descomentar próxima linha
    //TiXmlElement *pChild;
    Group group = Group();
    while(pRoot) {
        string name = (string)pRoot->Value();
        float x=0.0f,y=0.0f,z=0.0f,angle=0.0f;
        //Descomentar próxima linha e acrescentar o stime na linha a seguir
        //int time=0;
        const char *sx,*sy,*sz,*sangle; //*stime;
        if(name.compare("translate")==0) {
            if(!t) {
                //Substituir as próximas linhas pelas que estão em comentário
                sx = pRoot->Attribute("X");
                if(sx) x = atof(sx);
                sy = pRoot->Attribute("Y");
                if(sy) y = atof(sy);
                sz = pRoot->Attribute("Z");
                if(sz) z = atof(sz);
                Operation op = Operation('t',x,y,z,angle);
                t = true;
                group.operacoes.push_back(op);
                /*
                stime = pRoot->Attribute("time");
                if(stime) time = atoi(stime);
                pChild = pRoot->NextSiblingElement();
                vector<Coordinate> coords;
                while(pChild) {
                    if(name.compare("point")==0) {
                        sx = pChild->Attribute("X");
                        if(sx) x = atof(sx);
                        sy = pChild->Attribute("Y");
                        if(sy) y = atof(sy);
                        sz = pChild->Attribute("Z");
                        if(sz) z = atof(sz);
                        Coordinate coord = Coordinate(x,y,z);
                        coords.push_back(coord); //vector de coordenadas (3 floats cada coordenada) necessario class coordinate
                    }
                    pChild = pChild->NextSiblingElement("point");
                }
                Operation op = Operation('t',coords,angle,time);
                t = true;
                group.operacoes.push_back(op);
                */
            }
            else {
                perror("2 or more translation in same GROUP!\n");
                exit(1);
            }
        }
        else if(name.compare("rotate")==0) {
            if(!r) {
                sangle = pRoot->Attribute("angle");
                if(sangle) angle = atof(sangle);
                sx = pRoot->Attribute("axisX");
                if(sx) x = atof(sx);
                sy = pRoot->Attribute("axisY");
                if(sy) y = atof(sy);
                sz = pRoot->Attribute("axisZ");
                if(sz) z = atof(sz);
                //Substituir próximas 3 linhas pelas que estão em comentario
                Operation op = Operation('r',x,y,z,angle);
                r = true;
                group.operacoes.push_back(op);
              /*stime = pRoot->Attribute("time");
                if(stime) time = atoi(stime);
                Coordinate coord = Coordinate(x,y,z);
                vector<Coordinate> coords;
                coords.push_back(coord);
                Operation op = Operation('r',coords,angle,time);
                r = true;
                group.operacoes.push_back(op);
              */
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
                //Substituir próximas 3 linhas pelas que estão em comentario
                Operation op = Operation('s',x,y,z,angle);
                s = true;
                group.operacoes.push_back(op);
              /*Coordinate coord = Coordinate(x,y,z);
                vector<Cordinate> coords;
                coords.push_back(coord);
                Operation op = Operation('s',coords,angle,time);
                s = true;
                group.operacoes.push_back(op);
              */
            }
            else {
                perror("2 or more scale in same GROUP!\n");
                exit(3);
            }
        }
        else if(name.compare("models")==0) {
            if(!m) {
                //Retirar linha a baixo e descomentar a próxima
                TiXmlElement *pChild = pRoot->FirstChildElement("model");
                //pChild = pRoot->FirstChildElement("model");
                while(pChild) {
                    name = (string)pChild->Attribute("file");
                    if(figuras.find(name) == figuras.end()) { // se não  existir
                        // printf("name: %s\n", name.c_str());
                        Figura f;
                        f.pontos = file2list(name.c_str());
                        figuras[name] = f; 
                    }
                    //Descomentar proximas linhas apenas na Fase 4
                  /*texture = (string)pChild->Attribute("texture"); //Fase 4
                    if(texturas.find(texture) == texture.end()) { //se não existir
                        
                    }
                  */
                    group.ficheiros.push_back(name);
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
            group.filhos.push_back(searchRec(figuras, pRoot));
        }
        pRoot = pRoot->NextSiblingElement();
    }
    return group;
}

void parse(Group &group, map<string,Figura> &figuras, const char* path){
    TiXmlDocument doc(path);
    if(doc.LoadFile()) {
        TiXmlElement *pRoot; //*pChild;
        pRoot = doc.FirstChildElement("scene");
        if(pRoot) {
            pRoot = pRoot->FirstChildElement("group");
            //pChild = pRoot->FirstChildElement("group");
            //if(pChild) {
            if(pRoot) {
                group = searchRec(figuras,pRoot);
            }
          /*pChild = pRoot->FirstChildElement("ligths"); //Fase 4
            if(pChild) {
               ligths = searchLigths();
            }
          */
        }
    }
    else {
        perror("ERROR => Could not load XML File!\n");
        exit(1);
    }
}