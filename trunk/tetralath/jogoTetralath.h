#include <iostream>

#ifndef INTERFACE_GUI
#define INTERFACE_GUI

#include "interface_gui.h"
 
#endif

#ifndef JOGADOR_TETRALATH
#define JOGADOR_TETRALATH

#include "jogadorTetralath.h"
 
#endif

using namespace std;

/*
* Representa��o de um jogo de tetralath.
*/
class jogoTetralath{
	public:
	/*
	* Define os tipos de jogos.
	*/
	static const int JOGO_HUMANO_VS_PC = 0;
	static const int JOGO_HUMANO_VS_HUMANO = 1;
	static const int JOGO_PC_VS_PC = 2;
	
	/*
	* Define os poss�veis fins deste jogo.
	*/
	static const int EMPATE = 0; //se houve empate. 
	static const int JOGADOR_UM_GANHOU = 1; //se o jogador um ganhou o jogo.
	static const int JOGADOR_DOIS_GANHOU = 2; //se o jogador dois ganhou o jogo.
	static const int NAO_TERMINOU = 3; //se o jogo ainda n�o terminou.
		
	/*
	* Cria um novo jogo, com base no seu tipo, e o retorna.
	* @param _tipoJogo Define o tipo de jogo, se entre dois humanos, humano e pc ou pc contra pc.
	* @param _tabuleiroJogo Tabuleiro em que acontece o jogo.
	* @param _jogadorUm O jogador que far� a primeira jogada.
	* @param _jogadorDois O jogador que far� a segunda jogada.
	*/
	jogoTetralath(tabuleiroTetralath _tabuleiroJogo, jogadorTetralath *_jogadorUm, jogadorTetralath *_jogadorDois);

	/*
	* Inicia o jogo. Esta fun��o s� retornar� quando o jogo estiver terminado.
	* @param _interfaceUsuario A interface_gui usada para comunica��o com o usu�rio.
	* @return O jogador que ganhou o jogo.
	*/
	jogadorTetralath* iniciarJogo(interface_gui *_interfaceUsuario);

	/*
	* Deve ser chamada ao fim de uma jogada.
	* Ir� conferir se o jogo acabou e dir� de quem � a vit�ria.
	* @return EMPATE, se houve empate. 
	*		  JOGADOR_UM_GANHOU, se o jogador um ganhou o jogo.
	*		  JOGADOR_DOIS_GANHOU, se o jogador dois ganhou o jogo.
	*		  NAO_TERMINOU, se o jogo ainda n�o terminou.
	*/
	int conferirFimDoJogo();
		
	private:
	/*
	* O jogador que far� a primeira jogada.
	*/
	jogadorTetralath* jogadorUm;
	
	/*
	* O jogador que far� a segunda jogada.
	*/
	jogadorTetralath* jogadorDois;

	/*
	* Tabuleiro em que acontece o jogo.
	*/
	tabuleiroTetralath tabuleiroJogo;
};