#include <tinyxml.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

static void searchRec(TiXmlElement *pRoot) {
    
    pRoot = pRoot->FirstChildElement();
    while(pRoot) {
        string name = (string)pRoot->Value();
        if(name.compare("translate")==0) {
            const char* x = pRoot->Attribute("X");
            const char* y = pRoot->Attribute("Y");
            const char* z = pRoot->Attribute("Z");
            printf("TRANSLATE: X=%s Y=%s Z=%s \n",x,y,z);
        }
        else if(name.compare("rotate")==0) {
            const char* angle = pRoot->Attribute("angle");
            const char* x = pRoot->Attribute("axisX");
            const char* y = pRoot->Attribute("axisY");
            const char* z = pRoot->Attribute("axisZ");
            printf("ROTATE: Angle=%s X=%s Y=%s Z=%s \n",angle,x,y,z);
        }
        else if(name.compare("scale")==0) {
            const char* x = pRoot->Attribute("X");
            const char* y = pRoot->Attribute("Y");
            const char* z = pRoot->Attribute("Z");
            printf("SCALE: X=%s Y=%s Z=%s \n",x,y,z);
        }
        else if(name.compare("models")==0) {
            TiXmlElement *pChild = pRoot->FirstChildElement("model");
            printf("MODELS:\n");
            while(pChild) {
                name = (string)pChild->Attribute("file");
                cout << "File= " + name + "\n";
                pChild = pChild->NextSiblingElement("model");
            }
        }
        else if(name.compare("group")==0) {
            printf("GROUP\n");
            searchRec(pRoot);
        }
        //char* str = (char*) malloc(sizeof(char)*(strlen(fileName)+1));
        //strcpy(str, fileName);
        pRoot = pRoot->NextSiblingElement();
    }
}

static void parse(const char* path){
    TiXmlDocument doc(path);
    if(doc.LoadFile())
    {
        // doc.Print( stdout );
        TiXmlElement *pRoot;
        pRoot = doc.FirstChildElement("scene");
        if(pRoot) {
            pRoot = pRoot->FirstChildElement("group");
            if(pRoot) {
                searchRec(pRoot);
            }
        }
    }
    else 
    {
        perror("Could not load XML File");
        exit(1);
    }
    //return fileNames;
}

int main() {
    parse("file.xml");
    return 0;
}