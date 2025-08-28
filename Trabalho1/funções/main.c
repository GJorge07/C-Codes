#include <stdio.h>
#include <stdlib.h>
#include "racional.h"
#define RACIONAL

int i,n,max,r1,r2;

int main() {

    srand(0);

    scanf("%d",&n);
    scanf("%d",&max);

    for (i=1;1<=n;i++) {

        printf("%d %c",i,":");
        r1 = sorteia_r(-max,max);
        imprime_r(r1);

        r2 = sorteia_r(-max,max);
        imprime_r(r2);

        if (!valido_r(r1) || !valido(r2)) {
            printf("NUMERO INVALIDO");
            return 1;
        }
        soma_r(r1,r2);
        subtrai_r(r1,r2);
        multiplica_r(r1,r2);
        divide_r(r1,r2);
        
        if  (!valido_r(r2)){
            printf("DIVISAO INVALIDA");
            return 1;
        }
        printf(soma_r(r1,r2));
        printf(subtrai_r(r1,r2));
        printf(multiplica_r(r1,r2));
        printf(divide_r(r1,r2));
        return (0); 
    }
}
