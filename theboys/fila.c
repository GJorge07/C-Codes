#include "stdio.h"
#include "stdlib.h"

// descreve um nodo da fila 
struct fila_nodo_t
{
	int item;					// item associado ao nodo
	struct fila_nodo_t *prox;	// próximo nodo
};

// descreve uma fila 
struct fila_t
{
	struct fila_nodo_t *prim ;	// primeiro nodo da fila
	struct fila_nodo_t *ult ;	// último nodo da fila
	int num ;					// número de itens na fila
};

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f) {
	
	if (f == NULL || f->prim == NULL)	/*se fila nao existe ou é vazia*/
		return;
	
	struct fila_nodo_t *aux = f->prim;

	while (aux != NULL) {				/*laço que percorre a fila inteira*/
					
		printf("%d", aux->item);
		if (aux->prox != NULL)
			printf(" ");
		
		aux = aux->prox;
	}
	
}

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria () {
	struct fila_t *f = malloc(sizeof(struct fila_t));

	if (f != NULL) {
		f->prim = NULL;		/*Verifica se não é NULL e cria fila (primeiro nodo e num)*/
		f->ult = NULL;
		f->num = 0;
		return f;
	}
		
	return NULL;
}

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item) {

	struct fila_nodo_t *novo;

	if (f == NULL)
		return 0;

	novo = malloc(sizeof(struct fila_nodo_t));

	if (novo == NULL)
		return 0;

	novo->item = item;			/*cria novo nó pra novo*/
	novo->prox = NULL;

	if (f->prim == NULL)
    	f->prim = novo;   /*primeiro elemento da fila*/

	else 
    	f->ult->prox = novo;
	
	f->ult = novo;
	f->num++;
	return 1;
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item) {

	if (f == NULL || f->prim == NULL)
		return 0;
	
	struct fila_nodo_t *remove = f->prim;

	*item = remove->item;  /* *item recebe o primeiro item, pra devolver o elemento retirado*/


	f->prim = remove->prox;				 /*passa o nodo para o próximo e retira o primeiro*/

	if (f->prim == NULL)
    	f->ult = NULL; /* fila ficou vazia*/

	f->num--;
	free(remove);

	return 1;

}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f) {
	
	if (f == NULL)		/*Se a fila não existir, retorna erro*/
		return -1;

	return f->num; 
}


// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
/*nao libera o conteudo da fila(item),pois é int*/
struct fila_t *fila_destroi (struct fila_t *f) {
	
	struct fila_nodo_t *aux, *prox;

	if (f != NULL) {

		aux = f->prim;
		while (aux != NULL) {

			prox = aux->prox;		/*guarda aux->prox antes de destruir aux*/
			free(aux);				/*libera a fila*/
			aux = prox;
		}

	free(f);						/*destrói a fila*/
	}
	return NULL;
}



