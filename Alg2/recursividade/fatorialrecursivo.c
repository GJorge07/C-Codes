#include <stdio.h>

int fatrecursivo(int n) {  // da pra fzr in resultado e resultado = 1 // resultado = n*fatrecursivo(n-1) // return resultado
     if (n == 0) {
        printf("EU AMO A ISABELA\n");
        return 1;
    }
    else
        return n * fatrecursivo(n-1);
}

int main() {
    int n;
    scanf("%d",&n);
    fatrecursivo(n);
    int resultado = fatrecursivo(n);
    printf("fatorial de %d é = a  %d",n,resultado);
    return 0;
}