#include "jogadorMaquina.h"



/*
* Cria um novo jogador m�quina, passando como argumento o algoritmo que utiliza para suas jogadas.
* @param _iaEscolhida Intelig�ncia artificial deste jogador.
* @param _corPecas Cor das pe�as deste jogador.
*/
jogadorMaquina::jogadorMaquina(ia _iaEscolhida, int _corPecas){
	iaEscolhida = _iaEscolhida;
	setCorPecas(_corPecas);
	setTipoJogador(jogadorTetralath::TIPO_MAQUINA);
}

/*
* @param _tabuleiro O tabuleiro em que � feita a jogada.
* @return O �ndice da casa em que o jogador resolveu fazer sua jogada. Esta fun��o � implementada somente nas herdeiras.
*/
int jogadorMaquina::getIndiceCasaJogada(tabuleiroTetralath _tabuleiro){
	return 0;
}

