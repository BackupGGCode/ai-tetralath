#ifndef TABULEIRO_TETRALATH
#define TABULEIRO_TETRALATH

#include "tabuleiroTetralath.h"
 
#endif

/*
* Concentra todas fun��es da interface, isto �, a parte visual do jogo.
*/

/**************************************************
* Declara��es de comandos da interface do jogo.
*
*/
#define MOVIMENTO_CIMA 'w' //Movimenta para o vizinho A, se existir.
#define MOVIMENTO_CIMA_CAPS 'W'
#define MOVIMENTO_BAIXO 's' //Movimenta para o vizinho F, se existir.
#define MOVIMENTO_BAIXO_CAPS 'S'
#define MOVIMENTO_ESQUERDA 'a' //Movimenta para o vizinho C, se existir.
#define MOVIMENTO_ESQUERDA_CAPS 'A'
#define MOVIMENTO_DIREITA 'd' //Movimenta para o vizinho D, se existir.
#define MOVIMENTO_DIREITA_CAPS 'D'
#define COMANDO_FECHAR 'q' //Termina a aplica��o.
#define COMANDO_FECHAR_CAPS 'Q'
#define COMANDO_JOGAR 'j' //Faz uma jogada na posi��o em que estiver, se poss�vel.
#define COMANDO_JOGAR_CAPS 'J'
#define COMANDO_JOGAR_ALTERNATIVO ' '
#define COMANDO_DESFAZER_JOGADA 'z' //Desfaz a �ltima jogada.
#define COMANDO_DESFAZER_JOGADA_CAPS 'Z' 
#define COMANDO_SEM_ACAO 'o' //Usado para inicializa��o. N�o deve ter a��o atribu�da.
#define COMANDO_ESCOLHER_BRANCAS 'b' //No in�cio, escolhe as pe�as brancas para o usu�rio.
#define COMANDO_ESCOLHER_PRETAS 'p' //No in�cio, escolhe as pe�as pretas para o usu�rio.
#define COMANDO_ESCOLHER '$'//Faz um escolha em um menu.
#define COMANDO_PERCORRER_ALTERNATIVAS '*'//Percorre alternativas em um menu.

class interface_gui{
	public:
	/*
	* Construtor da classe.
	*/
	interface_gui();
	/*
	* Espera por comando do usu�rio e o retorna, quando for feito.
	* @return O comando digitado pelo usu�rio. N�o retorna comandos com CAPS, prefere sempre sua vers�o em lower case.
	*/
	char esperarComandoUsuario(void);
	/*
	* Imprime a tela inicial, que permite escolha da cor das pe�as do usu�rio.
	* @param opcao_realcar A op��o COMANDO_ESCOLHER_BRANCAS ou COMANDO_ESCOLHER_PRETAS que deve ficar real�ada.
	*/
	void imprimirTelaInicio(char opcao_realcar);
	/*
	* Imprime a tela do jogo.
	* @param casaAtual_param A casa em que est� o cursor.
	* @param pecasDaVez_param A cor das pe�as que est�o jogando.
	* @param tabuleiro_param O tabuleiro que ser� impresso.
	*/
	void imprimirTelaTabuleiro(int casaAtual_param, int pecasDaVez_param, tabuleiroTetralath *tabuleiro_param);
	/*
	* Imprime a tela do resultado de um jogo.
	* @param cor_pecas_ganhadoras_param A cor das pe�as que ganharam o jogo. Qualquer valor diferente de PECAS_PRETAS e PECAS_BRANCAS � empate.
	* @param casaAtual_param A casa em que est� o cursor.
	* @param tabuleiro_param O tabuleiro que ser� impresso.
	*/
	void imprimirTelaResultado(int cor_pecas_ganhadoras_param, int casaAtual_param, tabuleiroTetralath *tabuleiro_param);
	/*
	* Imprime todas as cores poss�veis no prompt no windows (S� funciona no windows!!!!!!).
	*/
	void imprimirCoresWindows(void);
		
	private:
	
	/*
	* Imprime um comando com letras brancas em colchetes.
	* @param comando_param Comando a imprimir.
	*/
	void imprimirComando(string comando_param);
	
	
};