void bubblesort(int vetor [], int n) {  //ORDENA DECRESCENTE
    int i,aux;

    do { 
    for(i = 0; i < n-1; i++) { 
            if (vetor[i+1] > vetor[i]) {
                    aux = vetor[i+1];
                    vetor[i+1] = vetor[i];
                    vetor[i] = aux;
            }
        }
    n--;
    }   
    while (n > 1);
}

void bubblesort(int vetor [], int n) {  //ORDENA CRESCENTE
    int i,aux; 

    do { 
    for(i = 0; i < n-1; i++) { 
            if (vetor[i+1] < vetor[i]) {
                    aux = vetor[i+1];
                    vetor[i+1] = vetor[i];
                    vetor[i] = aux;
            }
        }
    n--;     // pq o ultimo elemento(o maior) ja vai tar na poisção correta, mas os outros talvez nao
    }   
    while (n > 1);
}
