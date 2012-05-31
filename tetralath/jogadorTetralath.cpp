#include "jogadorTetralath.h"

/*
* @param _cor A cor das pe�as deste jogador. As cores s�o definidas em casaTabuleiroTetralath.
*/
void jogadorTetralath::setCorPecas(int _cor){
	corPecas = _cor;
}

/*
* A cor das pe�as deste jogador. As cores s�o definidas em casaTabuleiroTetralath.
*/
int jogadorTetralath::getCorPecas(){
	return corPecas;
}

/*
* @param _tipo O tipo do jogador, se humano ou m�quina. Tipos s�o definidos neste arquivo.
*/
void jogadorTetralath::setTipoJogador(int _tipo){
	tipoJogador = _tipo;
}

/*
* @return O tipo do jogador, se humano ou m�quina. Tipos s�o definidos neste arquivo.
*/
int jogadorTetralath::getTipoJogador(){
	return tipoJogador;
}