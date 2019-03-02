#ifndef TAD_COMUNITY_H
#define TAD_COMUNITY_H

#include <ArrayList.h>

/**
@file globalstruct.h
Módulo que contém as funções de criação, manipulação e destruição da estrutura global.
*/

/**\brief Cria a modularidade para a estrutura TCD_community*/
typedef struct TCD_community* TAD_community;

/* Construtor */
TAD_community TAD_COMUNITY(void); // controi a estrutura global

/* Getters */
TAD_ARRAY_LIST getModels (TAD_community com);

/* Setters */
void addModel(char* model, TAD_community com);

/* free */
void free_TAD_community(TAD_community com);


//  ----- PARA DEBUGGING -------------------------------------------------------
void printTAD_community(TAD_community com); // imprime a Globalstruct

#endif