#include "racional.c"
#include "simplifica.c"

struct racional divide_r (struct racional r1, struct racional r2) {
    struct racional resultado;

    if ((!valido_r(r1) || !valido_r(r2) || r2.num == 0)) { 
        resultado.num = 0;
        resultado.den = 0;
        return resultado;
    } 

    resultado.num = r1.num *r2.den;
    resultado.den = r1.den *r2.num;

    resultado = simplifica_r(resultado);
    return resultado;
}