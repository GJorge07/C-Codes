/* Implementação da função que inicializa(cria) o mundo - cria bases, herois e missoes e seta os valores iniciais. */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  

#include "inicia_mundo.h"
#include "outras_funcoes.h"
#include "entidades.h"

/* inicializando mundo */
 mundo_t *inicia_mundo() {
    mundo_t *mundo;

    if (!(mundo = malloc(sizeof(mundo_t))))
        return NULL;
        
    mundo->lef = fprio_cria();  /*cria a lef*/
    if (mundo->lef == NULL)
        return NULL;


    /* inicializa valores do mundo */
    mundo->relogio = T_INICIO;
    mundo->tamanho_mundo.x = N_TAMANHO_MUNDO;
    mundo->tamanho_mundo.y = N_TAMANHO_MUNDO;
    mundo->nhabilidades = N_HABILIDADES;
    mundo->nherois = N_HEROIS;
    mundo->nbases = N_BASES;
    mundo->nmissoes = N_MISSOES;
    mundo->ncompostosv = N_COMPOSTOS_V;
    mundo->neventos = 0;

    /* inicializa valores de herois */
    mundo->herois = malloc(sizeof(heroi_t*)*mundo->nherois); 

    if (mundo->herois == NULL) 
        return NULL;
    
    for (int i = 0; i < mundo->nherois; i++) {

        mundo->herois[i] = malloc(sizeof(heroi_t));

        if (mundo->herois[i] == NULL) 
            return NULL;

        mundo->herois[i]->vivo = 1;    
        mundo->herois[i]->id = i;
        mundo->herois[i]->base_atual = -1; 
        mundo->herois[i]->paciencia = aleat(0,100);
        mundo->herois[i]->velocidade = aleat(50,5000);
        mundo->herois[i]->experiencia = 0;
        mundo->herois[i]->habilidades = cjto_aleat(aleat(1,3),10);
    }
    
    /* inicializa valores de bases */
    mundo->bases = malloc(sizeof(base_t*)*mundo->nbases);          

    if (mundo->bases == NULL) 
        return NULL;
    
    for (int i = 0; i < mundo->nbases; i++) {
        mundo->bases[i] = malloc(sizeof(base_t));

        if (mundo->bases[i] == NULL) 
            return NULL;

        mundo->bases[i]->id = i;
        mundo->bases[i]->fila_max = 0;
        mundo->bases[i]->missoes_cumpridas = 0;
        mundo->bases[i]->lotacao = aleat(3,10);

        mundo->bases[i]->local_base.x = aleat(0,N_TAMANHO_MUNDO);
        mundo->bases[i]->local_base.y = aleat(0,N_TAMANHO_MUNDO);

        mundo->bases[i]->presentes = cjto_cria(mundo->nherois);      
        mundo->bases[i]->espera = fila_cria();
    }

    /* inicializa valores de missões */
    mundo->missoes = malloc(sizeof(missao_t*)*mundo->nmissoes);  
    
    if (mundo->missoes == NULL) 
        return NULL;

    for (int i = 0; i < mundo->nmissoes; i++) {
        mundo->missoes[i] = malloc(sizeof(missao_t));
        
        if (mundo->missoes[i] == NULL) 
            return NULL;
        
        mundo->missoes[i]->id = i;
        mundo->missoes[i]->cumprida = 0;
        mundo->missoes[i]->tentativas = 0;
        mundo->missoes[i]->local_missao.x = aleat(0,N_TAMANHO_MUNDO);
        mundo->missoes[i]->local_missao.y = aleat(0,N_TAMANHO_MUNDO);
        mundo->missoes[i]->habilidades_missao = cjto_aleat(aleat(6,10),10);
    }
    return mundo;
 } 