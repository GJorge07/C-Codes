/*Implementação dos diversos tipos de eventos que podem acontecer no mundo.*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>       /*pra usar o int max no evento fim*/
#include <math.h>

#include "entidades.h"
#include "eventos.h"
#include "outras_funcoes.h"
#include "chama_eventos.h"
#include "fprio.h"
#include "fila.h"
#include "lista.h"
#include "conjunto.h"

#define T_FIM_DO_MUNDO 525600

void eventos_iniciais(mundo_t *mundo) {

    int base, tempo_h, tempo_m;

    /*Evento de CHEGADA*/
    for (int i = 0; i < mundo->nherois; i++) {

        base = aleat(0, mundo->nbases - 1);
        tempo_h = aleat(0, 4321);

        cria_chega(mundo, i, base, tempo_h);

    }

    /* Eventos de MISSÃO */
    for (int j = 0; j < mundo->nmissoes; j++) {

        tempo_m = aleat(0, T_FIM_DO_MUNDO);

        cria_missao_evento(mundo, j, tempo_m);

    }
    /* Evento de FIM DO MUNDO */
    struct fim *fim = malloc(sizeof(struct fim));
    if (!fim) return;

    fim->tempo = T_FIM_DO_MUNDO;

    fprio_insere(mundo->lef, fim, FIM, T_FIM_DO_MUNDO);
}


void evento_chega(mundo_t *mundo, struct chega *chega) {

    if (!mundo || !chega)
        return;

    if (!valida_heroi(mundo, chega->heroi))
        return;

    mundo->neventos++;             /*incrementa o número de eventos*/

    int espera;

    int lot = mundo->bases[chega->base]->lotacao;          /*vagas em B*/
    int h = cjto_card(mundo->bases[chega->base]->presentes);   /*herois presentes na base*/
    int tam_fila = fila_tamanho(mundo->bases[chega->base]->espera);


    mundo->herois[chega->heroi]->base_atual = chega->base;

    if (tam_fila == 0 && h < lot )       
        espera = 1;
    else 
        espera = mundo->herois[chega->heroi]->paciencia > (10 * tam_fila);

    if (espera) {

        imprime_chega_e_espera(mundo, chega);
        cria_espera(mundo, chega->tempo, chega->heroi, chega->base);
        
    }

    else {

        imprime_chega_e_desiste(mundo, chega);
        cria_desiste(mundo, chega->tempo, chega->heroi, chega->base);

    }
}


void evento_espera(mundo_t *mundo, struct espera *espera) {

    if (!mundo || !espera)         
        return;

    if (!valida_heroi(mundo, espera->heroi))
        return;

    mundo->neventos++;
    
    imprime_espera(mundo, espera);

    fila_insere(mundo->bases[espera->base]->espera, espera->heroi);     /*insere heroi na base B*/

    /* atualizar fila_max após inserção */
    int tamanho_atual = fila_tamanho(mundo->bases[espera->base]->espera);
    if (tamanho_atual > mundo->bases[espera->base]->fila_max) 
        mundo->bases[espera->base]->fila_max = tamanho_atual;
    
    cria_avisa(mundo, espera->tempo, espera->base);

}

void evento_desiste(mundo_t *mundo, struct desiste *desiste) {

    if(!mundo || !desiste)
        return;

    if (!valida_heroi(mundo, desiste->heroi))
        return;

    mundo->neventos++;

    int destino = aleat(0, mundo->nbases - 1);  

    cria_viaja(mundo, desiste->tempo, desiste->heroi, desiste->base, destino);

    imprime_desiste(desiste);

}

void evento_avisa(mundo_t *mundo, struct avisa *avisa) {          //ver se ta certo o loop

    if (!mundo || !avisa)
        return;

    mundo->neventos++;

    int b = mundo->bases[avisa->base]->lotacao;         
    int h = cjto_card(mundo->bases[avisa->base]->presentes);  
    int tam_fila = fila_tamanho(mundo->bases[avisa->base]->espera);

    imprime_avisa_porteiro(mundo, avisa);

    while (tam_fila > 0 && b > h ) {            

        int heroi_removido;

        fila_retira(mundo->bases[avisa->base]->espera, &heroi_removido);         /*retira primeiro heroi da fila*/
        cjto_insere(mundo->bases[avisa->base]->presentes, heroi_removido);       /*insere heroi na fila*/


        imprime_avisa_e_admite(avisa,heroi_removido);

        cria_entra(mundo, avisa->tempo, heroi_removido, avisa->base);

        h = cjto_card(mundo->bases[avisa->base]->presentes);   /*atualiza numero de herois na base*/
        tam_fila = fila_tamanho(mundo->bases[avisa->base]->espera);

    }
}

void evento_entra(mundo_t *mundo, struct entra *entra) {

    if (!mundo || !entra)
        return;

    if (!valida_heroi(mundo,entra->heroi))
        return;

    mundo->neventos++;


    int tpb = 15 + (mundo->herois[entra->heroi]->paciencia * aleat(1,20));
                    
    cria_sai (mundo, entra->tempo + tpb, entra->heroi, entra->base);

    int tempo_sai = entra->tempo + tpb;

    imprime_entra(mundo, entra, tempo_sai);             

}

