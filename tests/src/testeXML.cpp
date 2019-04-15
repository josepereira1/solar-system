#include <tinyxml.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <group.h>
#include <operation.h>
#include <vector>
#include <Figura.h>
#include <Point.h>
#include <map>
#include <xmlParser.h>

using namespace std;

static void printGroup(Group g) {
    printf("GROUP:-----------------------------------------------\n");
    for(unsigned i = 0; i<g.operacoes.size() ;i++) {
        Operation op = g.operacoes[i];
        if(op.flag == 't') {
            printf("Operacao: Flag=%c ,Angle=%f ,Time=%d\n",op.flag,op.ang,op.time);
            for(unsigned j = 0; j<op.point.size() ; j++) {
                TAD_POINT point = op.point[j];
                printf("\tPoint: X=%f ,Y=%f ,Z=%f\n",getX(point),getY(point),getZ(point));
            }

        }
        else {
            TAD_POINT point = op.point[0];
            printf("Operacao: Flag=%c ,X=%f ,Y=%f ,Z=%f ,Angle=%f ,Time=%d\n",op.flag,getX(point),getY(point),getZ(point),op.ang,op.time);
        }
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

static void printFiguras(map<string,Figura> figuras) {
    map<string, Figura>::iterator it;
    for (it = figuras.begin(); it != figuras.end(); it++) {
        vector<float> pontos = it->second.pontos;
        for(unsigned k=0; k<pontos.size(); k+=3) {
            printf("file:%s => X=%f, Y=%f, Z=%f\n", it->first.c_str(), pontos[k], pontos[k+1], pontos[k+2]);
        }
    }
}

int main() {
    Group group;
    map<string,Figura> figuras;
    parse(group,figuras,"xmlTest.xml");
    printGroup(group);
    //printFiguras(figuras);
    return 0;
}