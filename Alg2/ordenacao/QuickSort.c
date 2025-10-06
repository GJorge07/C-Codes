#include <stdio.h>


int particao(int vetor [], int esq, int dir) {
    
    int pivo, aux, i=esq, j=dir;

    pivo = vetor[esq];

    while (i < j) {
        while (i < j && vetor[i] <= pivo)
            i++;     // avança posição esquerda
        while (i < j && vetor[j] > pivo)
            j --;       // retrai posição direita
        if (i < j) {
            aux = vetor[j];
            vetor[j] = vetor[i];      //troca esq com dir
            vetor[i] = aux;
        }
    }
    vetor[esq] = vetor[j];                 
    vetor[j] = pivo;          // onde a direita parou se torna o novo pivo
    return j;
}


void quicksort(int vetor [], int esq, int dir) {
    int pivo;
    if (esq < dir) {
        pivo = particao(vetor,esq,dir);
        quicksort(vetor, esq, pivo - 1);  //elementos antes do pivo
        quicksort(vetor, pivo + 1, dir);  //elementos dps do pivo
    }         
}


int main () {
    int vetor[10],i;

    for (i = 0; i < 10; i++)
        scanf("%d",&vetor[i]);

    quicksort(vetor,0,9);

    printf("Vetor ordenado: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}