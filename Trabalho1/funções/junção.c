#ifndef RACIONAL
#define RACIONAL
#include <stdlib.h> /* pro sorteia_r*/
#include <racional.h>

struct racional {
  int num;  
  int den;        
};


struct racional cria_r (int numerador, int denominador){

    struct racional r;

    r.num = numerador;
    r.den = denominador;

    return r;
}


int valido_r (struct racional r) {
    
    if (r.den == 0) {
        return 0;
    }
    
    return 1;
}

struct racional sorteia_r (int min, int max) {

    struct racional r;
    
    r.num = rand() % (max - min + 1) + min;
    r.den = rand() % (max - min + 1) + min;
    
    return r;
}

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

struct racional soma_r (struct racional r1, struct racional r2) {

    struct racional resultado;

    if (!valido_r(r1) || !valido_r(r2)) {
        resultado.num = 0;
        resultado.den = 0;
        return resultado;
    } 
    resultado.den = r1.den * r2.den;
    resultado.num = (r1.num * r2.den) + (r2.num * r1.den);
    resultado = simplifica_r(resultado);
    return resultado;
}

struct racional subtrai_r (struct racional r1, struct racional r2) {

    struct racional resultado;

    if (!valido_r(r1) || !valido_r(r2)) {
        resultado.num = 0;
        resultado.den = 0;
        return resultado;
    } 

    resultado.den = r1.den * r2.den;
    resultado.num = (r1.num * r2.den) - (r2.num * r1.den);
    resultado = simplifica_r(resultado);
    return resultado;
}

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
#endif
