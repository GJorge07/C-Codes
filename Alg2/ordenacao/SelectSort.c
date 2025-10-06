void selectionsort(int vetor [], int n) {   //ORDEM DESCRESCENTE
    int maior,i,j,aux;
    for (i = 0; i < n - 1 ; i++ ) {
        maior = i;
        for (j = i + 1; j < n; j++) {
            if (vetor[j] > vetor[maior])
                maior = j;
        }
        if (maior != i) {
            aux = vetor[maior];
            vetor[maior] = vetor[i]; 
            vetor[i] = aux;      
        }
    }
}

void selectionsort(int vetor [], int n) {   //ORDEM CRESCENTE
    int menor,i,j,aux;
    for (i = 0; i < n - 1 ; i++ ) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[menor])
                menor = j;
        }
        if (menor != i) {
            aux = vetor[menor];
            vetor[menor] = vetor[i]; 
            vetor[i] = aux;      
        }
    }
}