#include <stdio.h>

void levetor(int vetor [], int n) {
    int i;
    for (i = 1; i < n ; i++)
        scanf("%d",&vetor[i]);
}

int pesquisabinaria(int vetor [], int procurado, int n) {
    int meio,esq,dir;
    esq = 0;
    dir = n-1;
    while ((procurado != vetor[meio]) || (esq <= dir)) {
        meio = (esq + dir) / 2;
        if (procurado < vetor[meio])
            dir = meio - 1;
        else
            esq = meio + 1;
    }
    if (procurado == vetor[meio])
        return meio;
    else
        return -1;    

}