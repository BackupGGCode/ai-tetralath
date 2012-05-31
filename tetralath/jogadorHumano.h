#ifndef JOGADOR_TETRALATH
#define JOGADOR_TETRALATH

#include "jogadorTetralath.h"
 
#endif

#ifndef INTERFACE_GUI
#define INTERFACE_GUI

#include "interface_gui.h"
 
#endif

/*
* Define um jogador controlado por humano.
*/
class jogadorHumano : public jogadorTetralath{
	public:
	/*
	* Cria um novo jogador humano.
	* @param _interfaceComunicacaoUsuario A interface pela qual ser� poss�vel comunicar-se com o usu�rio.
	* @param _corPecas Cor das pe�as deste jogador.
	*/
	jogadorHumano(interface_gui _interfaceComunicacaoUsuario, int _corPecas);

	/*
	* Nesta classe, esta fun��o aguardar� entrada do usu�rio e retornar� a casa escolhida por ele, quando ele escolher uma casa v�lida.
	* Atente para o fato de que o usu�rio pode terminar a aplica��o aqui, atrav�s da interface.
	* @param _tabuleiro O tabuleiro em que � feita a jogada.
	* @return O �ndice da casa em que o jogador resolveu fazer sua jogada. Esta fun��o � implementada somente nas herdeiras.
	*/
	int getIndiceCasaJogada(tabuleiroTetralath _tabuleiro);

	private:
	/*
	* A interface pela qual ser� poss�vel comunicar-se com o usu�rio.
	*/
	interface_gui interfaceComunicacaoUsuario;
};