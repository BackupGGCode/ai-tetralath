#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef IA
#define IA

#include "ia.h"

#endif

#ifndef TABULEIRO_TETRALATH
#define TABULEIRO_TETRALATH

#include "tabuleiroTetralath.h"
 
#endif

/*
* Define um jogador de tetralath, seja ele artificial ou humano.
* Esta classe � abstrata, define a interface para seus dois tipos poss�veis.
*/
class jogadorTetralath{
	public:
	/*
	* Define o tipo do jogador, m�quina ou humano.
	*/
	static const int TIPO_HUMANO = 1;
	static const int TIPO_MAQUINA = 2;
	
	/*
	* @param _cor A cor das pe�as deste jogador. As cores s�o definidas em casaTabuleiroTetralath.
	*/
	void setCorPecas(int _cor);
	
	/*
	* A cor das pe�as deste jogador. As cores s�o definidas em casaTabuleiroTetralath.
	*/
	int getCorPecas();

	/*
	* @param _tipo O tipo do jogador, se humano ou m�quina. Tipos s�o definidos neste arquivo.
	*/
	void setTipoJogador(int _tipo);
	
	/*
	* @return O tipo do jogador, se humano ou m�quina. Tipos s�o definidos neste arquivo.
	*/
	int getTipoJogador();

	/*
	* @param _tabuleiro O tabuleiro em que � feita a jogada.
	* @return O �ndice da casa em que o jogador resolveu fazer sua jogada. Esta fun��o � implementada somente nas herdeiras.
	*/
	virtual int getIndiceCasaJogada(tabuleiroTetralath *_tabuleiro) = 0;

	private:
	/*
	* Define a cor das pe�as deste jogador. As cores s�o definidas em casaTabuleiroTetralath.
	*/
	int corPecas;

	/*
	* O tipo do jogador, se humano ou m�quina. Tipos s�o definidos neste arquivo.
	*/
	int tipoJogador;
};