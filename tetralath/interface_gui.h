#ifndef STRING_E_VECTOR
#define STRING_E_VECTOR
	#include <string>
	#include <vector>
#endif

class menu;
class tabuleiroTetralath;

using namespace std;

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
#define COMANDO_DEBUG_AVALIAR 'm'

class interface_gui{
	public:
	/*
	* Indicam as dimens�es da linha de comando.
	*/
	static const int LINHAS = 40;
	static const int COLUNAS = 150;

	/*
	* Construtor da classe.
	*/
	interface_gui();
	/*
	* Imprime um texto centralizado na tela.
	* @param texto_param Texto a ser impresso.
	*/
	static void imprimirTextoCentralizado(string texto_param);
	/*
	* Imprime tantos espa�os quanto for especificado.
	* @param _quantidadeEspacos Quantidade de espa�os que ser� impressa na tela.
	*/
	static void imprimirEspacos(int _quantidadeEspacos);
	/*
	* Espera por comando do usu�rio e o retorna, quando for feito.
	* @param _possivelTerminar Booleano que liga/desliga a atribui��o da flag que sinaliza a entrada de um COMANDO_FECHAR.
	* @return O comando digitado pelo usu�rio. N�o retorna comandos com CAPS, prefere sempre sua vers�o em lower case.
	*/
	char esperarComandoUsuario(bool _possivelTerminar);
	/*
	* Imprime uma tela que permite escolha entre v�rias op��es.
	* @param _opcoes Array de op��es que o usu�rio possui.
	* @param _opcaoEscolhida O �ndice, no array, da op��o escolhida. Se exceder os limites do array, ser� real�ada a �ltima.
	*/
	void imprimirTelaEscolhaEstatica(vector<string> _opcoes, int _opcaoEscolhida);
	/*
	* Controla a impress�o da tela de escolha com base em entrada do usu�rio.
	* @param _opcoes Op��es excludentes dentre as quais o usu�rio pode escolher.
	* @return Op��o que foi escolhida.
	*/
	int imprimirTelaEscolha(vector<string> _opcoes);
	/*
	* Imprime uma tela de escolha em que cada op��o � um submenu que pode ser acessado com [ENTER].
	* Recebe um objeto menu e nele define as op��es selecionadas.
	* @param _menu Vector de vectors. Cada vector � um submenu de op��es, que s�o strings.
	* Exemplo:
	*	imprimirTelaMenus(vector(vector("brancas","pretas"), 
								 vector("maquina", "humano"))) 
			= vector("brancas", "maquina")
	*/
	void imprimirTelaMenus(menu *_menu);
	/*
	* Imprime a tela do jogo.
	* @param casaAtual_param A casa em que est� o cursor.
	* @param tabuleiro_param O tabuleiro que ser� impresso.
	*/
	void imprimirTelaTabuleiro(int casaAtual_param, tabuleiroTetralath *tabuleiro_param);
	/*
	* Imprime a tela do resultado de um jogo.
	* @param cor_pecas_ganhadoras_param A cor das pe�as que ganharam o jogo. Qualquer valor diferente de PECAS_PRETAS e PECAS_BRANCAS � empate.
	* @param casaAtual_param A casa em que est� o cursor.
	* @param tabuleiro_param O tabuleiro que ser� impresso.
	*/
	void imprimirTelaResultado(int cor_pecas_ganhadoras_param, int casaAtual_param, tabuleiroTetralath *tabuleiro_param);
	/*
	* Imprime a tela que informa ao usu�rio para aguardar a jogada da intelig�ncia artificial.
	*/
	void imprimirTelaAguardarJogada();
	/*
	* Imprime todas as cores poss�veis no prompt no windows (S� funciona no windows!!!!!!).
	*/
	void imprimirCoresWindows(void);
	/*
	* @return Booleano que indica se o usu�rio informou � esta gui que deseja terminar o programa.
	*/
	bool usuarioQuerFecharPrograma();
	/*
	* Redimensiona esta gui para as dimens�es dadas.
	* @param _numeroLinhas O n�mero de linhas que a gui ter�.
	* @param _numeroColunas O n�mero de colunas que a gui ter�.
	*/
	void redimensionar(int _numeroLinhas, int _numeroColunas);
	/*
	* Gera string cujo �nico caractere tem o c�digo ASCII passado.
	* @param _codigoASCII C�digo ASCII do caractere que se quer na string.
	* @return String cujo �nico caractere tem o c�digo ASCII passado.
	*/
	static string getStringCaractereASCII(int _codigoASCII);

	private:
	/*
	* Booleano que indica se o usu�rio informou � esta gui que deseja terminar o programa.
	*/
	bool deveTerminar;

	/*
	* Imprime um comando com letras brancas em colchetes.
	* @param comando_param Comando a imprimir.
	*/
	void imprimirComando(string comando_param);
};