void evento_sai(mundo_t *mundo, struct sai *sai) {

    if (!mundo || !sai) 
        return;

     if (!valida_heroi(mundo, sai->heroi))
        return;

    mundo->neventos++;

    cjto_retira(mundo->bases[sai->base]->presentes, sai->heroi);    /*retira o heroi do conjunto de herois em B*/
    int destino = aleat(0, mundo->nbases-1);    /*escolhe base aleatoria*/

    cria_viaja(mundo, sai->tempo, sai->heroi, sai->base, destino);
    cria_avisa(mundo, sai->tempo, sai->base);
    
    imprime_sai(mundo, sai);

}

void evento_viaja(mundo_t *mundo, struct viaja *viaja) {

    if (!mundo || !viaja)
        return;

    if (!valida_heroi(mundo, viaja->heroi))
        return;

    mundo->neventos++;

    int x1 = mundo->bases[viaja->base]->local_base.x;  
    int y1 = mundo->bases[viaja->base]->local_base.y;  

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

    if (!valida_heroi(mundo, morre->heroi))
        return;

    mundo->neventos++;

    cjto_retira(mundo->bases[morre->base]->presentes, morre->heroi);    /*retira heroi da base*/

    mundo->herois[morre->heroi]->vivo = 0;              /*heroi = morto*/

    cria_avisa(mundo, morre->tempo, morre->base);
    imprime_morre(morre);

}

void evento_missao(mundo_t *mundo, struct missao *missao) {

    if (!mundo || !missao)
        return;
    
    mundo->neventos++;
    missao->tentativas++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", mundo->relogio, missao->id, missao->tentativas);
    cjto_imprime(missao->habilidades_missao);
    printf(" ]\n");

    /* vetor com ids das bases */
    int dist_missao[mundo->nbases];
    for (int i = 0; i < mundo->nbases; i++)
        dist_missao[i] = i;

    /* ordena vetor por distância da missão */
    quicksort(mundo, missao, dist_missao, 0, mundo->nbases - 1);

    int bmp = -1;
    struct cjto_t *hab_base = NULL;

    /* percorre bases para ver se alguma cumpre a missão */
    for (int i = 0; i < mundo->nbases; i++) {
        int base_id = dist_missao[i];
        base_t *b = mundo->bases[base_id];

        if (cjto_card(b->presentes) == 0)
            continue;

        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", mundo->relogio, missao->id, b->id,
               calcula_dist(b->local_base, missao->local_missao));
        cjto_imprime(b->presentes);
        printf(" ]\n");

        hab_base = cjto_cria(mundo->nhabilidades);
        for (int h = 0; h < mundo->nherois; h++) {
            if (cjto_pertence(b->presentes, h)) {
                printf("%6d: MISSAO %d HAB HEROI %2d: [ ", mundo->relogio, missao->id, h);
                cjto_imprime(mundo->herois[h]->habilidades);
                printf(" ]\n");

                struct cjto_t *temp = cjto_uniao(hab_base, mundo->herois[h]->habilidades);
                cjto_destroi(hab_base);
                hab_base = temp;
            }
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", mundo->relogio, missao->id, b->id);
        cjto_imprime(hab_base);
        printf(" ]\n");

        if (cjto_contem(hab_base, missao->habilidades_missao)) {
            bmp = base_id;
            break;
        }

        cjto_destroi(hab_base);
        hab_base = NULL;
    }

    /* missão cumprida normalmente */
    if (bmp >= 0) {
        missao->cumprida = 1;
        mundo->bases[bmp]->missoes_cumpridas++;

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", mundo->relogio, missao->id, bmp);
        cjto_imprime(hab_base);
        printf(" ]\n");

        for (int h = 0; h < mundo->nherois; h++)
            if (cjto_pertence(mundo->bases[bmp]->presentes, h))
                mundo->herois[h]->experiencia++;

        cjto_destroi(hab_base);
        return;
    }

    /* quando não achou BMP, verifica possibilidade de usar Composto V */
    if (mundo->ncompostosv > 0 && mundo->relogio % 2500 == 0) {
        int base_mais_proxima = -1;
        for (int i = 0; i < mundo->nbases; i++) {
            if (cjto_card(mundo->bases[dist_missao[i]]->presentes) > 0) {
                base_mais_proxima = dist_missao[i];
                break;
            }
        }

        if (base_mais_proxima != -1) {
            int heroi_veterano = -1, maior_xp = -1;
            for (int h = 0; h < mundo->nherois; h++) {
                if (cjto_pertence(mundo->bases[base_mais_proxima]->presentes, h) &&
                    mundo->herois[h]->experiencia > maior_xp) {
                    maior_xp = mundo->herois[h]->experiencia;
                    heroi_veterano = h;
                }
            }

            if (heroi_veterano >= 0) {
                mundo->ncompostosv--;
                missao->cumprida = 1;
                mundo->bases[base_mais_proxima]->missoes_cumpridas++;

                hab_base = cjto_cria(mundo->nhabilidades);
                for (int h = 0; h < mundo->nherois; h++) {
                    if (cjto_pertence(mundo->bases[base_mais_proxima]->presentes, h)) {
                        struct cjto_t *temp = cjto_uniao(hab_base, mundo->herois[h]->habilidades);
                        cjto_destroi(hab_base);
                        hab_base = temp;
                    }
                }
                struct cjto_t *hab_final_v = cjto_uniao(hab_base, missao->habilidades_missao);

                printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", mundo->relogio, missao->id, base_mais_proxima);
                cjto_imprime(hab_final_v);
                printf(" ]\n");

                cjto_destroi(hab_base);
                cjto_destroi(hab_final_v);

                /* cria evento MORRE */
                struct morre *evento = malloc(sizeof(struct morre));
                evento->tempo = mundo->relogio;
                evento->heroi = heroi_veterano;
                evento->base = base_mais_proxima;
                evento->missao = missao->id;
                fprio_insere(mundo->lef, evento, MORRE, evento->tempo);

                for (int h = 0; h < mundo->nherois; h++) {
                    if (h != heroi_veterano &&
                        cjto_pertence(mundo->bases[base_mais_proxima]->presentes, h))
                        mundo->herois[h]->experiencia++;
                }

                return;
            }
        }
    }

    /* missão impossível, reagendar para o dia seguinte */
    printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->relogio, missao->id);
    struct evento_missao *novo_ev = malloc(sizeof(struct evento_missao));
    novo_ev->id = missao->id;
    fprio_insere(mundo->lef, novo_ev, MISSAO, mundo->relogio + 1440);

}


