// programa principal do projeto "The Boys - 2025/2"
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


/* PROGRAMA PRINCIPAL */

int main () {

	srand(time(NULL));

/*CRIA MUNDO E INICIA ELE*/

	mundo_t *mundo = inicia_mundo();

/*EVENTOS INICIAIS*/

	eventos_iniciais(mundo);

/*CHAMA A LEF*/

	chama_eventos(mundo);

/*DESTRÓI O MUNDO*/

	destroi_mundo(mundo);
	
	return (0) ;
}

