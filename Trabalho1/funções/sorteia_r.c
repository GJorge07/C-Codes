#include "racional.c"

struct racional sorteia_r (int min, int max) {
    struct racional r;
    
    r.num = rand() % (max - min + 1) + min;
    r.den = rand() % (max - min + 1) + min;
    
    return r;
}

/* colocar  #include <stdlib.h>*/