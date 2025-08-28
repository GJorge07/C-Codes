/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>  /*para a função aleatório*/
#include "racional.h"

/* programa principal */

int main ()
{
    int i,n,max;
    struct racional r1,r2;
    struct racional soma, sub, mult, div;

    srand (0);


    scanf("%d",&n);
    scanf("%d",&max);

    for (i = 1; i <=n ; i++) {

        printf("%d: ",i);
        r1 = sorteia_r(-max,max);
        imprime_r(r1);
        printf(" ");

        r2 = sorteia_r(-max,max);
        imprime_r(r2);
        printf(" ");


        if (!valido_r(r1) || !valido_r(r2)) {
            printf("%c","NUMERO INVALIDO");
            return 1;
        }

        soma = soma_r(r1,r2);
        sub = subtrai_r(r1,r2);
        mult = multiplica_r(r1,r2);
        div = divide_r(r1,r2);
        
        if  (!valido_r(div)){
            printf("%c""DIVISAO INVALIDA");
            return 1;
        }
        imprime_r (soma);
        printf(" ");
        imprime_r(sub);
        printf(" ");
        imprime_r(mult);
        printf(" ");
        imprime_r(div);
        printf("\n");
    }
    return (0) ;
}
