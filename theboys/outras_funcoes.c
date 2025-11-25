//Implementação de outras funções utilizadas para a simulação do mundo.

//includes
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

    if (heroi < 0 || heroi <= mundo->nherois)       //0 até N-1
        return 0;

    if (!mundo->herois[heroi])           //Se heroi existe mas ponteiro é NULL
        return 0;
    
    return 1;
}

int valida_fila(mundo_t *mundo, int base) {

    if (!mundo)
        return 0;

    if (!base_valida(mundo,base)) //verifica se a base existe
        return 0;

    if (!mundo->bases[base]->espera)    //verifica se fila de espera existe
        return 0;

    return 1;
}
/*---------------------------------------CRIAÇÃO DE EVENTOS-------------------------------------------------*/

void cria_chega();

void cria_espera();

void cria_desiste();

void cria_avisa();

void cria_viaja();

void cria_sai();

void cria_entra();

void cria_morre();

/*---------------------------------------PRINTF DAS FUNÇÕES------------------------------------------------*/

void imprime_chega_e_espera(mundo_t *mundo, struct chega *chega) {

    printf("%6d: CHEGA HEROI %2d base %d (%2d/%2d) ESPERA", chega->tempo, chega->heroi, chega->base,cjto_card(mundo->bases[chega->base]->presentes),(mundo->bases[chega->base]->lotacao)); 
    //A fila de espera da base que esse herói está indo e capacidade máxima da base - os 2 ultimos
}

void imprime_chega_e_desiste(mundo_t *mundo, struct chega *chega) {

    printf("%6d: CHEGA HEROI %2d base %d (%2d/%2d) DESISTE", chega->tempo, chega->heroi, chega->base,cjto_card(mundo->bases[chega->base]->presentes),(mundo->bases[chega->base]->lotacao)); 

}

void imprime_espera(mundo_t *mundo, struct espera *espera) {

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", espera->tempo, espera->heroi, espera->base, fila_tamanho(mundo->bases[espera->base]->espera));

}

void imprime_desiste(mundo_t *mundo, struct desiste *desiste) {

    printf("%6d: DESISTE HEROI %2d BASE %d", desiste->tempo, desiste->heroi, desiste->base);

}

void imprime_avisa_porteiro(mundo_t *mundo, struct avisa *avisa) {

    printf("%6d: AVISA  PORTEIRO BASE %d (%2d/%2d) ", avisa->tempo, avisa->base, cjto_card(mundo->bases[avisa->base]->presentes), mundo->bases[avisa->base]->lotacao);
        printf("FILA [ ");
        fila_imprime(mundo->bases[avisa->base]->espera);
        printf(" ]\n");

}

void imprime_avisa_e_admite(struct avisa *avisa, int heroi_removido) {    //como faz o heroi removido ?

    printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d", avisa->tempo, avisa->base, heroi_removido);

}

void imprime_entrada(mundo_t *mundo, struct entra *entra, struct sai *sai) {

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d", entra->tempo, entra->heroi, entra->base, cjto_card(mundo->bases[entra->base]->presentes), mundo->bases[entra->base]->lotacao, sai->tempo);

}

void imprime_saida(mundo_t *mundo, struct sai *sai) {

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)", sai->tempo, sai->heroi, sai->base, cjto_card(mundo->bases[sai->base]->presentes),mundo->bases[sai->base]->lotacao);
    
}

void imprime_viagem(mundo_t *mundo, struct viaja *viaja, int distancia, int duracao) {
    
    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d", viaja->tempo, viaja->heroi, viaja->base, viaja->destino, distancia, mundo->herois[viaja->heroi]->velocidade, viaja->tempo+duracao);

}

void imprime_morte(mundo_t *mundo, struct morre *morre) {

    printf("%6d: MORRE HEROI %2d MISSAO %d", morre->tempo, morre->heroi, morre->missao);   //ver se esse missao ta certo, add no eventos.h agr

}