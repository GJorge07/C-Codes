//Protótipos de outras funções utilizadas para realizar a simulação do mundo.

#ifndef OUTRAS_FUNCOES_H
#define OUTRAS_FUNCOES_H

//includes

int valida_base(mundo_t *mundo, int base);

int valida_heroi(mundo_t *mundo, int heroi);

int valida_fila(mundo_t *mundo, int base);

void cria_chega();

void cria_espera();

void cria_desiste();

void cria_avisa();

void cria_viaja();

void cria_sai();

void cria_entra();

void cria_morre();

void imprime_chega_e_espera();

void imprime_chega_e_desiste();

void imprime_espera();

void imprime_desiste();

void imprime_avisa_porteiro();

void imprime_avisa_e_admite();

void imprime_entrada();

void imprime_saida();

void imprime_viagem();

void imprime_morte();

/*As funções de imprimir missão e imprimir fim deixei para colocar no eventos pois são mais complexas*/

//Outras funções usadas em eventos.c????

#endif