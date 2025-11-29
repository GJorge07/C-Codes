/*Protótipo da chamada do loop dos eventos (conjunto de ações que serão realizadas no mundo)*/
#ifndef CHAMA_EVENTOS_H
#define CHAMA_EVENTOS_H

#include "entidades.h"
#include "lista.h"           
#include "fprio.h"
#include "conjunto.h"
#include "eventos.h"

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5 
#define SAI 6 
#define VIAJA 7 
#define MORRE 8 
#define MISSAO 9 
#define FIM 10

void chama_eventos(mundo_t *mundo);

#endif
