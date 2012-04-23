#include "ia.h"

/*************************************************************************************
* ATEN��O: � partir daqui, todos m�todos s�o p�blicos
*************************************************************************************/
	/*
	* Construtor. N�o faz nada.
	* S� existe porque deixar os m�todos est�ticos estava dando erros demais.
	*/
	ia::ia(){
		
	}


/*
* Gerencia o uso do minimax at� que a condi��o de parada seja satisfeita.
* S�o feitas avalia��es em grafos de profundidades crescentes.
* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � CONTINUAR.
* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
* @param cor_pecas_avaliacao_param Cor das pe�as para a qual as avalia��es devem ser feitas.
* @return O melhor estado encontrado para o qual estado_inicial_param pode ir.
*/
tabuleiroTetralath ia::comecar_minimax(tabuleiroTetralath estado_inicial_param, int *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param){
	int MAXIMO_ITERACOES = tabuleiroTetralath::NUMERO_CASAS;
	int nivelMaximoSendoAvaliado = 1;
	int indiceMelhorJogadaEncontrada;
	float valoresJogadasEncontradas[MAXIMO_ITERACOES];

	tabuleiroTetralath* resultado_parcial[MAXIMO_ITERACOES];

	for(int i=0; i<MAXIMO_ITERACOES; i++){
		resultado_parcial[i] = new tabuleiroTetralath();
	}

	while(*deve_parar_param != PARAR){
		valoresJogadasEncontradas[nivelMaximoSendoAvaliado] = minimax(estado_inicial_param, resultado_parcial[nivelMaximoSendoAvaliado],
																	  deve_parar_param, tipo_jogada_param, nivelMaximoSendoAvaliado,
																	  NIVEL_INICIAL, cor_pecas_avaliacao_param);
		nivelMaximoSendoAvaliado++;
	}

	indiceMelhorJogadaEncontrada = procurarMelhor(valoresJogadasEncontradas, nivelMaximoSendoAvaliado, tipo_jogada_param);
	return *(resultado_parcial[indiceMelhorJogadaEncontrada]->clonar());
}

/*
* Gerencia o uso do minimax com poda alfa beta at� que a condi��o de parada seja satisfeita.
* S�o feitas avalia��es em grafos de profundidades crescentes.
* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � CONTINUAR.
* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
* @param cor_pecas_avaliacao_param Cor das pe�as para a qual as avalia��es devem ser feitas.
* @return O melhor estado encontrado para o qual estado_inicial_param pode ir.
*/
 tabuleiroTetralath ia::comecar_minimax_poda_alfa_beta(tabuleiroTetralath estado_inicial_param, int *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param){
	int MAXIMO_ITERACOES = tabuleiroTetralath::NUMERO_CASAS;
	int nivelMaximoSendoAvaliado = 1;
	int indiceMelhorJogadaEncontrada;
	float valoresJogadasEncontradas[MAXIMO_ITERACOES];

	tabuleiroTetralath* resultado_parcial[MAXIMO_ITERACOES];

	for(int i=0; i<MAXIMO_ITERACOES; i++){
		resultado_parcial[i] = new tabuleiroTetralath();
	}

	while(*deve_parar_param != PARAR){
		valoresJogadasEncontradas[nivelMaximoSendoAvaliado] = minimax_poda_alfa_beta(estado_inicial_param, resultado_parcial[nivelMaximoSendoAvaliado],
																					 deve_parar_param, tipo_jogada_param, nivelMaximoSendoAvaliado,
																					 NIVEL_INICIAL, cor_pecas_avaliacao_param);
		nivelMaximoSendoAvaliado++;
	}

	indiceMelhorJogadaEncontrada = procurarMelhor(valoresJogadasEncontradas, nivelMaximoSendoAvaliado, tipo_jogada_param);
	return *(resultado_parcial[indiceMelhorJogadaEncontrada]->clonar());
}



/*************************************************************************************
* ATEN��O: � partir daqui, todos m�todos s�o privados
*************************************************************************************/

