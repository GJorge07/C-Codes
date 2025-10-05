/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 09/09/2025 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"
/* coloque aqui as funções auxiliares que precisar neste arquivo */

void libera_r(struct racional **r) {
    if (r != NULL && *r != NULL) {
        free(*r);
        *r = NULL;
    }
}

void imprime_vetor(struct racional *vetor[], int n) {
    printf("VETOR = ");

    for (int i = 0; i < n; i++) {
        imprime_r(vetor[i]);
        if (i < n - 1)
            printf(" ");
    }

    printf("\n");
}

void elimina_vetor(struct racional *vetor[], int *n) {
    int i = 0;
    while (i < *n) {
        if (!valido_r(vetor[i])) {
            libera_r(&vetor[i]);         /* libera o racional inválido*/
            vetor[i] = vetor[*n - 1];   /*coloca o último no lugar*/
            (*n)--;
        } else {
            i++;
        }
    }
}


void ordena_vetor(struct racional *vetor[], int n ) {
    int i,j,menor;
    struct racional *aux;

    for(i = 0; i < n-1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (compara_r(vetor[j], vetor[menor]) < 0) 
                menor = j;
        }
    if (menor != i) {
      aux = vetor[i];
      vetor[i] = vetor[menor];
      vetor[menor] = aux;
    }
    }
}

void soma_vetor(struct racional *vetor[], int n, struct racional **soma) {
    int i;
    struct racional *novo, *antigo;

    *soma = cria_r(0, 1);  /* alocação inicial*/
    if (*soma == NULL) 
      return;

    for (i = 0; i < n; i++) {
        novo = cria_r(0, 1);
        if (novo == NULL) {
            libera_r(soma);
            return;
        }

        if (!soma_r(*soma, vetor[i], novo)) {
            libera_r(&novo);
            libera_r(soma);
            return;
        }

        antigo = *soma;
        *soma = novo;
        libera_r(&antigo);
    }
}

void libera_vetor(struct racional *vetor[], int n) {
    int i;  
    for (i = 0; i < n; i++)
        libera_r(&vetor[i]);
}

/* programa principal */
#include <stdio.h>
#include <stdlib.h>
#include "racional.h"

int main() {
    int n, i;
    long num, den;
    struct racional **vetor = NULL;
    struct racional *soma = NULL;

    
    scanf("%d", &n);
    if (n <= 0 || n >= 100) 
      return 1; 
    
    vetor = malloc(n * sizeof(*vetor));    /*aloca o vetor*/

    if (vetor == NULL)
       return 1;

   
    for (i = 0; i < n; i++) {
        scanf("%ld %ld", &num, &den);
        vetor[i] = cria_r(num, den);

    
        if (vetor[i] == NULL) {
            libera_vetor(vetor, i);
            free(vetor);
            return 1;
        }
    }
  
    imprime_vetor(vetor, n);

    elimina_vetor(vetor, &n);
   
    imprime_vetor(vetor, n);

    ordena_vetor(vetor, n);

    imprime_vetor(vetor, n);
    
    soma_vetor(vetor, n, &soma);

    printf("SOMA = ");
    imprime_r(soma);
    printf("\n");

    libera_vetor(vetor, n);

    imprime_vetor(vetor, n);

    free(vetor);

    libera_r(&soma);

    return 0;
}