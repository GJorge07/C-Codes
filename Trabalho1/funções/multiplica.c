#include "racional.c"
#include "simplifica.c"

struct racional multiplica_r (struct racional r1, struct racional r2) {
    struct racional resultado;

    if (!valido_r(r1) || !valido_r(r2)) {
        resultado.num = 0;
        resultado.den = 0;
        return resultado;
    } 

    resultado.num = r1.num * r2.num;
    resultado.den = r1.den * r2.den;

    resultado = simplifica_r(resultado);
    return resultado;
}