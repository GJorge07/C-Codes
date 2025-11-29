/*Protótipos das entidades, onde cada struct(entidade) tem seus próprios atributos declarados.*/
#ifndef ENTIDADES_H
#define ENTIDADES_H

#include "conjunto.h"
#include <math.h>
#include "fila.h"                 
#include "fprio.h"
#include "lista.h"
struct localizacao {

    int x;
    int y;
};

struct heroi {

    int id;
    struct cjto_t *habilidades;
    int paciencia;
    int velocidade;
    int experiencia;
    int base_atual;   
    int vivo;  /* 1 vivo e 0 morto */   
       
};

struct base {

    int id;
    int lotacao;
    struct cjto_t *presentes;  
    struct fila_t *espera;
    struct localizacao local_base;
    int missoes_cumpridas;
    int fila_max;

};

struct missao {

    int id;
    struct cjto_t *habilidades_missao;
    struct localizacao local_missao;
    int cumprida;        /*1 cumprida e 0 não cumprida */
    int tentativas;     /*numero de tentativas de cumprimento da missão*/
    int tempo;

};

struct mundo {

    int nherois;
    struct heroi **herois;      /* h* representa 1 heroi -> ** é vetor p representar varios herois */

    int nbases;
    struct base **bases;     

    int nmissoes;
    struct missao **missoes;

    int nhabilidades;
    
    int ncompostosv;

    int neventos;

    struct localizacao tamanho_mundo;

    int relogio;            /* tempo atual do mundo */

    struct fprio_t *lef;         
};

typedef struct heroi heroi_t;
typedef struct base base_t;
typedef struct missao missao_t;
typedef struct mundo mundo_t;

#endif