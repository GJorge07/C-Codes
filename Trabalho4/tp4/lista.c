#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
/* coloque demais includes aqui */

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (){
        struct lista *l = malloc(sizeof(struct lista));       /*aloca espaço p lista*/
        if (l!= NULL) {
            l->ini = NULL;
            l->ptr = NULL;
            l->tamanho = 0;
        }         /*inicializa como vazia a lista se houver espaço disponível*/
        return l;
}

void lista_destroi (struct lista **lista){
    struct nodo *aux,*prox;

    if (lista == NULL || *lista == NULL)
        return;

    aux = (*lista)->ini;

    while (aux != NULL) {
        prox = aux->prox;     /*uso do prox pra nao perder aux*/
        free(aux);           
        aux = prox;       
    }
    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *novo = malloc(sizeof(struct nodo));           /*aloca memoria pra nova inserção*/

    if (novo) {
        novo->chave = chave;            
        novo->prox = lista->ini;              /*novo aponta pro antigo primeiro*/
        lista->ini = novo;                    /*início agora é o novo*/
        lista->tamanho++;
        return 1;
    }
    return 0;
}

int lista_insere_fim (struct lista *lista, int chave){
    struct nodo *aux, *novo = malloc(sizeof(struct nodo));     /*aloca memoria pra nova inserção*/

    if (novo == NULL) 
        return 0;
        
    if (novo) {
        novo->chave = chave;
        novo->prox = NULL;
        if (lista->ini == NULL) {           /*Se o conteúdo da lista for vazio, será como inserir no início*/
            lista->ini = novo;
            lista->tamanho++;
        }
        else {
            aux = lista->ini;             /*Caso contrário, percorremos a lista toda até o aux->prox apontar pro nada*/
            while (aux->prox != NULL)
                 aux = aux->prox;
            aux->prox = novo;
            lista->tamanho++;
        }
        return 1;
    }
    return 0;
}

int lista_insere_ordenado (struct lista *lista, int chave){     

    struct nodo *aux, *novo = malloc(sizeof(struct nodo));

    if (novo) {
        novo->chave = chave;
        novo->prox = NULL;
        if (lista->ini == NULL) { /*Se a lista for vazia, insere como no início*/
            lista->ini = novo;
            lista->tamanho++;
        }
        else if (lista->ini->chave > novo->chave) {    /*se o elemento for o primeiro*/
            novo->prox = lista->ini;
            lista->ini = novo;
            lista->tamanho++;
            }

            else {
            aux = lista->ini;
            while (aux->prox && aux->prox->chave < chave)  /*Caso contrário, insere quando achar alguém maior que o elemento*/
                aux = aux->prox;
            novo->prox = aux->prox;
            aux->prox = novo;
            lista->tamanho++;
            }
            return 1;
        }
    return 0;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    struct nodo *remover;

    if (lista->ini == NULL)         
        return 0;
    
        
    remover = lista->ini;           /*o primeiro elemento vai p segunda posição, e desalocamos a primeira posição*/
    *chave = remover->chave;
    lista->ini = remover->prox;
    free(remover);
    lista->tamanho--;
    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    struct nodo *aux, *remover;    

    if (lista->ini == NULL)         
        return 0;
    
    if (lista->ini->prox == NULL)  {   
        remover = lista->ini;      /*Se o conteúdo da lista for unitário, removemos esse único elemento*/
        lista->ini = NULL;
        *chave =remover->chave;
        free(remover);
        lista->tamanho--;
    }
    else {
        aux = lista->ini;             /*Caso contrário, percorremos a lista toda até o aux->prox apontar pro nada*/
        while (aux->prox->prox != NULL)
            aux = aux->prox;
        remover = aux->prox;
        aux->prox = NULL;
        *chave = remover->chave;               
        free(remover);              /*desalocar memória*/
        lista->tamanho--;
    }
    return 1;
}

int lista_remove_ordenado(struct lista *lista, int chave) {
    struct nodo *aux , *remover;

    if (lista->ini == NULL)
        return 0; 

    aux = lista->ini;
    
    if (lista->ini->chave == chave) {          /*Caso o primeiro elemento seja o que deve ser removido*/
        remover = lista->ini;
        lista->ini = lista->ini->prox;
        free(remover);
        lista->tamanho--;
        return 1;
    }

    while (aux->prox != NULL && aux->prox->chave != chave)         /*Caso nao seja o primeiro elemento*/
        aux = aux->prox;

    if (aux->prox == NULL)
        return 0; 

    remover = aux->prox;
    aux->prox = remover->prox;          /*Faz o antecessor do que foi removido apóntar pro sucessor*/
    free(remover);
    lista->tamanho--;
    return 1;
}


int lista_vazia (struct lista *lista){
    if (lista->ini == NULL)
        return 1;
    return 0;
}

int lista_tamanho (struct lista *lista){
    struct nodo *aux;
    int soma = 0;

    aux = lista->ini;
    while (aux->prox != NULL) {       /*enquanto o prox não for nulo, vai contando, com isso chega até o fim da lista*/
        aux = aux->prox;
        soma++;
    }

    return soma;
}

int lista_pertence (struct lista *lista, int chave){
    struct nodo *aux = lista->ini;

    while (aux != NULL ) {          /*enquanto aux apontar p algo valido, verifica*/
        if (aux->chave == chave)
            return 1;
        aux = aux->prox;
    }
    return 0;
}

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    
    if (lista->ptr == NULL)
    return 0;
    
    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}
