/* Protótipo da inicialização do mundo */

#ifndef INICIA_MUNDO_H
#define INICIA_MUNDO_H

#include "entidades.h"
#include "lista.h"
#include "fprio.h"
#include "conjunto.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100) 
#define N_COMPOSTOS_V (N_HABILIDADES * 3)


mundo_t *inicia_mundo();   

#endif