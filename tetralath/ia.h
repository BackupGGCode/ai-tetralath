#include <iostream>

#ifndef TABULEIRO_TETRALATH
#define TABULEIRO_TETRALATH

#include "tabuleiroTetralath.h"
 
#endif

/*
* Classe para intelig�ncia artificial.
* Encapsula o algoritmo e permite acesso a resultado parcial em qualquer momento ap�s in�cio da computa��o.
* A classe n�o possui construtor. Ela serve somente para encapsulamento dos algoritmos, "limpando" o c�digo principal
* e permitindo reuso.
* ATEN��O: Como n�o h� construtor, todos dados e m�todos devem ser est�ticos.
*/
class ia{
	public:
	//dados
	/*
	* Usadas para definir se o minimax deve continuar ou ser interrompido.
	*/
	static const bool CONTINUAR = false;
	static const bool PARAR = true;
	
	/*
	* Indicam tipos de movimentos de avalia��o dos valores dos filhos.
	*/
	static const int JOGADA_MAX = 1;
	static const int JOGADA_MIN = 0;
	
	//m�todos
	/*
	* Construtor. N�o faz nada.
	* S� existe porque deixar os m�todos est�ticos estava dando erros demais.
	*/
	ia();
	
	/*
	* Gerencia o uso do minimax at� que a condi��o de parada seja satisfeita.
	* S�o feitas avalia��es em grafos de profundidades crescentes.
	* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
	* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
	*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
	*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � continuar.
	* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
	* @return O nome da casa em que deve ser feita a jogada.
	*/
	int comecar_minimax(tabuleiroTetralath estado_inicial_param, bool *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param);
	
	/*
	* Gerencia o uso do minimax com poda alfa beta at� que a condi��o de parada seja satisfeita.
	* S�o feitas avalia��es em grafos de profundidades crescentes.
	* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
	* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
	*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
	*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � continuar.
	* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
	* @return O melhor estado encontrado para o qual estado_inicial_param pode ir.
	*/
	tabuleiroTetralath comecar_minimax_poda_alfa_beta(tabuleiroTetralath estado_inicial_param, bool *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param);
	
	
	private:
	//dados
	/*
	* Na expans�o do grafo do minimax, � o valor atribu�do ao n�vel do estado_inicial passado � fun��o comecar_(nome do algortimo).
	*/
	static const int NIVEL_INICIAL = 0;

	/*
	* Tabuleiro utilizado nos algoritmos. � sempre inicializado nas fun��es comecar_x.
	*/
	tabuleiroTetralath tabuleiro;
	
	/*
	* Contem o nome da casa em que deve ser feita a jogada, apos execucao do minimax.
	*/
	int resultado_minimax;

	//m�todos

	/*
	* Executa o algoritmo minimax. O caminhamento utilizado � progressivo em profundidade.
	* Utiliza a vari�vel de inst�ncia tabuleiro para dar in�cio ao algoritmo. Todas jogadas s�o simuladas neste tabuleiro.
	* O resultado � colocado em resultado_minimax.
	* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
	*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
	*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � continuar.
	* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
	* @param nivel_maximo_param Especifica quantos niveis (em profundidade) o grafo pode ser expandido.
	* @param nivel_atual_param Define a dist�ncia (no grafo expandido) entre estado_inicial_param e o estado que iniciou esta fun��o.
	*						   Logicamente, na primeira chamada � fun��o, deve conter 0.
	* @param cor_pecas_avaliacao_param Cor das pe�as para a qual as avalia��es devem ser feitas.
	* @return O melhor valor de avalia��o encontrado em toda a sub�rvore do nodo estado_inicial_param.
	*/
	float minimax(bool *deve_parar_param, int tipo_jogada_param, int nivel_maximo_param, int nivel_atual_param, int cor_pecas_avaliacao_param);

	/*
	* Executa o algoritmo minimax com poda alfa beta. O caminhamento utilizado � progressivo em profundidade.
	* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
	* @param resultado_parcial_param Ponteiro para vari�vel em que ser� colocado o resultado parcial. Este resultado s� tem utilidade
	*								 caso corresponda a um objeto diretamente ligado ao objeto que deu in�cio � primeira chamada desta fun��o.
	* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
	*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
	*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � continuar.
	* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
	* @param nivel_maximo_param Especifica quantos niveis (em profundidade) o grafo pode ser expandido.
	* @param nivel_atual_param Define a dist�ncia (no grafo expandido) entre estado_inicial_param e o estado que iniciou esta fun��o.
	*						   Logicamente, na primeira chamada � fun��o, deve conter 0.
	* @return O melhor estado para o qual estado_inicial_param pode ir.
	*/
	float minimax_poda_alfa_beta(tabuleiroTetralath estado_inicial_param, tabuleiroTetralath* resultado_parcial_param, bool *deve_parar_param, 
								 int tipo_jogada_param, int nivel_maximo_param, int nivel_atual_param, int cor_pecas_avaliacao_param);

};