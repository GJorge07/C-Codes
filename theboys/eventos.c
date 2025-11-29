//Implementação dos diversos tipos de eventos que podem acontecer no mundo.

//4 no documento - usar fila de prioridade

//includes - falta mais
#include "entidades.h"
#include "eventos.h"
#include "outras_funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>       //pra usar o int max no evento fim
#include <math.h>
#include "chama_eventos.h"

//defines
#define T_FIM_DO_MUNDO 50000

void eventos_iniciais(mundo_t *mundo) {

    int base, tempo1, tempo2;

    
    for (int i = 0; i < mundo->nherois; i++) {

        base = aleat(0, mundo->nbases - 1);
        tempo1 = aleat(0, 4321);
        cria_chega(mundo, i, base, tempo1);         //i sao os herois
    }
    
    for (int j = 0; j < mundo->nmissoes; j++) {
        
        tempo2 = aleat(0, T_FIM_DO_MUNDO);
        cria_missao(mundo,j,mundo->missoes[j]->habilidades_missao,mundo->missoes[j]->local_missao,tempo2);
    }
    
    //para o fim, não fiz cria_fim!!!!!!!
    struct fim *fim;
	if (!(fim = malloc(sizeof(struct fim))))
		return; 
	fim->tempo = T_FIM_DO_MUNDO;

	fprio_insere(mundo->lef, fim, FIM, T_FIM_DO_MUNDO);
}

