#include <stdio.h>

int fatiterativo(int n) {
    int i, resultado =1;
    i = n+1;  //muda aq
    while (i > 0)  {
        resultado *= i;
        i--;
    }
    resultado = resultado / (n+1);  //muda aq
    return resultado;
}

int main() {
    int n;
    scanf("%d", &n);
    int resultado = fatiterativo(n);
    printf("Fatorial de %d = %d\n", n, resultado);
    return 0;
}
//Uma definição recursiva do fatorial é N! = (N+1)!/(N+1); 
//que tal usar esta definição para implementar uma função no computador?