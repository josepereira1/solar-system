#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <string.h>

#include <xmlParser.h>
#include <ArrayList.h>
#include <Point.h>
#include <file2list.h>

static void search_elements(xmlTextReaderPtr node, TAD_ARRAY_LIST fileNames){
    xmlChar *attribVal = NULL;
    while(xmlTextReaderRead(node)){    //  enquanto não dá erro ou existe algo para ler
        attribVal = xmlTextReaderLocalName(node);
        if (attribVal){
            if (strcmp((char*) attribVal, "model") != 0){
                xmlFree(attribVal);
                continue;
            }
            xmlFree(attribVal);
        }
        attribVal = xmlTextReaderGetAttribute(node, (const xmlChar*) "file");  
        if (attribVal){
            int len = strlen((char*) attribVal);
            char* str = malloc(sizeof(char) * (len+1)); // +1 por causa do '\0'
            strcpy(str, (char*) attribVal);
            xmlFree(attribVal);
            addElem(fileNames, str);
        } 
    }
}


static TAD_ARRAY_LIST getFileNames(const char* path){
    LIBXML_TEST_VERSION
    xmlTextReaderPtr tree = NULL;
    if ((tree = xmlReaderForFile(path, NULL, 0)) == NULL ) {
        char* errorMsg = malloc(sizeof(char)*(strlen(path)+21));
        sprintf(errorMsg, "could not open file %s", path);
        perror(errorMsg);
        free(errorMsg);
        exit(1);
    }
    TAD_ARRAY_LIST fileNames = ARRAY_LIST(1);
    if (tree) {
        search_elements(tree, fileNames);
        xmlFreeTextReader(tree);
    }
    // printf("models parser done!\n");
    return fileNames;
}


TAD_ARRAY_LIST getPointsFromFiles(const char* path) {
    TAD_ARRAY_LIST fileNames = getFileNames(path);
    TAD_ARRAY_LIST res = ARRAY_LIST(50);
    for(int i=0; i<getArraySize(fileNames); i++) {
        char* fileName = (char*) getElem(fileNames, i);
        printf("file=%s\n", fileName);
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

