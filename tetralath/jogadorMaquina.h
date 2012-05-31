#ifndef JOGADOR_TETRALATH
#define JOGADOR_TETRALATH

#include "jogadorTetralath.h"
 
#endif

/*
* Define um jogador controlado pela m�quina, via intelig�ncia artificial.
*/
class jogadorMaquina : public jogadorTetralath{
	public:
	/*
	* Cria um novo jogador m�quina, passando como argumento o algoritmo que utiliza para suas jogadas.
	* @param _iaEscolhida Intelig�ncia artificial deste jogador.
	* @param _corPecas Cor das pe�as deste jogador.
	*/
	jogadorMaquina(ia _iaEscolhida, int _corPecas);

	/*
	* Nesta classe, esta fun��o chamar� o algoritmo da ia para decidir qual jogada deve ser feita.
	* @param _tabuleiro O tabuleiro em que � feita a jogada.
	* @return O �ndice da casa em que o jogador resolveu fazer sua jogada. Esta fun��o � implementada somente nas herdeiras.
	*/
	int getIndiceCasaJogada(tabuleiroTetralath _tabuleiro);

	private:
	/*
	* Intelig�ncia artificial deste jogador.
	*/
	ia iaEscolhida;
};