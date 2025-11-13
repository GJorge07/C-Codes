//Protótipos das entidades, onde cada struct(entidade) tem seus próprios atributos declarados.

#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdbool.h>
#include <stdlib.h>
#include "conjunto.h"
#include <math.h>
#include "fila.h"                 //nn tenho ctz de quais precisa ou n


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
};

struct base {

    int id;
    int lotacao;
    struct cjto_t *presentes;  
    struct fila_t *espera;
    struct localizacao local_base;

};

struct missao {

    int id;
    struct cjto_t *habilidades_missao;
    struct localizacao local_missao;

};

struct mundo {

    int nherois;
    struct heroi **herois;      //h* representa 1 heroi -> ** é vetor p representar varios herois

    int nbases;
    struct base **bases;     

    int nmissoes;
    struct missao **missoes;

    int nhabilidades;
    
    int ncompostosv;

    struct localizacao tamanho_mundo;

    int relogio;

};

typedef struct localizacao localizacao_t;
typedef struct heroi heroi_t;
typedef struct base base_t;
typedef struct missao missao_t;
typedef struct mundo mundo_t;

#endif