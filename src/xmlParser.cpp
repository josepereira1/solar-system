#include <tinyxml.h>

#include <ArrayList.h>
#include <xmlParser.h>
#include <file2list.h>
#include <Point.h>

static TAD_ARRAY_LIST getFileNames(char* path){
    TiXmlDocument doc(path);

    if(doc.LoadFile())
    {
        // doc.Print( stdout );
        TiXmlElement *pRoot, *pParm;
        pRoot = doc.FirstChildElement("scene");
        if(pRoot)
        {
            pParm = pRoot->FirstChildElement("model");
            while(pParm)
            {
                const char* fileName = pRoot->ToElement()->Attribute("file");
                printf("%s\n", fileName);
                pParm = pParm->NextSiblingElement("model");
            }
        }
    }
    else 
    {
        perror("Could not load XML File");
        exit(1);
    }
}


TAD_ARRAY_LIST getPointsFromFiles(char* path) {
    TAD_ARRAY_LIST fileNames = getFileNames(path); // saca o nome dos ficheiros
    TAD_ARRAY_LIST res = ARRAY_LIST(50); // lista de pontos
    for(int i=0; i<getArraySize(fileNames); i++) {
        char* fileName = (char*) getElem(fileNames, i);
        TAD_ARRAY_LIST pontos = file2list(fileName);
        free(fileName);
        for(int v=0; v<getArraySize(pontos); v++) { // copia para o res
            TAD_POINT p = (TAD_POINT) getElem(pontos, v);
            addElem(res, p);
        }
        free_ARRAY_LIST(pontos);
    }
    return res;
}