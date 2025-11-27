//Implementação do loop principal da simulação -> pega o evento, lê o tiṕo, chama a função e repete até acabar (FIM)

//includes
#include "chama_eventos.h"
#include "eventos.h"

void chama_eventos(mundo_t *mundo) {

    int continuar = 1;

    while (continuar && fprio_tamanho(mundo->lef) > 0) {        //enquanto continuar for 1 e tiver evento na lef

        int tipo, prio;
        void *item_escolhido = fprio_retira(mundo->lef, &tipo, &prio); //VOIDDD????   //item_escolhido é o evento retirado da lef

        if (item_escolhido == NULL) 
            break;

        switch (tipo) {                        //verifica o tipo do evento e chama a função correspondente

            case CHEGA:
                evento_chega(mundo, item_escolhido);
                break;

            case SAI:
                evento_sai(mundo, item_escolhido);
                break;

            case VIAJA:
                evento_viaja(mundo, item_escolhido);
                break;

            case MORRE:
                evento_morre(mundo, item_escolhido);
                break;

            //case MISSAO:
                //evento_missao(mundo, item_escolhido);
                //break;

            //case FIM:
                //evento_fim(mundo, item_escolhido);
                //continuar = 0;   // encerra o while
                //break;
        }

        free(item_escolhido);  //toda vez que um evento é processado, libera a memória alocada para ele, pois ele sai da fprio e fica "perdido"
    }
}