/*
* Executa o algoritmo minimax. O caminhamento utilizado � progressivo em profundidade.
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
* @param cor_pecas_avaliacao_param Cor das pe�as para a qual as avalia��es devem ser feitas.
* @return O melhor valor de avalia��o encontrado em toda a sub�rvore do nodo estado_inicial_param.
*/
float ia::minimax(tabuleiroTetralath estado_inicial_param,
									  tabuleiroTetralath* resultado_parcial_param,
									  int *deve_parar_param,
									  int tipo_jogada_param,
									  int nivel_maximo_param,
									  int nivel_atual_param, int cor_pecas_avaliacao_param)
{
	int filhoAtual;
	int valorUtilidadeEstado;
	int tipoJogadaFilho = (tipo_jogada_param == (int) JOGADA_MIN? (int) JOGADA_MAX : (int) JOGADA_MIN);
	int numeroDeFilhos = estado_inicial_param.calcularNumeroMovimentosLegais();
	int indiceMelhorValorEncontradoNaSubarvore;

	bool estado_ehFolha = (numeroDeFilhos == 0);
	bool estado_jahAtingiuNivelMaximo = (nivel_atual_param == nivel_maximo_param);

	tabuleiroTetralath *estadoFilho;
	tabuleiroTetralath *melhorEstadoEncontrado;
	tabuleiroTetralath resultadosParciaisFilhos[numeroDeFilhos+1]; //O primeiro indice v�lido ser� 1.

	float melhorValorEncontradoNaSubarvore;
	float valoresEncontradosNaSubarvore[numeroDeFilhos];

	if(estado_ehFolha or estado_jahAtingiuNivelMaximo){
		resultado_parcial_param->copiarDe(&estado_inicial_param);
		melhorValorEncontradoNaSubarvore = estado_inicial_param.avaliarParaPecasDaCor(cor_pecas_avaliacao_param);
	} else {
		for(int i=0; i<numeroDeFilhos; i++){
			resultadosParciaisFilhos[i] = *(new tabuleiroTetralath());
		}
		filhoAtual = 1;
		estadoFilho = estado_inicial_param.procurarEstadoAtingivelNaPosicao(filhoAtual);
		while(estadoFilho != tabuleiroTetralath::NAO_HA_ESTADO_ATINGIVEL and *deve_parar_param != PARAR){
			valoresEncontradosNaSubarvore[filhoAtual] = minimax(*estadoFilho, &(resultadosParciaisFilhos[filhoAtual]),
																deve_parar_param, tipoJogadaFilho, nivel_maximo_param,
																nivel_atual_param+1, cor_pecas_avaliacao_param);
			filhoAtual++;
			estadoFilho = estado_inicial_param.procurarEstadoAtingivelNaPosicao(filhoAtual);
		}
		//Usa-se filhoAtual-1 ao inv�s de numeroDeFilhos, pois numeroDeFilhos causaria invas�o de mem�ria se deve_parar_param tivesse sido acionado.
		indiceMelhorValorEncontradoNaSubarvore = procurarMelhor(valoresEncontradosNaSubarvore, filhoAtual-1, tipo_jogada_param);
		melhorEstadoEncontrado = &(resultadosParciaisFilhos[indiceMelhorValorEncontradoNaSubarvore]);
		resultado_parcial_param->copiarDe(melhorEstadoEncontrado);
		melhorValorEncontradoNaSubarvore = melhorEstadoEncontrado->avaliarParaPecasDaCor(cor_pecas_avaliacao_param);
	}

	return melhorValorEncontradoNaSubarvore;
}

/*
* Executa o algoritmo minimax com poda alfa beta. O caminhamento utilizado � progressivo em profundidade.
* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
* @param resultado_parcial_param Ponteiro para vari�vel em que ser� colocado o resultado parcial. Este resultado s� tem utilidade
*								 caso corresponda a um objeto diretamente ligado ao objeto que deu in�cio � primeira chamada desta fun��o.* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � continuar.
* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
* @param nivel_maximo_param Especifica quantos niveis (em profundidade) o grafo pode ser expandido.
* @param nivel_atual_param Define a dist�ncia (no grafo expandido) entre estado_inicial_param e o estado que iniciou esta fun��o.
*						   Logicamente, na primeira chamada � fun��o, deve conter 0.
* @param cor_pecas_avaliacao_param Cor das pe�as para a qual as avalia��es devem ser feitas.
* @return O melhor valor de avalia��o encontrado em toda a sub�rvore do nodo estado_inicial_param.
*/
float ia::minimax_poda_alfa_beta(tabuleiroTetralath estado_inicial_param,
													 tabuleiroTetralath* resultado_parcial_param,
													 int *deve_parar_param,
													 int tipo_jogada_param,
													 int nivel_maximo_param,
													 int nivel_atual_param, int cor_pecas_avaliacao_param)
{


}

/*
* Tenta encontrar em um array um valor (obtido com avalia��o dos elementos) condizente com o objetivo par�metro.
* @param array_param Um array em que cada elemento � um float.
* @param tamanho_array_param A quantidade de itens no array (contando � partir do elemento de �ndice 1).
* @param objetivo_param Determina se deve-se procurar pelo elemento que tenha o maior valor (JOGADA_MAX) ou
*						por aquele que tenha o menor valor (JOGADA_MIN).
* @return O �ndice do array que possui o melhor valor.
*/
 int ia::procurarMelhor(float array_param[], int tamanho_array_param, int objetivo_param){
	int indiceMelhorResultadoParcial;
	float valorResultadoParcial;
	float valorMelhorResultadoParcial = tabuleiroTetralath::PERDA;
	for(int i=0; i<tamanho_array_param; i++){
		valorResultadoParcial = array_param[i];
		if(valorMelhorResultadoParcial <= valorResultadoParcial){
			indiceMelhorResultadoParcial = i;
		}
	}
	return indiceMelhorResultadoParcial;
}