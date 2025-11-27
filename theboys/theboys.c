// programa principal do projeto "The Boys - 2024/2"
// Autor: Gabriel Dobrowolski Jorge, GRR 20250938

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "lista.h"
#include "entidades.h"
#include "eventos.h"
#include "inicia_mundo.h"
#include "destroi_mundo.h"
#include "chama_eventos.h"
#include "outras_funcoes.h"


#define T_INICIO 0
#define T_FIM_DO_MUNDO 1000                //525600                  
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)
#define N_COMPOSTOS_V (N_HABILIDADES * 3)

// minimize o uso de variáveis globais

// programa principal
int main ()
{

srand(time(NULL));

/*----------------------------------------------------------------------------------*/
//CRIANDO MUNDO E INICIALIZANDO:

	mundo_t *mundo = inicia_mundo();

/*----------------------------------------------------------------------------------*/
// EVENTOS INICIAIS:

	eventos_iniciais(mundo);

/*----------------------------------------------------------------------------------*/
// CHAMANDO A LEF:

	chama_eventos(mundo);

/*----------------------------------------------------------------------------------*/
//DESTRUINDO O MUNDO:

	destroi_mundo(mundo);
	
/*----------------------------------------------------------------------------------*/
	return (0) ;
}

