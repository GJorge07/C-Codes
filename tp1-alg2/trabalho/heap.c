/*Implementação do Tipo Abstrato de Dados Heap*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //como mexer nisso??
#include "heap.h"

#define CAPACIDADE 1024 //tá bom esse tamanho?? ponteiro??

//Entender como manipular strings!!!!

struct paciente
{
	char nome[50]; //vai dar boa isso??
	int prioridade;
};

struct heap
{
	struct paciente fila[CAPACIDADE];
	int tam;
};

void troca(struct paciente *a, struct paciente *b);
{
	struct paciente aux = *a;
	*a = *b;
	*b = aux;
}

/*Nunca feita
 *Inicializa estrutura de dados heap.
 *Retorna endereço para ela ou NULL em caso de erro
 **/
Heap *InicHeap()
{
	struct heap *h;
	if (!(h = malloc(sizeof(struct heap))))
		return NULL;

	h->tam = 0;

	return h;
}

//professor não manda número a ser inserido no parâmetro, nem atribui ele
/*Insere o paciente, com prioridade e nome, dentro do heap,
 *na posição de acordo com sua prioridade.
 *Retorna 1 se conseguiu inserir;
 *Retorna 0 se o heap estiver cheio.
 **/
int InsereHeap(Heap *h, int prioridade, const char *nome); //tá certo esse nome?
{
	int i = h->tam + 1;

	if (i > CAPACIDADE)
		return 0;
	
	h->fila[i].prioridade = prioridade; //assim o acesso?
	h->fila[i].nome = nome;
	
	while (i > 1 && h->fila[i/2].prioridade < h->fila[i].prioridade) //alguma outra condição de parada??
	{
		troca(h->fila[i/2], h->fila[i]); //isso mesmo ou endereços??
		i = i/2;
	}
	
	h->tam++;

	return 1;
}

/*Nunca feita
 *Como faz caso de erro para fila vazia
 *fila única!!!!
 *
 *Retorna o paciente com maior prioridade e o remove do heap.
 **/
Paciente RemoveHeap(Heap *h);
{
	struct paciente;

	//Testar fila vazia ou única aqui!!!

	removido = h->fila[1];
	
	h->fila[1] = h->fila[h->tam]; /*Coloca o últumo paciente no início*/
	
	h->tam--;
	
	SacodeHeap(h, h->tam);
	
	return removido;
}

/*Reportar número de comparações e trocas!
 *
 *Transforma a estrutura de dados em um heap.
 *Retorna 0 se fila estiver vazia;
 *Retorna 1 se conseguiu heapficar.
 **/
int Heapfy(Heap *h);
{
	int i;

	if (h->tam == 0) //Função encapsulada??
		return 0;

	/*laço que seleciona o da vez que será inserido*/
	for (i = 2; i <= h->tam, i++) InsereHeap(v, i, v[i]);

	return 1;
}

/*Verifica se a estrutura de dados é um heap.
 *Retorna 0 se não for e 1 se for.
 **/
int ChecaHeap(Heap *h);
{
	int i;
	for (i = h->tam; i > 1; i--)
		if (h->fila[i/2].prioridade < h->tam[i].prioridade) //menor ou menor e igual??
			return 0;
	
	return 1;
}

/*NUnca feita
 *Imprime o heap, com cada paciente sendo impresso
 *da seguinte forma: "('prioridade') ('nome')"*/
void ImprimeHeap(const Heap *h); //pq const??
{
	int i;
	
	if (h->tam == 0) //encapsular??
		printf("Fila vazia!");
	
	for (i = 1; i <= h->tam-1; i++)
	{
		printf("(%d - ", h->fila[i].prioridade);
		//como imprime char???
	}
	printf("(%d - ", h->fila[h->tam]);
	//imprimir char
}

/*Reportar número de comparações e trocas
 *
 *Ordena, crescentemente, um heap.
 *Retorna 0 se fila estiver vazia;
 *Retorna 1 se conseguiu ordenar.
 **/
int HeapSort(Heap *h);
{
	int i;

	if (h->tam == 0) //fila vazia??
		return 0;
	
	Heapfy(h);
	
	for (i = h->tam; i > 1; i--)
	{
		troca(h->fila[1], h->fila[i]);
		SacodeHeap(h, i - 1);
	}

	return 1;
}

/*Nunca feita
 *
 *Atualiza a prioridade de algum paciente que piorou ou melhorou:
 *se melhorou = 0, paciente piorou;
 *se melhorou = 1, paciente melhorou.
 *Retorna 0 se paciente não for encontrado ou se a fila estiver vazia;
 *Retorna 1 se conseguiu alterar a prioridade.
 **/
int AlteraHeap(Heap *h,const char *nome, int melhorou); //pq nome??
{
	//como implementar essa busca pelo nome??
	
	if (melhorou)
		troca(x, y);
	
	troca(x, z);
	return;
}

/*Coloca um paciente que está fora de ordem na primeira posição
 *na sua posição certa no heap.
 *Retorna 0 se fila estiver vazia;
 *Retorna 1 se conseguiu sacodir.
 **/
int SacodeHeap(Heap *h, int tam);
{
	int i = 2;

	//casos de erro!!!
	
	while (i <= tam)
	{
		if (i < tam?? h->fila[i+1].prioridade > h->fila[i].prioridade) i++;
		
		if (h->fila[i/2].prioridade >= h->fila[i].prioridade) break;
		
		troca(h->fila[i], h->fila[i/2]); //endereços??
		
		i = i*2;
		/* Será?
		if (v[i/2].prioridade < v[i].prioridade)
			troca(v[i], v[i/2]);
		*/
	}
}