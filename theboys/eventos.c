//Implementação dos diversos tipos de eventos que podem acontecer no mundo.

//4 no documento - usar fila de prioridade

//includes - falta mais
#include "entidades.h"
#include "eventos.h"

//defines

void eventos_iniciais(mundo_t *mundo);

void evento_chega(mundo_t *mundo, struct chega *chega);

void evento_espera(mundo_t *mundo, struct espera *espera);

void evento_desiste(mundo_t *mundo, struct desiste *desiste);

void evento_avisa(mundo_t *mundo, struct avisa *avisa);

void evento_entra(mundo_t *mundo, struct entra *entra);

void evento_sai(mundo_t *mundo, struct sai *sai);

void evento_viaja(mundo_t *mundo, struct viaja *viaja);

void evento_morre(mundo_t *mundo, struct morre *morre);

void evento_missao(mundo_t *mundo, struct missao *missao);

void evento_fim(mundo_t *mundo, struct fim *fim);