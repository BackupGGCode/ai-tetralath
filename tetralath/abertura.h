/*
* Abertura do jogo tetralath.
* Capaz de verificar se a abertura de aplica a um tabuleiro, conferindo
* se as casas que necessita est�o livres.
*/

#include <iostream>
#ifndef STRING_E_VECTOR
#define STRING_E_VECTOR
	#include <string>
	#include <vector>
#endif

using namespace std;

class tabuleiroTetralath;

class abertura{
	public:

	/*
	* Valor de nome dado a casa n�o existente.
	*/
	static const int CASA_INEXISTENTE = -1;

	/*
	* Indicam as aberturas dispon�veis.
	*/
	static const int SEM_ABERTURA = 0;
	static const int ABERTURA_DUPLA = 1;
	static const int ABERTURA_TRIANGULO_AGRESSIVO = 2;
	static const int ABERTURA_DUPLA_FILEIRA_AGRESSIVA = 3;

	/*
	* Aberturas existentes. Todas definidas no fim do arquivo, ap�s a defini��o desta classe.
	*/
	static int DUPLA[];
	static int TRIANGULO_AGRESSIVO[];

	/*
	* Cria nova abertura.
	* @param _tipo Diz o tipo, um dentre os definidos nesta classe.
	*/
	abertura(int _tipo);

	/*
	* @return nome da pr�xima casa em que se deve jogar. Caso o limite j� tenha sido excedido, retorna CASA_INEXISTENTE.
	*/
	int getNomeProximaJogada();

	/*
	* Incrementa o contador da jogada atual.
	*/
	void jogar();

	/*
	* @param _tabuleiro Tabuleiro em que o teste ser� feito.
	* @return Booleano indicando se � poss�vel utilizar esta abertura no tabuleiro dado, se as casas
	*					que ela necessita est�o livres.
	* Obs.: O teste considera a pr�xima jogada a ser feita desta abertura.
	* Obs2.: Esta fun��o considera somente as casas do vetor casas, n�o considerada transla��es e rota��es.
	*/
	bool aplicavelAoTabuleiro(tabuleiroTetralath *_tabuleiro);

	private:

	/*
	* Diz o tipo da abertura, que define as casas base em que se joga.
	*/
	int tipo;

	/*
	* �ndice da �ltima jogada feita com getNomeProximaJogada.
	*/
	int indiceUltimaJogada;

	/*
	* Vetor que indica as casas em que se deve jogar para realizar esta abertura.
	*/
	vector<int> casas;


};



