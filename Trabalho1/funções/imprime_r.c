#include "racional.c"
#include "simplifica.c"

void imprime_r (struct racional r) {

    r = simplifica_r(r);

    if (r.den == 0) {
        printf("INVALIDO");
        return;
    }
    
    if (r.num == 0) {
        printf("0");
        return;
    }

    if (r.den == 1) {
        printf("%d",r.num);
        return;
    }

    if (r.den == r.num) {
        printf("1");
        return;
    }

    if (r.den < 0 || r.num < 0) {
        printf("-%d/%d", -r.num,r.den);
        return;
    }

    if (r.den <0 && r.num <0) {
        r.den = r.den *-1;
        r.num = r.num *-1;
        printf("%d/%d", r.num, r.den);
        return;
    }
}

