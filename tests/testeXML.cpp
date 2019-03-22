#include <tinyxml.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <group.h>
#include <operation.h>
#include <vector>

using namespace std;

static Group searchRec(TiXmlElement *pRoot) {
    bool t = false, r = false, s = false, m = false;
    pRoot = pRoot->FirstChildElement();
    Group group = Group();
    while(pRoot) {
        string name = (string)pRoot->Value();
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
                Operation op = Operation('t',x,y,z,angle);
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
                sangle = pRoot->Attribute("angle");
                if(sangle) angle = atof(sangle);
                sx = pRoot->Attribute("axisX");
                if(sx) x = atof(sx);
                sy = pRoot->Attribute("axisY");
                if(sy) y = atof(sy);
                sz = pRoot->Attribute("axisZ");
                if(sz) z = atof(sz);
                Operation op = Operation('r',x,y,z,angle);
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
                Operation op = Operation('s',x,y,z,angle);
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
                TiXmlElement *pChild = pRoot->FirstChildElement("model");
                while(pChild) {
                    name = (string)pChild->Attribute("file");
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
            group.filhos.push_back(searchRec(pRoot));
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
    perror("Could not load XML File\n");
    exit(1);
}

void printGroup(Group g) {
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

int main() {
    Group a = parse("file.xml");
    printGroup(a);
    return 0;
}