#include "racional.c"

struct racional simplifica_r(struct racional r)
{
    int divisor;

    if (r.den == 0){
    return r;
    }

    if ((r.num <0) && (r.den <0)) {
        r.num = r.num * -1;
        r.den = r.den * -1;
    }

    if ((r.den < 0) && (r.num > 0)) {
        r.den = r.den * -1;
        r.num = r.num * -1;
    }


    divisor = mdc(r.num,r.den);
    r.num = r.num / divisor;
    r.den = r.den / divisor;

    return r;
}