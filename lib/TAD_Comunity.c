#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <TAD_Comunity.h>
#include <ArrayList.h>

#define MODELS_DIM_INICIAL        1

/**
@file TAD_Comunity.c
Módulo que contém as funções de criação, manipulação e destruição da estrutura global.
*/

/**\brief Estrutura global que contem as sub-estruturas com informação de posts, utilizadores, tacom e datas*/
typedef struct TCD_community{

  /**\brief ArrayList que contem os nomes dos modelos*/
  TAD_ARRAY_LIST models;  

} TCD_community;


/**
\brief Cria a estrutura global.
@return retorna a estrutura
*/
TAD_community TAD_COMUNITY(){ // cria estrutura global que contem as hash tables de users e posts
    TAD_community com = malloc(sizeof(TCD_community));
    com->models = ARRAY_LIST(MODELS_DIM_INICIAL);
    return com;
}


/**
\brief Retorna o ArrayList que contem a informação dos Modelos.
@param com - estrutura global
@return retorna o ArrayList
*/
TAD_ARRAY_LIST getModels (TAD_community com){
  return com->models;
}


/**
\brief Adiciona um modelo ao ArrayList que contem os modelos.
@param model - modelo
@param com - estrutura global
*/
void addModel(char* model, TAD_community com){
  char* tmp = malloc((strlen(model)+1)*sizeof(char));
  strcpy(tmp,model);
  addElem(com->models, (void*) tmp);
}


static void free_ARRAY_LIST_models(TAD_ARRAY_LIST models){
    if (models){
        for (int i = 0; i < getArraySize(models); i++){
            char* elem = (char*) getElem (models, i);
            if (elem) {
              free(elem);
              elem = NULL;
            }
        }
        free_ARRAY_LIST(models);
    }
}


/**
\brief Liberta a zona de memória alocada para a estrutura global.
@param com - estrutura global
*/
void free_TAD_community(TAD_community com){
  if (com){
    free_ARRAY_LIST_models(com->models);
    free(com);
    com = NULL;
  }
}


//  ----- PARA DEBUGGING -------------------------------------------------------

/**
\brief Imprime no STD_OUT uma representação da Tabela de Hash.
@param com - estrutura global
*/
void printTAD_community(TAD_community com){
  for(int i = 0; i < getArraySize(com->models); i++){
    printf("%s\n", (char*) getElem (com->models, i));
  }
}