/* 
 * Tipos Abstratos de Dados - TADs
 * Arquivo de implementação para TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
 *
 * Este arquivo deve conter as implementações das funções cujos protótipos
 * foram definidos em racional.h. Neste arquivo também podem ser definidas
 * funções auxiliares para facilitar a implementação daquelas funções.
*/

/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h> /* pro sorteia_r*/
#include "racional.h"
#define RACIONAL


/* retorna um número aleatório entre min e max, inclusive. */
long aleat (long min, long max)
{
  return min+rand()%(max-min+1);
}

/* Máximo Divisor Comum entre a e b      */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
    int resto;

    while (b != 0) {
        resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long mmc (long a, long b)
{
  return (a*b) / mdc (a,b);
}

/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
struct racional simplifica_r (struct racional r)
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

    if (r.den <0) {
    r.num = -r.num;
    r.den = -r.den;    /* pro negativo ficar no numerador*/
    }

    return r;
}

/*
 * Implemente aqui as funcoes definidas no racionais.h; caso precise,
 * pode definir aqui funcoes auxiliares adicionais, que devem ser usadas
 * somente neste arquivo.
*/


struct racional cria_r (long  numerador, long denominador){

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

struct racional sorteia_r (long min, long max) {

    struct racional r;
    
    r.num = rand() % (max - min + 1) + min;
    r.den = rand() % (max - min + 1) + min;
    
    return r;
}

void imprime_r (struct racional r) {

    r = simplifica_r(r);

    if (r.den == 0) {
        printf("%c","INVALIDO");
        return;
    }
    
    if (r.num == 0) {
        printf("%d",0);
        return;
    }

    if (r.den == 1) {
        printf("%ld",r.num);
        return;
    }

    if (r.num == r.den) {
        printf("%d",1);
        return;
    }
    printf("%ld/%ld", r.num, r.den);
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
