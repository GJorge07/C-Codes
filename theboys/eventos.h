//Implementação dos protótipos das funções dos possíveis eventos no mundo

#ifndef EVENTOS_H
#define EVENTOS_H

#include "entidades.h"
#include "lista.h"            
#include "fprio.h"
#include "conjunto.h"


/*Definidos assim principalmente para facilitar no switch case do chama_eventos*/

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

struct chega {  

    int tempo;
    int heroi;
    int base;

};

struct espera {

    int tempo;
    int heroi;
    int base;

};

struct desiste {

    int tempo;
    int heroi;
    int base;

};

struct avisa {
    
    int tempo;   
    int base;

};

struct entra {
    
    int tempo;
    int heroi;
    int base;

};

struct sai {

    int tempo;
    int heroi;
    int base;

};

struct viaja {

    int tempo;
    int heroi;
    int base;

};

struct morre {

    int tempo;
    int heroi;
    int base;

};

struct missao {

    int tempo;
    int missao;

};

struct fim {

    int tempo;

};

/*funções que implementam a lógica de cada evento.*/
/*mundo_t *mundo é o estado global da simulação e evento_t *evento é o evento que está sendo feito*/

void eventos_iniciais(mundo_t *mundo);

void evento_chega(mundo_t *mundo, struct chega *chega);

void evento_espera(mundo_t *mundo, struct espera *espera);

void evento_desiste(mundo_t *mundo, struct desiste *desiste);

void evento_avisa(mundo_t *mundo, struct avisa *avisa);

void evento_entra(mundo_t *mundo, struct entra *entra);

void evento_sai(mundo_t *mundo, struct sai *sai);

void evento_viaja(mundo_t *mundo, struct viaja *viaja);

void evento_morre(mundo_t *mundo, struct morre *morre);

void evento_missao(mundo_t *mundo, struct missao *missao);

void evento_fim(mundo_t *mundo, struct fim *fim);


#endif