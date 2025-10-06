#include <stdio.h>

void levetor(int vetor [], int n) {
    int i;
    for (i = 1; i < n ; i++)
        scanf("%d",&vetor[i]);
}

int comsentinela(int vetor [], int n, int procurado) {
    int i=0;
    vetor[0] = procurado;
    while (vetor[i]!=procurado) 
        i++;
    if  (i!=0)
        return i;
    return -1;
}


int main() { 
    int n,x,vetor[100],procurado;
    scanf("%d",&n);
    levetor(vetor,n);
    scanf("%d",&procurado);
    x = comsentinela(vetor,n,procurado);
    printf("%d",x);
}

     



//Escreva dois programas na linguagem C que implementam o algoritmo da pesquisa sequencial, inspecionando o
// vetor a partir da última posição, COM e SEM sentinela. Faça um procedimento para criar um vetor de números 
// aleatórios, e permita que o usuário entre com o elemento a ser procurado. Edite, compile e execute seus programas.