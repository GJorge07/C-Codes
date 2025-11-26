//Implementação dos diversos tipos de eventos que podem acontecer no mundo.

//4 no documento - usar fila de prioridade

//includes - falta mais
#include "entidades.h"
#include "eventos.h"
#include "outras_funcoes.h"
#include <math.h>

//defines
#define T_FIM_DO_MUNDO 525600

void eventos_iniciais(mundo_t *mundo) {

    mundo->lef = fprio_cria();   // cria a fila de prioridade da lista de eventos futuros

    for (int i = 0; i < mundo->nherois; i++) {      //percorre todos os herois do mundo

        // cria o evento e insere heroi
        struct evento_t *ev = malloc(sizeof(struct evento_t));            //nn fiz typedef desse

        ev->tipo = CHEGA;
        ev->tempo = aleat(0, 4320);
        ev->heroi = i;                      //qual heroi chega em uma base aleat em um tempo aleat
        ev->base = aleat(0, mundo->nbases - 1);

        
        mundo->herois[i]->base_atual = ev->base;            //att base atual do heroi antes da simulação começar

        // lista(lef), item(ev), tipo(chega), prio(ev->tempo)
        fprio_insere(mundo->lef, ev, CHEGA, ev->tempo);
    }

    //insere missoes na lef
    for (int i=0; i < mundo->nmissoes; i++) {

        struct evento_t *ev = malloc(sizeof(struct evento_t));

        ev->tipo = MISSAO;
        ev->tempo = aleat(0,T_FIM_DO_MUNDO);            //cada missao m ocorre em um tempo aleat
        ev->missao = i;

        // lista(lef), item(ev), tipo(missao), prio(ev->tempo)
        fprio_insere(mundo->lef, ev, MISSAO, ev->tempo);
    }

    //insere fim na lef, serve p finalizar a simulação
     struct evento_t *ev = malloc(sizeof(struct evento_t));

     ev->tempo = T_FIM_DO_MUNDO;
     ev->tipo = FIM;

     fprio_insere(mundo->lef,ev,FIM,ev->tempo);

    //Quando o tempo chegar em 525.600, acabou a simulação.
}

void evento_chega(mundo_t *mundo, struct chega *chega) {

    struct espera *esp;

    if (!mundo || !chega)
        return;

    if (!heroi_valido(mundo, chega->heroi) || !base_valida(mundo, chega->base))
        return;

    mundo->herois[chega->heroi]->base_atual = chega->base;

    if (fila_tamanho(mundo->bases[chega->base]->espera) == 0 && mundo->bases[chega->base]->presentes < mundo->bases[chega->base]->lotacao )       //se há vagas em B e a fila de espera em B está vazia
        esp = 1;
    else 
        esp = mundo->herois[chega->heroi]->paciencia > (10 * mundo->bases[chega->base]->lotacao);
    

    if (esp) {
        cria_espera(mundo, chega->tempo, chega->heroi, chega->base);
        imprime_chega_e_espera(mundo, chega);
        
    }

    else {
        cria_desiste(mundo, chega->tempo, chega->heroi, chega->base);
        imprime_chega_e_desiste(mundo, chega);
    }
    
}

//heroi entra na fila de espera e porteiro é avisado
void evento_espera(mundo_t *mundo, struct espera *espera) {

    if (!mundo || !espera)          //Pra não dar seg fault antes
        return;

    if (!heroi_valido(mundo, espera->heroi) || !base_valida(mundo, espera->base)  || !fila_valida(mundo, espera->base))
        return;

    fila_insere(mundo->bases[espera->base]->espera, espera->heroi);     //insere heroi na base B

    cria_avisa(mundo, espera->tempo, espera->base);

    imprime_espera(mundo, espera);

}

void evento_desiste(mundo_t *mundo, struct desiste *desiste) {

    if(!mundo || !desiste)
        return;

    if (!heroi_valido(mundo, desiste->heroi) || !base_valida(mundo, desiste->base))
        return;

    int destino = aleat(0, mundo->nbases - 1);    // precisa do -1??

    cria_viaja(mundo, desiste->tempo, desiste->heroi, desiste->base, destino);

    imprime_desiste(mundo, desiste);
}

