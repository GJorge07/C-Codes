/* Implementação do loop principal da simulação -> pega o evento, lê o tiṕo, chama a função e repete até acabar (FIM) */
#include <stdio.h>
#include <stdlib.h>

#include "entidades.h"
#include "chama_eventos.h"
#include "eventos.h"
#include "fprio.h"


void chama_eventos(mundo_t *mundo) {

    int continuar = 1;

    while (continuar && fprio_tamanho(mundo->lef) > 0) {        

        int tipo, prio;         /*prio representa o tempo que o evento ocorre*/
        void *item_escolhido = fprio_retira(mundo->lef, &tipo, &prio); /* item_escolhido é o evento retirado da lef */

        if (item_escolhido == NULL) 
            break;

         mundo->relogio = prio;            

        switch (tipo) {                        /* verifica o tipo do evento e chama a função correspondente */
            
            case CHEGA:
                evento_chega(mundo, (struct chega*)item_escolhido);
                break;

            case ESPERA:
                evento_espera(mundo, (struct espera*)item_escolhido);
                break;

            case DESISTE:
                evento_desiste(mundo, (struct desiste*)item_escolhido);
                break;

            case AVISA:
                evento_avisa(mundo, (struct avisa*)item_escolhido);
                break;

            case ENTRA:
                evento_entra(mundo, (struct entra*)item_escolhido);
                break;

            case SAI:
                evento_sai(mundo, (struct sai*)item_escolhido);
                break;

            case VIAJA:
                evento_viaja(mundo, (struct viaja*)item_escolhido);
                break;

            case MORRE:
                evento_morre(mundo, (struct morre*)item_escolhido);
                break;

            case MISSAO: {
                int id = ((struct evento_missao*)item_escolhido)->id;
                missao_t *m = mundo->missoes[id];        /* pega a missão real */
                evento_missao(mundo, m);                 
                break;
            }


            case FIM:
                evento_fim(mundo, (struct fim*)item_escolhido);
                continuar = 0; 
                break;
        }

        /* toda vez que um evento é processado, libera a memória alocada para ele, pois ele sai da fprio e fica "perdido" */
        free(item_escolhido);  
    
    }
}
