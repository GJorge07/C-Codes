/* Implementação da função que destrói tudo - bases, heróis, missões e o mundo como um todo. */
#include <stdio.h>
#include <stdlib.h>

#include "entidades.h"
#include "destroi_mundo.h"
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"

void destroi_mundo(mundo_t *mundo) {

    if (!mundo)
        return;

    /* destroi herois */
    for (int i = 0; i < mundo->nherois; i++) {      
        cjto_destroi(mundo->herois[i]->habilidades);     /* destroi habilidades, uma por uma */
        free(mundo->herois[i]);                          /* destroi herois, um por um */
    }
    free(mundo->herois);                                /* destroi o local onde tavam todos os herois */

    /* destroi bases */
    for (int i = 0; i < mundo->nbases; i++) {
        cjto_destroi(mundo->bases[i]->presentes);      /* destroi conjunto de presentes, um por um */
        fila_destroi(mundo->bases[i]->espera);        /* destroi fila de espera, uma por uma */
        free(mundo->bases[i]);                        /* destroi bases, uma por uma */    
    }
    free(mundo->bases);                                /* destroi o local onde tavam todas as bases */
    
    /* destroi missoes */
    for (int i = 0; i < mundo->nmissoes; i++) {
        cjto_destroi(mundo->missoes[i]->habilidades_missao); /* destroi conjunto de habilidades da missao, uma por uma */
        free(mundo->missoes[i]);                            /* destroi missoes, uma por uma */  
    }
    free(mundo->missoes);                                    /* destroi o local onde tavam todas as missoes */

    /* destroi lista de eventos futuros */
        fprio_destroi(mundo->lef);                      

    /* destroi mundo */
    free(mundo);
}

/* Vai destruindo de cima pra baixo, em cada struct, se há uma outra struct com ponteiro, chama a função de destruição dela primeiro, como habilidades, presentes, fila de espera, etc. Depois libera a struct em si. Depois libera o vetor de ponteiros e no final libera a lef e o mundo. */