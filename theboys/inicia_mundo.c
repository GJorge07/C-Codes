//Implementação da função que inicializa(cria) o mundo - cria bases, herois e missoes e seta os valores iniciais.
//A principio ta certo, testei e ta funcionando sem leak de memoria
//5 no documento

//includes
#include <stdio.h>
#include <stdlib.h>
#include <time.h>            
#include "inicia_mundo.h"
#include "outras_funcoes.h"

//defines
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100) 
#define N_COMPOSTOS_V (N_HABILIDADES * 3)



//inicializando mundo
 mundo_t *inicia_mundo() {
    mundo_t *mundo = malloc(sizeof(mundo_t));

    if (mundo == NULL) 
        return NULL;
        
    srand(time(NULL));


    //inicializa valores do mundo
    mundo->relogio = T_INICIO;
    mundo->tamanho_mundo.x = N_TAMANHO_MUNDO;
    mundo->tamanho_mundo.y = N_TAMANHO_MUNDO;
    mundo->nhabilidades = N_HABILIDADES;
    mundo->nherois = N_HEROIS;
    mundo->nbases = N_BASES;
    mundo->nmissoes = N_MISSOES;
    mundo->ncompostosv = N_COMPOSTOS_V;

    //inicializa valores de herois
    mundo->herois = malloc(sizeof(heroi_t*)*mundo->nherois);      //faz malloc mesmo ou usa cria cjto??????????

    if (mundo->herois == NULL) 
        return NULL;
    
    for (int i = 0; i < mundo->nherois; i++) {

        mundo->herois[i] = malloc(sizeof(heroi_t));

        if (mundo->herois[i] == NULL) 
            return NULL;

        mundo->herois[i]->id = i;
        mundo->herois[i]->paciencia = aleat(0,100);
        mundo->herois[i]->velocidade = aleat(50,5000);
        mundo->herois[i]->experiencia = 0;
        mundo->herois[i]->habilidades = cjto_aleat(aleat(1,3),10);
    }
    
    //inicializa valores de bases
    mundo->bases = malloc(sizeof(base_t*)*mundo->nbases);          //faz malloc mesmo ou usa cria cjto??????????

    if (mundo->bases == NULL) 
        return NULL;
    
    for (int i = 0; i < mundo->nbases; i++) {
        mundo->bases[i] = malloc(sizeof(base_t));

        if (mundo->bases[i] == NULL) 
            return NULL;

        mundo->bases[i]->id = i;
        mundo->bases[i]->lotacao = aleat(3,10);

        mundo->bases[i]->local_base.x = aleat(0,N_TAMANHO_MUNDO);
        mundo->bases[i]->local_base.y = aleat(0,N_TAMANHO_MUNDO);

        mundo->bases[i]->presentes = cjto_cria(mundo->bases[i]->lotacao);      
        mundo->bases[i]->espera = fila_cria();
    }

    
    //Inicializa valores de missões

    mundo->missoes = malloc(sizeof(missao_t*)*mundo->nmissoes);   //faz malloc mesmo ou usa cria cjto??????????
    
    if (mundo->missoes == NULL) 
        return NULL;

    for (int i = 0; i < mundo->nmissoes; i++) {
        mundo->missoes[i] = malloc(sizeof(missao_t));
        
        if (mundo->missoes[i] == NULL) 
            return NULL;
        
        mundo->missoes[i]->id = i;
        mundo->missoes[i]->local_missao.x = aleat(0,N_TAMANHO_MUNDO);
        mundo->missoes[i]->local_missao.y = aleat(0,N_TAMANHO_MUNDO);
        mundo->missoes[i]->habilidades_missao = cjto_aleat(aleat(6,10),10);
    }
    return mundo;
 } 