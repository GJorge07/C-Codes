//Implementação de outras funções utilizadas para a simulação do mundo.

//includes
#include <stdio.h>
#include "entidades.h"
#include "eventos.h"

//outras funções usadas no simulador
int aleat(int min, int max) {
    return min + rand() % (max - min + 1);
}

int valida_base(mundo_t *mundo, int base) {

    if (!mundo)
        return 0;

    if (base < 0 || base >= mundo->nbases)         // 0 até N-1
        return 0;
    
    if (!mundo->bases[base])                 //Se base existe mas ponteiro é NULL
        return 0;

    return 1;
}

int valida_heroi(mundo_t *mundo, int heroi) {


    if (!mundo)
        return 0;

    if (heroi < 0 || heroi >= mundo->nherois)       //0 até N-1
        return 0;

    if (!mundo->herois[heroi])           //Se heroi existe mas ponteiro é NULL
        return 0;

    if (!mundo->herois[heroi]->vivo)  // herói morto
        return 0;
    
    return 1;
}

int valida_fila(mundo_t *mundo, int base) {

    if (!mundo)
        return 0;

    if (!valida_base(mundo,base)) //verifica se a base existe
        return 0;

    if (!mundo->bases[base]->espera)    //verifica se fila de espera existe
        return 0;

    return 1;
}
/*---------------------------------------CRIAÇÃO DE EVENTOS-------------------------------------------------*/

void cria_chega(mundo_t *mundo, int heroi, int base, int tempo) {

    struct chega *chega;
    if (!(chega = malloc(sizeof(struct chega))))
        return;

    chega->heroi = heroi;
    chega->base = base;
    chega->tempo = tempo;

    fprio_insere(mundo->lef, chega, CHEGA, chega->tempo);
}

void cria_espera(mundo_t *mundo, int tempo, int heroi, int base) {

    struct espera *espera;
    if (!(espera = malloc(sizeof(struct espera))))
        return;

    espera->tempo = tempo;
    espera->heroi = heroi;
    espera->base = base;

    fprio_insere(mundo->lef, espera, ESPERA, espera->tempo);
}

void cria_desiste(mundo_t *mundo, int tempo, int heroi, int base) {

    struct desiste *desiste;
    if (!(desiste = malloc(sizeof(struct desiste))))
        return;

    desiste->tempo = tempo;
    desiste->heroi = heroi;
    desiste->base = base;

    fprio_insere(mundo->lef, desiste, DESISTE, desiste->tempo);
}

void cria_avisa(mundo_t *mundo, int tempo, int base) {

    struct avisa *avisa;
    if (!(avisa = malloc(sizeof(struct avisa))))
        return;

    avisa->tempo = tempo;
    avisa->base = base;
    
    fprio_insere(mundo->lef, avisa, AVISA, avisa->tempo);
}

void cria_viaja(mundo_t *mundo, int tempo, int heroi, int destino) {

    struct viaja *viaja;
    if (!(viaja = malloc(sizeof(struct viaja))))
        return;

    viaja->tempo = tempo;
    viaja->heroi = heroi;
    viaja->destino = destino;

    fprio_insere(mundo->lef, viaja, VIAJA, viaja->tempo);

}

void cria_sai(mundo_t *mundo, int tempo, int heroi, int base) {

    struct sai *sai;
    if (!(sai = malloc(sizeof(struct sai))))
        return;

    sai->tempo = tempo;
    sai->heroi = heroi;
    sai->base = base;

    fprio_insere(mundo->lef, sai, SAI, sai->tempo);
}

void cria_entra(mundo_t *mundo, int tempo, int heroi, int base) {

    struct entra *entra;
    if (!(entra = malloc(sizeof(struct entra))))
        return;

    entra->tempo = tempo;
    entra->heroi = heroi;
    entra->base = base;

    fprio_insere(mundo->lef, entra, ENTRA, entra->tempo);
}

void cria_morre(mundo_t *mundo, int tempo, int heroi, int base, int missao) {

    struct morre *morre;
    if (!(morre = malloc(sizeof(struct morre))))
        return;

    morre->tempo = tempo;
    morre->heroi = heroi;
    morre->base = base;
    morre->missao = missao;

    fprio_insere(mundo->lef, morre, MORRE, morre->tempo);
}

void cria_missao(mundo_t *mundo, int id, struct cjto_t *hab, struct localizacao local, int tempo) {

        struct missao *missao;
        if (!(missao = malloc(sizeof(struct missao))))
            return;

        missao->id = id;
        missao->habilidades_missao = hab;
        missao->local_missao = local;

        fprio_insere(mundo->lef, missao, MISSAO, tempo);
}

/*---------------------------------------PRINTF DAS FUNÇÕES------------------------------------------------*/

void imprime_chega_e_espera(mundo_t *mundo, struct chega *chega) {

    printf("%6d: CHEGA HEROI %2d base %d (%2d/%2d) ESPERA\n", chega->tempo, chega->heroi, chega->base,cjto_card(mundo->bases[chega->base]->presentes),(mundo->bases[chega->base]->lotacao)); 
    //A fila de espera da base que esse herói está indo e capacidade máxima da base - os 2 ultimos
}

void imprime_chega_e_desiste(mundo_t *mundo, struct chega *chega) {

    printf("%6d: CHEGA HEROI %2d base %d (%2d/%2d) DESISTE\n", chega->tempo, chega->heroi, chega->base,cjto_card(mundo->bases[chega->base]->presentes),(mundo->bases[chega->base]->lotacao)); 

}

void imprime_espera(mundo_t *mundo, struct espera *espera) {

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", espera->tempo, espera->heroi, espera->base, fila_tamanho(mundo->bases[espera->base]->espera));

}

void imprime_desiste(struct desiste *desiste) {

    printf("%6d: DESISTE HEROI %2d BASE %d\n", desiste->tempo, desiste->heroi, desiste->base);

}

void imprime_avisa_porteiro(mundo_t *mundo, struct avisa *avisa) {

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d)\n", avisa->tempo, avisa->base, cjto_card(mundo->bases[avisa->base]->presentes), mundo->bases[avisa->base]->lotacao);
        printf("FILA [ ");
        fila_imprime(mundo->bases[avisa->base]->espera);
        printf(" ]\n");

}

void imprime_avisa_e_admite(struct avisa *avisa, int heroi_removido) {    //como faz o heroi removido ?

    printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", avisa->tempo, avisa->base, heroi_removido);

}

void imprime_entra(mundo_t *mundo, struct entra *entra, int sai_tempo) {

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", entra->tempo, entra->heroi, entra->base, cjto_card(mundo->bases[entra->base]->presentes), mundo->bases[entra->base]->lotacao, sai_tempo);

}

void imprime_sai(mundo_t *mundo, struct sai *sai) {

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", sai->tempo, sai->heroi, sai->base, cjto_card(mundo->bases[sai->base]->presentes),mundo->bases[sai->base]->lotacao);
    
}

void imprime_viaja(mundo_t *mundo, struct viaja *viaja, int distancia, int duracao) {
    
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", viaja->tempo, viaja->heroi, viaja->base, viaja->destino, distancia, mundo->herois[viaja->heroi]->velocidade, viaja->tempo+duracao);

}

void imprime_morre(struct morre *morre) {

    printf("%6d: MORRE HEROI %2d MISSAO %d\n", morre->tempo, morre->heroi, morre->missao);   //ver se esse missao ta certo, add no eventos.h agr

}