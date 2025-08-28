#include "racional.c"

struct racional cria_r (int numerador, int denominador) {
    struct racional r;

    r.num = numerador;
    r.den = denominador;

    return r;
}
