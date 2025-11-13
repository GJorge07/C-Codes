#include "fprio.h"
#include <stdio.h>
#include <stdlib.h>
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades, usada em eventos ESPERA e AVISA
//USADA PRA IMPLEMENTAR A LEF
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// descreve um nodo da fila de prioridades
struct fpnodo_t;
// descreve uma fila de prioridades
struct fprio_t;

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria () {
	struct fprio_t *f = malloc (sizeof(struct fprio_t));
		if ( f!=NULL ) {
			f->prim = NULL;         /*Verifica se não é vazia e cria primeiro nodo e numero de itens na fila*/
			f->num = 0;
			return f;
		}
		return NULL;
	}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f) {
	struct fpnodo_t *aux, *prox;

	if (f != NULL) {
		aux = f->prim;
		while (aux != NULL) {       /*libera até chegar no final da fila*/
			prox = aux->prox;
			if (aux->item != NULL)
				free(aux->item);
			free(aux);
			aux = prox;
			}
	free(f);
	f = NULL;
	}
	return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {

	struct fpnodo_t *aux,*novo;
	
	if (f == NULL || item == NULL)
		return -1;

	novo = malloc(sizeof(struct fpnodo_t));

	if (novo == NULL)
		return -1;

	novo->item = item;			/*cria novo nó pra novo*/
	novo->tipo = tipo;
	novo->prio = prio;
	novo->prox = NULL;

	aux = f->prim;

	while (aux != NULL) {        /*Verificar se não tem item repetido*/
    if (aux->item == item) {
		free(novo);
        return -1;
	}
    aux = aux->prox;
}

	if (f->num == 0) {          /*se a fila for vazia, insere como primeiro*/
		f->prim = novo;
		f->num++;
		return f->num;
	}

	aux = f->prim;

	if (novo->prio < f->prim->prio) { 		/*se tiver que inserir por pŕimeiro*/
		novo->prox = f->prim;
		f->prim = novo;
		f->num++;
		return f->num;
	}

	while (aux->prox && aux->prox->prio <= prio)            /*Inserir no meio, com o FIFO*/
		aux = aux->prox;
	novo->prox = aux->prox;
	aux->prox = novo;
	f->num++;
	return f->num;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio) {

		if (f == NULL || f->prim == NULL)
        return NULL;

		if (tipo == NULL || prio == NULL)
			return NULL;
		
		struct fpnodo_t *remove = f->prim;
		void *item = remove->item;

		
		if (tipo != NULL)
		 	*tipo = remove->tipo;
    	if (prio != NULL) 
			*prio = remove->prio;

		f->prim = remove->prox;
		f->num--;
		free(remove);
		return item;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho(struct fprio_t *f) {

    if (f == NULL)
        return -1;

    return f->num;
}


// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime(struct fprio_t *f) {
    if (f == NULL || f->prim == NULL)
        return;

    struct fpnodo_t *aux = f->prim;

    while (aux != NULL) {
        printf("(%d %d)", aux->tipo, aux->prio);
        if (aux->prox != NULL)   /*espaço só entre elementos*/
            printf(" ");
        aux = aux->prox;
    }
}

