#include <tinyxml.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "../include/group.h"
#include <vector>

using namespace std;

static Group searchRec(TiXmlElement *pRoot) {
    bool t = false, r = false, s = false, m = false;
    pRoot = pRoot->FirstChildElement();
    Group group = Group();
    while(pRoot) {
        string name = (string)pRoot->Value();
        Operation op;
        float x=0.0f,y=0.0f,z=0.0f,angle=0.0f;
        const char *sx,*sy,*sz,*sangle;
        if(name.compare("translate")==0) {
            if(!t) {
                sx = pRoot->Attribute("X");
                if(sx) x = atof(sx);
                sy = pRoot->Attribute("Y");
                if(sy) y = atof(sy);
                sz = pRoot->Attribute("Z");
                if(sz) z = atof(sz);
                op = Operation('t',x,y,z,angle);
                printf("TRANSLATE: X=%f Y=%f Z=%f\n",x,y,z);
                t = true;
                group.operacoes.add(op);
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
                op = Operation('r',x,y,z,angle);
                printf("ROTATE: Angle=%f X=%f Y=%f Z=%f\n",angle,x,y,z);
                r = true;
                group.operacoes.add(op);
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
                op = Operation('s',x,y,z,angle);
                printf("SCALE: X=%f Y=%f Z=%f\n",x,y,z);
                s = true;
                group.operacoes.add(op);
            }
            else {
                perror("2 or more scale in same GROUP!\n");
                exit(3);
            }
        }
        else if(name.compare("models")==0) {
            if(!m) {
                TiXmlElement *pChild = pRoot->FirstChildElement("model");
                printf("MODELS:\n");
                while(pChild) {
                    name = (string)pChild->Attribute("file");
                    group.ficheiros.add(name);
                    cout << "File= " + name + "\n";
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
            printf("GROUP\n");
            group.filhos.add(searchRec(pRoot));
        }
        pRoot = pRoot->NextSiblingElement();
    }
    return group;
}

static Group parse(const char* path){
    TiXmlDocument doc(path);
    if(doc.LoadFile()) {
        TiXmlElement *pRoot;
        pRoot = doc.FirstChildElement("scene");
        if(pRoot) {
            pRoot = pRoot->FirstChildElement("group");
            if(pRoot) {
                return searchRec(pRoot);
            }
        }
    }
    else {
        perror("Could not load XML File\n");
        exit(1);
    }
    //return NULL;
}

int main() {
    Group a = parse("file.xml");
    return 0;
}