#include "jogadorHumano.h"



/*
* Cria um novo jogador humano.
* @param _interfaceComunicacaoUsuario A interface pela qual ser� poss�vel comunicar-se com o usu�rio.
* @param _corPecas Cor das pe�as deste jogador.
*/
jogadorHumano::jogadorHumano(interface_gui _interfaceComunicacaoUsuario, int _corPecas){
	setTipoJogador(jogadorTetralath::TIPO_HUMANO);
	setCorPecas(_corPecas);
	interfaceComunicacaoUsuario = _interfaceComunicacaoUsuario;
}
	
/*
* @param _tabuleiro O tabuleiro em que � feita a jogada.
* @return O �ndice da casa em que o jogador resolveu fazer sua jogada. Esta fun��o � implementada somente nas herdeiras.
*/
int jogadorHumano::getIndiceCasaJogada(tabuleiroTetralath _tabuleiro){
	return 0;
}

