#include <windows.h>
#include <process.h>
#include "jogadorMaquina.h"

/******************************************************************************
*						FUN��ES AUXILIARES
*******************************************************************************/

/*
* A fun��o executa em tempo muito menor ao pedido para o aviso.
* Ela cria uma espera de 5 segundos e, ao final da espera, coloca TRUE em variavel_aviso_param.
* @param variavel_aviso_param Ponteiro cujo conte�do ser� TRUE ap�s tempo_segundos_param.
*/
unsigned int __stdcall esperar(void *variavel_aviso_param){
	Sleep(5000);
	bool *enderecoVariavelAviso = (bool*) variavel_aviso_param;
	*enderecoVariavelAviso = TRUE;
	return 0;
}
void avisarAoFimDeCincoSegundos(bool *variavel_aviso_param){
	*variavel_aviso_param = false;
	_beginthreadex(0, 0, &esperar, (void *) variavel_aviso_param, 0, 0);
}

/******************************************************************************
*						FUN��ES DO HEADER
*******************************************************************************/

/*
* Cria um novo jogador m�quina, passando como argumento o algoritmo que utiliza para suas jogadas.
* @param _iaEscolhida Intelig�ncia artificial deste jogador.
* @param _corPecas Cor das pe�as deste jogador.
*/
jogadorMaquina::jogadorMaquina(ia _iaEscolhida, int _corPecas){
	setCorPecas(_corPecas);
	setTipoJogador(jogadorTetralath::TIPO_MAQUINA);
	iaEscolhida = _iaEscolhida;
}

/*
* @param _tabuleiro O tabuleiro em que � feita a jogada.
* @return O �ndice da casa em que o jogador resolveu fazer sua jogada. Esta fun��o � implementada somente nas herdeiras.
*/
int jogadorMaquina::getIndiceCasaJogada(tabuleiroTetralath *_tabuleiro){
	bool condicaoParadaMinimax = false;
	avisarAoFimDeCincoSegundos(&condicaoParadaMinimax);
	return iaEscolhida.comecar_avaliacao(*_tabuleiro, &condicaoParadaMinimax, ia::JOGADA_MAX, getCorPecas());
}