void evento_chega(mundo_t *mundo, struct chega *chega) {

    if (!mundo || !chega)
        return;

    if (!valida_heroi(mundo, chega->heroi) || !valida_base(mundo, chega->base))
        return;

    mundo->neventos++;

    int espera;

    int lot = mundo->bases[chega->base]->lotacao;          //vagas em B
    int h = cjto_card(mundo->bases[chega->base]->presentes);   //herois presentes na base
    int tam_fila = fila_tamanho(mundo->bases[chega->base]->espera);


    mundo->herois[chega->heroi]->base_atual = chega->base;

    if (tam_fila == 0 && h < lot )       //se há vagas em B e a fila de espera em B está vazia
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

//heroi entra na fila de espera e porteiro é avisado
void evento_espera(mundo_t *mundo, struct espera *espera) {

    if (!mundo || !espera)          //Pra não dar seg fault antes
        return;

    if (!valida_heroi(mundo, espera->heroi) || !valida_base(mundo, espera->base))
        return;

    mundo->neventos++;
    
    imprime_espera(mundo, espera);

    fila_insere(mundo->bases[espera->base]->espera, espera->heroi);     //insere heroi na base B

    // ATUALIZAR fila_max após inserção
    int tamanho_atual = fila_tamanho(mundo->bases[espera->base]->espera);
    if (tamanho_atual > mundo->bases[espera->base]->fila_max) {
        mundo->bases[espera->base]->fila_max = tamanho_atual;
    }
    
    cria_avisa(mundo, espera->tempo, espera->base);


}

void evento_desiste(mundo_t *mundo, struct desiste *desiste) {

    if(!mundo || !desiste)
        return;

    if (!valida_heroi(mundo, desiste->heroi) || !valida_base(mundo, desiste->base))
        return;

    mundo->neventos++;

    int destino = aleat(0, mundo->nbases - 1);    // precisa do -1??

    cria_viaja(mundo, desiste->tempo, desiste->heroi, desiste->base, destino);

    imprime_desiste(desiste);
}

void evento_avisa(mundo_t *mundo, struct avisa *avisa) {          //ver se ta certo o loop

    if (!mundo || !avisa)
        return;

     if (!valida_base(mundo, avisa->base))
        return;

    mundo->neventos++;

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

    if (!valida_heroi(mundo,entra->heroi) || !valida_base(mundo,entra->base))
        return;

    mundo->neventos++;

    int tpb = 15 + (mundo->herois[entra->heroi]->paciencia * aleat(1,20));
                    
    cria_sai (mundo, entra->tempo + tpb, entra->heroi, entra->base);

    int tempo_sai = entra->tempo + tpb;

    imprime_entra(mundo, entra, tempo_sai);             //ver se é entra + tpb mesmo

}

void evento_sai(mundo_t *mundo, struct sai *sai) {

    if (!mundo || !sai) 
        return;

     if (!valida_heroi(mundo, sai->heroi) || !valida_base(mundo, sai->base))
        return;

    mundo->neventos++;

    cjto_retira(mundo->bases[sai->base]->presentes, sai->heroi);    //retira o heroi do conjunto de herois em B
    int destino = aleat(0, mundo->nbases-1);    //escolhe base aleatoria

    cria_viaja(mundo, sai->tempo, sai->heroi, sai->base, destino);
    cria_avisa(mundo, sai->tempo, sai->base);
    
    imprime_sai(mundo, sai);
}

void evento_viaja(mundo_t *mundo, struct viaja *viaja) {

    if (!mundo || !viaja)
        return;

    if (!valida_heroi(mundo, viaja->heroi) || !valida_base(mundo, viaja->destino))
        return;

    mundo->neventos++;

    int x1 = mundo->bases[viaja->base]->local_base.x;  // CORRIGIDO
    int y1 = mundo->bases[viaja->base]->local_base.y;  // CORRIGIDO

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

    if (!valida_heroi(mundo, morre->heroi) || !valida_base(mundo, morre->base))
        return;

    mundo->neventos++;

    cjto_retira(mundo->bases[morre->base]->presentes, morre->heroi);    //retira heroi da base

    mundo->herois[morre->heroi]->vivo = 0;              //heroi = morto

    cria_avisa(mundo, morre->tempo, morre->base);
    imprime_morre(morre);

}

void evento_missao(mundo_t *mundo, struct missao *missao) {
    
    int dist_missao[mundo->nbases];         //id das bases
    
    mundo->neventos++;

    missao->tentativas++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ",mundo->relogio,missao->id,missao->tentativas);
    cjto_imprime(missao->habilidades_missao);
    printf(" ]\n");

    //inicia o vetor
    for (int i = 0; i < mundo->nbases; i++ ) 
            dist_missao[i] = i;
    
    //ordena o vetor com ordem crescente de distância
    quicksort(mundo,missao,dist_missao,0,mundo->nbases - 1);

    //bmp (percorre o vetor e ve se a base pode cumprir a missão)

    int bmp = -1;

    for (int i = 0; i < mundo->nbases; i++) {

        int base_id = dist_missao[i];

        if (cjto_card(mundo->bases[base_id]->presentes) == 0)      //se quantidade de herois na base for 0, pula
            continue;

        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ",mundo->relogio,missao->id,mundo->bases[base_id]->id,calcula_dist(missao->local_missao,mundo->bases[base_id]->local_base));
        cjto_imprime(mundo->bases[base_id]->presentes);
        printf(" ]\n");

        struct cjto_t *hab_uniao = cjto_cria(mundo->nhabilidades);
        if (hab_uniao == NULL)
            continue;

        for (int j = 0; j < mundo->nherois; j++) {

            if (cjto_pertence(mundo->bases[base_id]->presentes, j)) {

                printf("%6d: MISSAO %d HAB HEROI %2d: [ ",mundo->relogio,missao->id,mundo->herois[j]->id);
                cjto_imprime(mundo->herois[j]->habilidades);
                printf(" ]\n");

                struct cjto_t *hab_nova = cjto_uniao(hab_uniao, mundo->herois[j]->habilidades);
                cjto_destroi(hab_uniao);
                hab_uniao = hab_nova;
            }
    }


        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ",mundo->relogio,missao->id,mundo->bases[base_id]->id);
        cjto_imprime(hab_uniao);
        printf(" ]\n");

    int base_cumpre = cjto_contem(hab_uniao, missao->habilidades_missao);   //base pode cumprir missao

    if (base_cumpre) {
        bmp = base_id;
        cjto_destroi(hab_uniao);
        break;
    }

    cjto_destroi(hab_uniao);
    hab_uniao = NULL;
}


//Achou bmp, incrementa xp dos herois presentes na base
    if (bmp >=0) {
        
        missao->ncumpridas++;   // missão cumprida
        mundo->bases[bmp]->missoes_cumpridas++;    //base cumpriu mais uma missão

        /* recria união das habilidades para impressão */
        struct cjto_t *hab_final = cjto_cria(mundo->nhabilidades);
        for (int h = 0; h < mundo->nherois; h++) {
            if (cjto_pertence(mundo->bases[bmp]->presentes, h)) {
                struct cjto_t *temp = cjto_uniao(hab_final, mundo->herois[h]->habilidades);
                cjto_destroi(hab_final);
                hab_final = temp;
            }
        }

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",mundo->relogio,missao->id,bmp);
        cjto_imprime(hab_final);
        printf(" ]\n");

        cjto_destroi(hab_final);

    // incrementa exp
        for (int h = 0; h < mundo->nherois; h++) {
            if (cjto_pertence(mundo->bases[bmp]->presentes, h))
                mundo->herois[h]->experiencia++;
        }
        return;
    }

    /* quando não achou BMP, verifica possibilidade de usar compostoV */
    if (mundo->ncompostosv > 0 && mundo->relogio % 2500 == 0) {
        
        /* encontra primeira base não vazia no vetor ordenado por distância */
        int base_mais_proxima = -1;
        for (int k = 0; k < mundo->nbases; k++) {
            if (cjto_card(mundo->bases[dist_missao[k]]->presentes) > 0) {
                base_mais_proxima = dist_missao[k];
                break;
            }
        }
        
        /* se não encontrou nenhuma base com heróis, missão impossível */
        if (base_mais_proxima == -1) {
            printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->relogio, missao->id);
            cria_missao(mundo, missao->id, missao->habilidades_missao, missao->local_missao, mundo->relogio + 24*60);
            return;
        }
        
        /* procura herói com maior experiência na base mais próxima */
        int heroi_veterano = -1;
        int experiencia_maxima = -1;
        int encontrou_veterano = 0;
        
        for (int h = 0; h < mundo->nherois; h++) {
            if (cjto_pertence(mundo->bases[base_mais_proxima]->presentes, h)) {
                if (mundo->herois[h]->experiencia > experiencia_maxima) {
                    experiencia_maxima = mundo->herois[h]->experiencia;
                    heroi_veterano = h;
                    encontrou_veterano = 1;
                }
            }
        }
        
        /* se encontrou um herói veterano, usa composto V */
        if (encontrou_veterano) {
            mundo->ncompostosv--;                    // usa um composto V
            missao->ncumpridas++;                    // marca missão como cumprida
            mundo->bases[base_mais_proxima]->missoes_cumpridas++;  // base cumpriu missão
            
            //print - missao cumprida compostoV
            
            printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ",mundo->relogio,missao->id,base_mais_proxima);
            
            /* recria união para impressão */
            struct cjto_t *hab_compostoV = cjto_cria(mundo->nhabilidades);
            for (int h = 0; h < mundo->nherois; h++) {
                if (cjto_pertence(mundo->bases[base_mais_proxima]->presentes, h)) {
                    struct cjto_t *temp = cjto_uniao(hab_compostoV, mundo->herois[h]->habilidades);
                    cjto_destroi(hab_compostoV);
                    hab_compostoV = temp;
                }
            }
            /* adiciona habilidades da missão (efeito do compostoV) */
            struct cjto_t *hab_final_v = cjto_uniao(hab_compostoV, missao->habilidades_missao);
            cjto_imprime(hab_final_v);
            printf(" ]\n");
            
            cjto_destroi(hab_compostoV);
            cjto_destroi(hab_final_v);

            /* para o herói mais experiente (H): cria e insere na LEF o evento MORRE (agora, H) */
            cria_morre(mundo, mundo->relogio, heroi_veterano, base_mais_proxima, missao->id);

            /* incrementa a experiência dos demais heróis presentes na BMP */
            for (int h = 0; h < mundo->nherois; h++) {
                if (cjto_pertence(mundo->bases[base_mais_proxima]->presentes, h) && h != heroi_veterano) {
                    mundo->herois[h]->experiencia++;
                }
            }

            //imprime_missao_cumprida_compostoV(mundo, missao, base_mais_proxima, heroi_veterano);
        } else {
            printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->relogio, missao->id);
            cria_missao(mundo, missao->id, missao->habilidades_missao, missao->local_missao, mundo->relogio + 1440);
        }
    } else {
        /* PRINT OBRIGATÓRIO - missão impossível */
        printf("%6d: MISSAO %d IMPOSSIVEL\n", mundo->relogio, missao->id);
        cria_missao(mundo, missao->id, missao->habilidades_missao, missao->local_missao, mundo->relogio + 1440);
    }
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
    int tentativas_min = INT_MAX;            //int max é o maior valor possivel de int -> numero muito grande
    int tentativas_max = 0;
    int soma_tentativas = 0;

    for (int i = 0; i < mundo->nmissoes; i++) {
        if (mundo->missoes[i]->ncumpridas > 0) {
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

    //se não houve tentativas, ajustar valores
    if (tentativas_min == INT_MAX) {
        tentativas_min = 0;
    }

    /* Calcula taxa de mortalidade */
    int herois_mortos = 0;
    for (int i = 0; i < mundo->nherois; i++) {
        if (!mundo->herois[i]->vivo) {
            herois_mortos++;
        }
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
