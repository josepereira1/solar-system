#include <xmlParser.h>
#include <tinyxml.h>	
#include <iostream>
#include <operation.h>
#include <fromFile.h>
#include <math.h>
#include <../toolkits/devil/IL/il.h>

using namespace std;

Textura loadTexture(string s) {
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
    Textura tex = Textura(texID); 
    
    glBindTexture(GL_TEXTURE_2D,texID);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_S,      GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_WRAP_T,      GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MAG_FILTER,      GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,  GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

// DEBUG
static void printFigura(Figura f) {
	printf("indicesTAM=%d\n", f.indicesTAM);
	int i;
	for (i = 0; i < f.indicesTAM-1; i++) {
		printf("%d, ", f.indexPoints[i]);
	}
	printf("%d", f.indexPoints[i]);
	printf("\npointsTAM=%d\n", f.pointsTAM);
	for (i = 0; i < f.pointsTAM-1; i++) {
		printf("%.5f, ", f.points[i]);
	}
	printf("%.5f", f.points[i]);
	printf("\nnormalsTAM=%d\n", f.normalsTAM);
	for (i = 0; i < f.normalsTAM-1; i++) {
		printf("%.5f, ", f.normals[i]);
	}
	printf("%.5f", f.normals[i]);
	printf("\ntexCoordsTAM=%d\n", f.texCoordsTAM);
	for (i = 0; i < f.texCoordsTAM-1; i++) {
		printf("%.5f, ", f.texCoords[i]);
	}
	printf("%.5f", f.texCoords[i]);
	printf("\n\n\n\n\n\n\n"); // para separar as figuras de modo legível
}

static Group searchRec(map<string,Figura> &figuras, map<string,Textura> &texturas, int *nGrupos, TiXmlElement *pRoot) {
    
    bool t = false, r = false, s = false, m = false;
    pRoot = pRoot->FirstChildElement();
    TiXmlElement *pChild;
    
    Group group = Group();
    
    while(pRoot) {
        string name = (string)pRoot->Value();
        string textura;

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

                    if (name.compare("") != 0) {
						(*nGrupos) += 1;
						if (figuras.find(name) == figuras.end()) { // se não  existir 
							//Tamanho dos indices iguais para todos
							int indicesTAM;

							//points
							unsigned int* indexPoints;
							float* points;
							int pointsTAM;

							//normals
                            int indexNormalsTAM;
							unsigned int* indexNormals;
							float* normals;
							int normalsTAM;

							//texCoords
                            int indexTexCoordsTAM;
							unsigned int* indexTexCoords;
							float* texCoords;
							int texCoordsTAM;

							file2list(name, &indicesTAM, &indexPoints, &points, &pointsTAM, &indexNormalsTAM, &indexNormals, &normals, &normalsTAM, &indexTexCoordsTAM, &indexTexCoords, &texCoords, &texCoordsTAM);
							Figura f = Figura(indicesTAM, indexPoints, points, pointsTAM, indexNormalsTAM, indexNormals, normals, normalsTAM, indexTexCoordsTAM, indexTexCoords, texCoords, texCoordsTAM);

							figuras.insert(pair<string, Figura>(name, f));
						}

						textura = (string)pChild->Attribute("texture");
						if ((textura.compare("") != 0) && textura.compare("DIFF") != 0 && textura.compare("AMB") != 0 && textura.compare("EMI") != 0 && textura.compare("SPEC") != 0 ) {
							if(texturas.find(textura) == texturas.end()) 
								texturas.insert(pair<string, Textura>(textura, loadTexture(textura)));
						}
						else {
                            TAD_POINT p = POINT(1.0f, 1.0f, 1.0f);
                            string diff,amb,emi,spec;
                            if(textura.compare("DIFF") == 0){
							    p = POINT(atof(pChild->Attribute("diffX")), atof(pChild->Attribute("diffY")), atof(pChild->Attribute("diffZ")));
                            }
                             else if(textura.compare("AMB") == 0)
                                p = POINT(atof(pChild->Attribute("ambX")), atof(pChild->Attribute("ambY")), atof(pChild->Attribute("ambZ")));
                             else if(textura.compare("EMI") == 0)
                                p = POINT(atof(pChild->Attribute("emiX")), atof(pChild->Attribute("emitY")), atof(pChild->Attribute("emiZ")));
                            else if(textura.compare("SPEC")) p = POINT(atof(pChild->Attribute("specX")), atof(pChild->Attribute("specY")), atof(pChild->Attribute("specZ")));
                            else{}
							group.materials.push_back(p);
						}
						group.ficheiros.push_back(name);
						if (textura.compare("") != 0)
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

static vector<Light> searchLights(TiXmlElement *pRoot) {
	vector<Light> lights = vector<Light>();

	string tipo = "";

	while (pRoot) {
		const char *posX, *posY, *posZ, *spotX, *spotY, *spotZ;
		float pos[4];
		float diff[4];
		float amb[4];
		float spot[3];
		pos[0] = 0; pos[1] = 0; pos[2] = 0; pos[3] = 0;
		diff[0] = 1.0f; diff[1] = 1.0f; diff[2] = 1.0f; diff[3] = 1.0f;
		amb[0] = 0.2f; amb[1] = 0.2f; amb[2] = 0.2f; amb[3] = 1.0f;
		spot[0] = 0; spot[1] = 0; spot[2] = 0;

		string name = (string) pRoot->Value();
		if (name.compare("light") == 0) {
			tipo = (string) pRoot->Attribute("type");

			posX = pRoot->Attribute("posX");
			if (posX) pos[0] = atof(posX);
			posY = pRoot->Attribute("posY");
			if (posY) pos[1] = atof(posY);
			posZ = pRoot->Attribute("posZ");
			if (posZ) pos[2] = atof(posZ);

			if (tipo.compare("POINT") == 0) {
				pos[3] = 1.0f;
				lights.push_back(Light('p', pos[0],pos[1],pos[2],pos[3], diff[0],diff[1],diff[2],diff[3], amb[0],amb[1],amb[2],amb[3], spot[0],spot[1],spot[2]));
			}
			else if (tipo.compare("DIRECTIONAL") == 0) {
				pos[3] = 0;
				lights.push_back(Light('d', pos[0], pos[1], pos[2], pos[3], diff[0], diff[1], diff[2], diff[3], amb[0], amb[1], amb[2], amb[3], spot[0], spot[1], spot[2]));
			}
			else if (tipo.compare("SPOT") == 0) {
				pos[3] = 1.0f;
				spotX = pRoot->Attribute("spotX");
				if (spotX) spot[0] = atof(spotX);
				spotY = pRoot->Attribute("spotY");
				if (spotY) spot[1] = atof(spotY);
				spotZ = pRoot->Attribute("spotZ");
				if (spotZ) spot[2] = atof(spotZ);
				lights.push_back(Light('s', pos[0], pos[1], pos[2], pos[3], diff[0], diff[1], diff[2], diff[3], amb[0], amb[1], amb[2], amb[3], spot[0], spot[1], spot[2]));
			}
		}
		
		//printf("pos= %f , %f , %f , %f\n", pos[0], pos[1], pos[2], pos[3]);
		//printf("diff= %f , %f , %f , %f\n", diff[0], diff[1], diff[2], diff[3]);
		//printf("amb= %f , %f , %f , %f\n", amb[0], amb[1], amb[2], amb[3]);
		//printf("spot= %f , %f , %f\n", spot[0], spot[1], spot[2], spot[3]);
		pRoot = pRoot->NextSiblingElement(); //próximas luzes
	}
	return lights;
}

void parse(Group &group, vector<Light> &lights, map<string,Figura> &figuras, map<string,Textura> &textures, int *nGrupos, const char* path){
    TiXmlDocument doc(path);
    if(doc.LoadFile()) {
        TiXmlElement *pRoot,*pChild,*pChild2;
        pRoot = doc.FirstChildElement()->FirstChildElement();
        if (pRoot) {
			pChild = pRoot->FirstChildElement();
			pChild2 = pRoot->NextSiblingElement();
			if (pChild) {
				lights = searchLights(pChild);
			}
			if (pChild2) {
				group = searchRec(figuras, textures, nGrupos, pChild2);
			}

        }
    }
    else {
        perror("ERROR => Could not load XML File!\n");
        exit(1);
    }
}
