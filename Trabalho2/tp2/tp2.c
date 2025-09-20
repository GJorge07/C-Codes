/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 24/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h> 
#include "racional.h"
/* coloque aqui as funções auxiliares que precisar neste arquivo */
void ordena_vetor(struct racional vetor [], int n ) {
    int i,j,menor;
    struct racional aux;

    for(i = 0; i < n-1; i++) {
        menor = i;
      for (j = i + 1; j < n; j++) {
        if (compara_r(vetor[j], vetor[menor]) < 0) {
          menor = j;
        }
      }
      if (menor != i) {
        aux = vetor[i];
        vetor[i] = vetor[menor];
        vetor[menor] = aux;
        }
    }
}

struct racional soma_vetor(struct racional vetor[], int n) { 
    int i;
    struct racional soma = cria_r(0, 1), cont;
    for (i = 0; i < n; i++) {
        soma_r(soma, vetor[i], &cont);
        soma = cont;
    }
    return soma;
}

int elimina_vetor(struct racional vetor[], int n) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        if (valido_r(vetor[esq])) {
            esq++;
        } else {
            /* Troca inválido da esquerda com o da direita */
            struct racional x = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = x;
            dir--;
        }
    }
    return esq;
}

void imprime_v(struct racional vetor [],int n) {
  int i;    
  printf("VETOR = ");

        for (i = 0; i < n; i++) {
        imprime_r(vetor[i]);
        printf(" ");
        }
        printf("\n");
}


/* programa principal */
#define TAM 100
int main ()
{
    int n,i;
    struct racional vetor[TAM];

    scanf("%d",&n);
    if ( n > 0  && n < 100) {

      for(i = 0;i< n ;i++) {
        long num,den;
        scanf("%ld %ld",&num,&den);
        vetor[i] = cria_r(num,den);
      }    
      imprime_v(vetor,n);
     
      n = elimina_vetor(vetor, n);
          
      imprime_v(vetor,n);
     
      ordena_vetor(vetor, n);
              
      imprime_v(vetor,n);

      struct racional soma = soma_vetor(vetor,n);
              
      printf("SOMA = ");
      imprime_r(soma);
      printf("\n");
            
      return 0;
    } 
    else {
      printf("INVALIDO\n");    
  return 0 ;
  }
}