void evento_avisa(mundo_t *mundo, struct avisa *avisa) {          //ver se ta certo o loop

    if (!mundo || !avisa)
        return;

     if (!base_valida(mundo, avisa->base))
        return;

    int b = mundo->bases[avisa->base]->lotacao;          //vagas em B
    int h = cjto_card(mundo->bases[avisa->base]->presentes);   //herois presentes na base
    int tam_fila = fila_tamanho(mundo->bases[avisa->base]->espera);

    imprime_avisa_porteiro(mundo, avisa);

    while (tam_fila > 0 && b > h ) {            //n tenho ctz q ta certo

        int heroi_removido;

        fila_retira(mundo->bases[avisa->base]->espera, &heroi_removido);         //retira primeiro heroi da fila
        cjto_insere(mundo->bases[avisa->base]->presentes, heroi_removido);       //insere heroi na fila


        imprime_avisa_e_admite(avisa,heroi_removido);

        cria_entra(mundo, avisa->tempo, heroi_removido, avisa->base);

        h = cjto_card(mundo->bases[avisa->base]->presentes);   //herois presentes na base
        tam_fila = fila_tamanho(mundo->bases[avisa->base]->espera);
    }

}

void evento_entra(mundo_t *mundo, struct entra *entra) {

    if (!mundo || !entra)
        return;

    if (!heroi_valido(mundo,entra->heroi) || !base_valida(mundo,entra->base))
        return;

    int tpb = 15 + (mundo->herois[entra->heroi]->paciencia * aleat(1,20));
                    
    cria_sai (mundo, entra->tempo + tpb, entra->heroi, entra->base);

    imprime_entra(mundo, entra, entra + tpb);             //ver se é entra + tpb mesmo

}

void evento_sai(mundo_t *mundo, struct sai *sai) {

    if (!mundo || !sai) 
        return;

     if (!heroi_valido(mundo, sai->heroi) || !base_valida(mundo, sai->base))
        return;

    cjto_retira(mundo->bases[sai->base]->presentes, sai->heroi);    //retira o heroi do conjunto de herois em B
    int destino = aleat(0, mundo->nbases-1);    //escolhe base aleatoria

    cria_viaja(mundo, sai->tempo, sai->heroi, destino);
    cria_avisa(mundo, sai->tempo, sai->base);
    
    imprime_sai(mundo, sai);
}

void evento_viaja(mundo_t *mundo, struct viaja *viaja) {

    if (!mundo || !viaja)
        return;

    if (!heroi_valido(mundo, viaja->heroi) || !base_valida(mundo, viaja->destino))
        return;

    int x1 = mundo->bases[mundo->herois[viaja->heroi]->base_atual]->local_base.x;
    int y1 = mundo->bases[mundo->herois[viaja->heroi]->base_atual]->local_base.y;

    int x2 = mundo->bases[viaja->destino]->local_base.x;
    int y2 = mundo->bases[viaja->destino]->local_base.y;

    int formula1 = (x1 - x2) * (x1 - x2);
	int formula2 = (y1 - y2) * (y1 - y2);
	int formulageral = formula1 + formula2;

    int distancia = (int) sqrt(formulageral);

    int duracao = (distancia / mundo->herois[viaja->heroi]->velocidade);


    cria_chega(mundo, viaja->heroi, viaja->destino, viaja->tempo + duracao); 
    imprime_viaja(mundo, viaja, distancia, duracao);    
}

void evento_morre(mundo_t *mundo, struct morre *morre) {

    if (!mundo || !morre)
        return;

    if (!heroi_valido(mundo, morre->heroi) || !base_valida(mundo, morre->base))
        return;

    cjto_retira(mundo->bases[morre->base]->presentes, morre->heroi);    //retira heroi da base

    mundo->herois[morre->heroi]->vivo = 0;              //heroi = morto

    cria_avisa(mundo, morre->tempo, morre->base);
    imprime_morre(mundo,morre);

}

void evento_missao(mundo_t *mundo, struct missao *missao) {



}

void evento_fim(mundo_t *mundo, struct fim *fim) {
    


}