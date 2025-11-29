/*Protótipos de outras funções utilizadas para realizar a simulação do mundo*/
#ifndef OUTRAS_FUNCOES_H
#define OUTRAS_FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "entidades.h"
#include "eventos.h"

int aleat(int min, int max);

int calcula_dist(struct localizacao loc1, struct localizacao loc2);

int Particao(mundo_t *mundo, missao_t *missao, int v[], int ini, int fim);

void quicksort(mundo_t *mundo, missao_t *missao, int dist_missao[], int inicio, int fim);

int valida_heroi(mundo_t *mundo, int heroi);

void cria_chega(mundo_t *mundo, int heroi, int base, int tempo);

void cria_espera(mundo_t *mundo, int tempo, int heroi, int base);

void cria_desiste(mundo_t *mundo, int tempo, int heroi, int base);

void cria_avisa(mundo_t *mundo, int tempo, int base);

void cria_viaja(mundo_t *mundo, int tempo, int heroi, int base_origem, int destino);

void cria_sai(mundo_t *mundo, int tempo, int heroi, int base);

void cria_entra(mundo_t *mundo, int tempo, int heroi, int base);

void cria_morre(mundo_t *mundo, int tempo, int heroi, int base, int missao);

void cria_missao_evento(mundo_t *mundo, int id_missao, int tempo);

void cria_missao(mundo_t *mundo, int id, struct cjto_t *hab, struct localizacao local, int tempo);

void imprime_chega_e_espera(mundo_t *mundo, struct chega *chega);

void imprime_chega_e_desiste(mundo_t *mundo, struct chega *chega);

void imprime_espera(mundo_t *mundo, struct espera *espera);

void imprime_desiste(struct desiste *desiste);

void imprime_avisa_porteiro(mundo_t *mundo, struct avisa *avisa);

void imprime_avisa_e_admite(struct avisa *avisa, int heroi_removido);

void imprime_entra(mundo_t *mundo, struct entra *entra, int sai_tempo);

void imprime_sai(mundo_t *mundo, struct sai *sai);

void imprime_viaja(mundo_t *mundo, struct viaja *viaja, int distancia, int duracao);

void imprime_morre(struct morre *morre);

#endif