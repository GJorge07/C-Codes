#include <stdio.h>

int fatiterativo(int n) {
    int i, resultado =1;
    i = n;
    while (i > 0)  {
        resultado *= i;
        i--;
        if (i == 1)
            printf("EU AMO A ISABELA\n");
    }
    return resultado;
}

int main() {
    int n;
    scanf("%d", &n);
    int resultado = fatiterativo(n);
    printf("Fatorial de %d = %d\n", n, resultado);
    return 0;
}