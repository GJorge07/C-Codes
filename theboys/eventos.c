//Implementação dos diversos tipos de eventos que podem acontecer no mundo.

//4 no documento - usar fila de prioridade

//includes - falta mais
#include "entidades.h"
#include "eventos.h"
#include "outras_funcoes.h"
#include <math.h>
#include "chama_eventos.h"

//defines
#define T_FIM_DO_MUNDO 1000

void eventos_iniciais(mundo_t *mundo) {

    int base, tempo1, tempo2;

    
    for (int i = 0; i < mundo->nherois; i++) {

        base = aleat(0, mundo->nbases - 1);
        tempo1 = aleat(0, 4321);
        cria_chega(mundo, i, base, tempo1);         //i sao os herois
    }
    
    for (int j = 0; j < mundo->nmissoes; j++) {
        
        tempo2 = aleat(0, T_FIM_DO_MUNDO);
        cria_missao(mundo,j,mundo->missoes[j]->habilidades_missao,mundo->missoes[j]->local_missao,tempo2);
    }
    
    //para o fim, não fiz cria_fim!!!!!!!
    struct fim *fim;
	if (!(fim = malloc(sizeof(struct fim))))
		return; 
	fim->tempo = T_FIM_DO_MUNDO;

	fprio_insere(mundo->lef, fim, FIM, T_FIM_DO_MUNDO);
}

void evento_chega(mundo_t *mundo, struct chega *chega) {

    if (!mundo || !chega)
        return;

    if (!valida_heroi(mundo, chega->heroi) || !valida_base(mundo, chega->base))
        return;

    int espera;

    int lot = mundo->bases[chega->base]->lotacao;          //vagas em B
    int h = cjto_card(mundo->bases[chega->base]->presentes);   //herois presentes na base
    int tam_fila = fila_tamanho(mundo->bases[chega->base]->espera);


    mundo->herois[chega->heroi]->base_atual = chega->base;

    if (tam_fila == 0 && h < lot )       //se há vagas em B e a fila de espera em B está vazia
        espera = 1;
    else 
        espera = mundo->herois[chega->heroi]->paciencia > (10 * tam_fila);
    

    if (espera) {
        imprime_chega_e_espera(mundo, chega);
        cria_espera(mundo, chega->tempo, chega->heroi, chega->base);
        
    }

    else {
        imprime_chega_e_desiste(mundo, chega);
        cria_desiste(mundo, chega->tempo, chega->heroi, chega->base);
    }
}

//heroi entra na fila de espera e porteiro é avisado
void evento_espera(mundo_t *mundo, struct espera *espera) {

    if (!mundo || !espera)          //Pra não dar seg fault antes
        return;

    if (!valida_heroi(mundo, espera->heroi) || !valida_base(mundo, espera->base))
        return;

    imprime_espera(mundo, espera);

    fila_insere(mundo->bases[espera->base]->espera, espera->heroi);     //insere heroi na base B

    cria_avisa(mundo, espera->tempo, espera->base);


}

void evento_desiste(mundo_t *mundo, struct desiste *desiste) {

    if(!mundo || !desiste)
        return;

    if (!valida_heroi(mundo, desiste->heroi) || !valida_base(mundo, desiste->base))
        return;

    int destino = aleat(0, mundo->nbases - 1);    // precisa do -1??

    cria_viaja(mundo, desiste->tempo, desiste->heroi, destino);

    imprime_desiste(desiste);
}

void evento_avisa(mundo_t *mundo, struct avisa *avisa) {          //ver se ta certo o loop

    if (!mundo || !avisa)
        return;

     if (!valida_base(mundo, avisa->base))
        return;

    int b = mundo->bases[avisa->base]->lotacao;          //vagas em B
    int h = cjto_card(mundo->bases[avisa->base]->presentes);   //herois presentes na base
    int tam_fila = fila_tamanho(mundo->bases[avisa->base]->espera);

    imprime_avisa_porteiro(mundo, avisa);

    while (tam_fila > 0 && b > h ) {            //n tenho ctz q ta certo

        int heroi_removido;

        fila_retira(mundo->bases[avisa->base]->espera, &heroi_removido);         //retira primeiro heroi da fila
        cjto_insere(mundo->bases[avisa->base]->presentes, heroi_removido);       //insere heroi na fila


        imprime_avisa_e_admite(avisa,heroi_removido);

        cria_entra(mundo, avisa->tempo, heroi_removido, avisa->base);

        h = cjto_card(mundo->bases[avisa->base]->presentes);   //herois presentes na base
        tam_fila = fila_tamanho(mundo->bases[avisa->base]->espera);
    }
}

void evento_entra(mundo_t *mundo, struct entra *entra) {

    if (!mundo || !entra)
        return;

    if (!valida_heroi(mundo,entra->heroi) || !valida_base(mundo,entra->base))
        return;

    int tpb = 15 + (mundo->herois[entra->heroi]->paciencia * aleat(1,20));
                    
    cria_sai (mundo, entra->tempo + tpb, entra->heroi, entra->base);

    int tempo_sai = entra->tempo + tpb;

    imprime_entra(mundo, entra, tempo_sai);             //ver se é entra + tpb mesmo

}

void evento_sai(mundo_t *mundo, struct sai *sai) {

    if (!mundo || !sai) 
        return;

     if (!valida_heroi(mundo, sai->heroi) || !valida_base(mundo, sai->base))
        return;

    cjto_retira(mundo->bases[sai->base]->presentes, sai->heroi);    //retira o heroi do conjunto de herois em B
    int destino = aleat(0, mundo->nbases-1);    //escolhe base aleatoria

    cria_viaja(mundo, sai->tempo, sai->heroi, destino);
    cria_avisa(mundo, sai->tempo, sai->base);
    
    imprime_sai(mundo, sai);
}

void evento_viaja(mundo_t *mundo, struct viaja *viaja) {

    if (!mundo || !viaja)
        return;

    if (!valida_heroi(mundo, viaja->heroi) || !valida_base(mundo, viaja->destino))
        return;

    int x1 = mundo->bases[mundo->herois[viaja->heroi]->base_atual]->local_base.x;     //n tenho ctz q é viaja->heroi
    int y1 = mundo->bases[mundo->herois[viaja->heroi]->base_atual]->local_base.y;

    int x2 = mundo->bases[viaja->destino]->local_base.x;
    int y2 = mundo->bases[viaja->destino]->local_base.y;

    int formula1 = (x1 - x2) * (x1 - x2);
	int formula2 = (y1 - y2) * (y1 - y2);
	int formulageral = formula1 + formula2;

    int distancia = (int) sqrt(formulageral);

    int duracao = (distancia / mundo->herois[viaja->heroi]->velocidade);


    cria_chega(mundo, viaja->heroi, viaja->destino, viaja->tempo + duracao); 
    imprime_viaja(mundo, viaja, distancia, duracao);    
}

void evento_morre(mundo_t *mundo, struct morre *morre) {

    if (!mundo || !morre)
        return;

    if (!valida_heroi(mundo, morre->heroi) || !valida_base(mundo, morre->base))
        return;

    cjto_retira(mundo->bases[morre->base]->presentes, morre->heroi);    //retira heroi da base

    mundo->herois[morre->heroi]->vivo = 0;              //heroi = morto

    cria_avisa(mundo, morre->tempo, morre->base);
    imprime_morre(morre);

}

//void evento_missao(mundo_t *mundo, struct missao *missao) {



//}

//void evento_fim(mundo_t *mundo, struct fim *fim) {
    


//}