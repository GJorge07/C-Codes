#include "racional.c"

int valido_r (struct racional r) {
    
    if (r.den == 0) {
        return 0;
    }
    
    return 1;
}

