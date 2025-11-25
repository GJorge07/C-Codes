//Implementação dos diversos tipos de eventos que podem acontecer no mundo.

//4 no documento - usar fila de prioridade

//includes - falta mais
#include "entidades.h"
#include "eventos.h"
#include "outras_funcoes.h"

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

    if (!)     //se heroi tiver morto, return
        return;

    mundo->herois[chega->heroi]->base_atual = chega->base;


    if (base->lotacao > 0 && base->fila_t == 0)
        esp = 1;
    else
        esp = heroi->paciencia > (10 * base->lotacao (em b));

    if esp {
        fprio_insere(mundo->lef,x,ESPERA,y);
        return;
    }

    fprio_insere(mundo->lef,x,DESISTE,y);

}

//heroi entra na fila de espera e porteiro é avisado
void evento_espera(mundo_t *mundo, struct espera *espera) {

    if (!mundo || !espera)          //Pra não dar seg fault antes
        return;

    if (!heroi_valido(mundo, espera->heroi) || !base_valida(mundo, espera->base)  || !fila_valida(mundo, espera->base))
        return;

    fila_insere(mundo->bases[espera->base]->espera, espera->heroi);     //insere heroi na base B

    cria_avisa();

    imprime_espera();

}

void evento_desiste(mundo_t *mundo, struct desiste *desiste) {

    if(!mundo || !desiste)
        return;

    if (!heroi_valido(mundo, desiste->heroi) || !base_valida(mundo, desiste->base))
        return;

    int destino = aleat(0, mundo->nbases - 1);    // precisa do -1??

    cria_viaja();

    imprime_desiste();
}

void evento_avisa(mundo_t *mundo, struct avisa *avisa) {          //ver se ta certo o loop

    if (!mundo || !avisa)
        return;


    int b = mundo->bases[avisa->base]->lotacao;          //vagas em B
    int h = cjto_card(mundo->bases[avisa->base]->presentes);   //herois presentes na base

    imprime_avisa_porteiro();

    while (b > 0 && b > h ) {            //n tenho ctz q ta certo

        fila_retira(mundo->bases[avisa->base]->espera, &heroi_removido);         //retira primeiro heroi da fila
        cjto_insere(mundo->bases[avisa->base]->presentes, heroi_removido);       //insere heroi na fila


        imprime_avisa_e_admite();

        cria_entra();

        b = mundo->bases[avisa->base]->lotacao;
    }

}

void evento_entra(mundo_t *mundo, struct entra *entra) {

    if (!mundo || !entra)
        return;

    if (!heroi_valido(mundo,entra->heroi) || !base_valida(mundo,entra->base))
        return;

    int tpb = 15 + (mundo->herois[entra->heroi]->paciencia * aleat(1,20));
                    
    cria_sai();

    imprime_entra();

}

void evento_sai(mundo_t *mundo, struct sai *sai) {

    if (!mundo || !sai) 
        return;

     if (!heroi_valido(mundo, sai->heroi) || !base_valida(mundo, sai->base))
        return;

    cjto_retira(mundo->bases[sai->base]->presentes, sai->heroi);    //retira o heroi do conjunto de herois em B
    int destino = aleat(0, mundo->nbases-1);    //escolhe base aleatoria

    cria_viaja();
    cria_avisa();
    
    imprime_sai();
}

void evento_viaja(mundo_t *mundo, struct viaja *viaja) {

    if (!mundo || !viaja)
        return;

    if (!heroi_valido(mundo, viaja->heroi) || !base_valida(mundo, viaja->base))
        return;


    cria_chega();
    imprime_viaja();    
}

void evento_morre(mundo_t *mundo, struct morre *morre) {

    if (!mundo || !morre)
        return;

    if (!heroi_valido(mundo, morre->heroi) || !base_valida(mundo, morre->base))
        return;

    cjto_retira(mundo->bases[morre->base]->presentes, morre->heroi);    //retira heroi da base

    mundo->herois[morre->heroi]->vivo = 0;              //heroi = morto

    cria_avisa();
    imprime_morre();

}

void evento_missao(mundo_t *mundo, struct missao *missao) {



}

void evento_fim(mundo_t *mundo, struct fim *fim) {
    


}