void evento_fim(mundo_t *mundo, struct fim *fim) {
    
    if (!mundo || !fim)
        return;

    printf("%6d: FIM\n", mundo->relogio);

    /* Imprime informações de todos os heróis */
    for (int i = 0; i < mundo->nherois; i++) {
        if (mundo->herois[i]->vivo) {
            printf("HEROI %2d VIVO PAC %3d VEL %4d EXP %4d HABS [ ",
                   mundo->herois[i]->id,
                   mundo->herois[i]->paciencia,
                   mundo->herois[i]->velocidade,
                   mundo->herois[i]->experiencia);
        } else {
            printf("HEROI %2d MORTO PAC %3d VEL %4d EXP %4d HABS [ ",
                   mundo->herois[i]->id,
                   mundo->herois[i]->paciencia,
                   mundo->herois[i]->velocidade,
                   mundo->herois[i]->experiencia);
        }
        cjto_imprime(mundo->herois[i]->habilidades);
        printf(" ]\n");
    }

    /* Imprime informações de todas as bases */
    for (int i = 0; i < mundo->nbases; i++) {
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n",
               mundo->bases[i]->id,
               mundo->bases[i]->lotacao,
               mundo->bases[i]->fila_max,
               mundo->bases[i]->missoes_cumpridas);

    }

    /* Calcula estatísticas das missões */
    int missoes_cumpridas = 0;
    int tentativas_min = INT_MAX;            /* int max é o maior valor possivel de int -> numero muito grande */
    int tentativas_max = 0;
    int soma_tentativas = 0;

    for (int i = 0; i < mundo->nmissoes; i++) {

        if (mundo->missoes[i]->cumprida == 1) {
            missoes_cumpridas++;
        }
        
        if (mundo->missoes[i]->tentativas < tentativas_min) {
            tentativas_min = mundo->missoes[i]->tentativas;
        }
        
        if (mundo->missoes[i]->tentativas > tentativas_max) {
            tentativas_max = mundo->missoes[i]->tentativas;
        }
        
        soma_tentativas += mundo->missoes[i]->tentativas;
    }

    /* se não houve tentativas, ajustar valores */
    if (tentativas_min == INT_MAX)
        tentativas_min = 0;

    /* Calcula taxa de mortalidade */
    int herois_mortos = 0;
    for (int i = 0; i < mundo->nherois; i++) {

        if (!mundo->herois[i]->vivo) 
            herois_mortos++;
            
    }

    /* Imprime estatísticas finais */
    printf("EVENTOS TRATADOS: %d\n", mundo->neventos);
    
    float percentual_cumpridas = (float)missoes_cumpridas / mundo->nmissoes * 100.0;
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", 
           missoes_cumpridas, mundo->nmissoes, percentual_cumpridas);
    
    float media_tentativas = (float)soma_tentativas / mundo->nmissoes;
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n",
           tentativas_min, tentativas_max, media_tentativas);
    
    float taxa_mortalidade = (float)herois_mortos / mundo->nherois * 100.0;
    printf("TAXA MORTALIDADE: %.1f%%\n", taxa_mortalidade);

}
