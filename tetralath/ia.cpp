#include "ia.h"

/*************************************************************************************
* ATEN��O: � partir daqui, todos m�todos s�o p�blicos
*************************************************************************************/
/*
* Construtor base... Faz nada!
*/
ia::ia(void){}

/*
* Construtor. 
* @param _algoritmo O algoritmo que deve ser utilizado por esta ia. Definido nesta classe.
*/
ia::ia(int _algoritmo){
	algoritmo = _algoritmo;
}

/*
* Construtor de c�pia.
* @param _ia ia a ser copiada.
*/
ia::ia(ia *_ia){
	algoritmo = _ia->algoritmo;
}

/*
* Gerencia o uso do algoritmo escolhido at� que a condi��o de parada seja satisfeita.
* S�o feitas avalia��es em grafos de profundidades crescentes.
* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � continuar.
* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
* @return O nome da casa em que deve ser feita a jogada.
*/
int ia::comecar_avaliacao(tabuleiroTetralath estado_inicial_param, bool *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param){
	int casaResultado = 0;
	switch(algoritmo){
		case ia::MINIMAX: casaResultado = comecar_minimax(estado_inicial_param, deve_parar_param, tipo_jogada_param, cor_pecas_avaliacao_param);
			break;
		case ia::MINIMAX_PODA: casaResultado = comecar_minimax_poda_alfa_beta(estado_inicial_param, deve_parar_param, tipo_jogada_param, cor_pecas_avaliacao_param);
			break;
	}
	return casaResultado;
}



/*************************************************************************************
* ATEN��O: � partir daqui, todos m�todos s�o privados
*************************************************************************************/

/*
* Gerencia o uso do minimax at� que a condi��o de parada seja satisfeita.
* S�o feitas avalia��es em grafos de profundidades crescentes.
* @param estado_inicial_param Estado � partir do qual o grafo ser� expandido.
* @param deve_parar_param Ponteiro para vari�vel que indica se o minimax deve terminar sua execu��o e retornar o resultado parcial.
*		 Esta vari�vel � constantemente checada para verificar se � necess�rio parar. Seus poss�veis valores s�o CONTINUAR e PARAR,
*		 definidos nesta classe. Caso o valor n�o seja nenhum destes, o default assumido � CONTINUAR.
* @param tipo_jogada_param O tipo de jogada (JOGADA_MAX ou JOGADA_MIN) que deve ser aplicado aos valores dos filhos de estado_inicial_param.
* @param cor_pecas_avaliacao_param Cor das pe�as para a qual as avalia��es devem ser feitas.
* @return O nome da casa em que deve ser feita a jogada.
*/
int ia::comecar_minimax(tabuleiroTetralath estado_inicial_param, bool *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param){
	int MAXIMO_ITERACOES = estado_inicial_param.numeroDeCasasLivres();
	int nivelMaximoSendoAvaliado = 1;
	int casaMelhorJogada = 0;
	float resultado_melhor_aplicacao_minimax = tabuleiroTetralath::PERDA;
	float resultado_aplicacao_minimax = tabuleiroTetralath::PERDA;

	tabuleiro = *(new tabuleiroTetralath(&estado_inicial_param, true));

	while(*deve_parar_param != PARAR and nivelMaximoSendoAvaliado <= MAXIMO_ITERACOES){
		resultado_aplicacao_minimax = minimax(deve_parar_param, tipo_jogada_param, nivelMaximoSendoAvaliado, NIVEL_INICIAL, cor_pecas_avaliacao_param);
		if(!(*deve_parar_param) && resultado_melhor_aplicacao_minimax <= resultado_aplicacao_minimax){
			resultado_melhor_aplicacao_minimax = resultado_aplicacao_minimax;
			casaMelhorJogada = resultado_minimax;
			nivelMaximoSendoAvaliado++;
		}
	}
	return casaMelhorJogada;
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
 int ia::comecar_minimax_poda_alfa_beta(tabuleiroTetralath estado_inicial_param, bool *deve_parar_param, int tipo_jogada_param, int cor_pecas_avaliacao_param){
	int MAXIMO_ITERACOES = estado_inicial_param.numeroDeCasasLivres();
	int nivelMaximoSendoAvaliado = 1;
	int casaMelhorJogada = 0;
	float resultado_melhor_aplicacao_minimax = tabuleiroTetralath::PERDA;
	float resultado_aplicacao_minimax = tabuleiroTetralath::PERDA;

	tabuleiro = *(new tabuleiroTetralath(&estado_inicial_param, true));

	while(*deve_parar_param != PARAR and nivelMaximoSendoAvaliado <= MAXIMO_ITERACOES){
		resultado_aplicacao_minimax = minimax_poda_alfa_beta(deve_parar_param, tipo_jogada_param, nivelMaximoSendoAvaliado, NIVEL_INICIAL, cor_pecas_avaliacao_param);
		if(!(*deve_parar_param) && resultado_melhor_aplicacao_minimax <= resultado_aplicacao_minimax){
			resultado_melhor_aplicacao_minimax = resultado_aplicacao_minimax;
			casaMelhorJogada = resultado_minimax;
			nivelMaximoSendoAvaliado++;
		}
	}
	return casaMelhorJogada;
}

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
float ia::minimax(bool *deve_parar_param, int tipo_jogada_param, int nivel_maximo_param, int nivel_atual_param, int cor_pecas_avaliacao_param){
	int jogadaAtual;
	int valorJogada;
	int tipoJogadaFilho = (tipo_jogada_param == (int) JOGADA_MIN? (int) JOGADA_MAX : (int) JOGADA_MIN);
	int casaMelhorJogada;

	bool valor_deveSerMaximizado = (tipo_jogada_param == JOGADA_MAX);
	bool estado_ehFolha = (tabuleiro.calcularNumeroMovimentosLegais() == 0);
	bool estado_jahAtingiuNivelMaximo = (nivel_atual_param == nivel_maximo_param);

	float valorMelhorJogada;

	if(estado_ehFolha or estado_jahAtingiuNivelMaximo){
		valorMelhorJogada = tabuleiro.avaliarParaPecasDaCor(cor_pecas_avaliacao_param);
	} else {
		if(nivel_atual_param == NIVEL_INICIAL){ //Necess�rio saber qual a casa de melhor jogada.
			casaMelhorJogada = 0;
			jogadaAtual=0;
			if(valor_deveSerMaximizado){
				valorMelhorJogada = tabuleiroTetralath::PERDA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorMelhorJogada <= valorJogada){
							casaMelhorJogada = jogadaAtual;
							valorMelhorJogada = valorJogada;
						}
					}
					jogadaAtual++;
				}
			} else {
				valorMelhorJogada = tabuleiroTetralath::VITORIA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorJogada <= valorMelhorJogada){
							casaMelhorJogada = jogadaAtual;
							valorMelhorJogada = valorJogada;
						}
					}
					jogadaAtual++;
				}
			}
			resultado_minimax = casaMelhorJogada;
		} else { //N�o � necess�rio saber a casa de melhor jogada, s� seu valor.
			jogadaAtual=0;
			if(valor_deveSerMaximizado){
				valorMelhorJogada = tabuleiroTetralath::PERDA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorMelhorJogada <= valorJogada){
							valorMelhorJogada = valorJogada;
						}
					}
					jogadaAtual++;
				}
			} else {
				valorMelhorJogada = tabuleiroTetralath::VITORIA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorJogada <= valorMelhorJogada){
							valorMelhorJogada = valorJogada;
						}
					}
					jogadaAtual++;
				}
			}
		}
	}

	return valorMelhorJogada;
}

/*
* Executa o algoritmo minimax com poda alfa beta. O caminhamento utilizado � progressivo em profundidade.
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
float ia::minimax_poda_alfa_beta(bool *deve_parar_param, int tipo_jogada_param, int nivel_maximo_param, int nivel_atual_param, int cor_pecas_avaliacao_param){
	int jogadaAtual;
	int valorJogada;
	int tipoJogadaFilho = (tipo_jogada_param == (int) JOGADA_MIN? (int) JOGADA_MAX : (int) JOGADA_MIN);
	int casaMelhorJogada;

	bool valor_deveSerMaximizado = (tipo_jogada_param == JOGADA_MAX);
	bool estado_ehFolha = (tabuleiro.calcularNumeroMovimentosLegais() == 0);
	bool estado_jahAtingiuNivelMaximo = (nivel_atual_param == nivel_maximo_param);
	bool realizarPoda = false;

	float valorMelhorJogada;

	if(estado_ehFolha or estado_jahAtingiuNivelMaximo){
		valorMelhorJogada = tabuleiro.avaliarParaPecasDaCor(cor_pecas_avaliacao_param);
	} else {
		if(nivel_atual_param == NIVEL_INICIAL){ //Necess�rio saber qual a casa de melhor jogada.
			casaMelhorJogada = 0;
			jogadaAtual=0;
			if(valor_deveSerMaximizado){
				valorMelhorJogada = tabuleiroTetralath::PERDA;
				
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS and !realizarPoda){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax_poda_alfa_beta(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorMelhorJogada <= valorJogada){
							casaMelhorJogada = jogadaAtual;
							valorMelhorJogada = valorJogada;
							realizarPoda = (valorMelhorJogada == tabuleiroTetralath::VITORIA);
						}
					}
					jogadaAtual++;
				}
			} else {
				valorMelhorJogada = tabuleiroTetralath::VITORIA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS and !realizarPoda){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax_poda_alfa_beta(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorJogada <= valorMelhorJogada){
							casaMelhorJogada = jogadaAtual;
							valorMelhorJogada = valorJogada;
							realizarPoda = (valorMelhorJogada == tabuleiroTetralath::PERDA);
						}
					}
					jogadaAtual++;
				}
			}
			resultado_minimax = casaMelhorJogada;
		} else { //N�o � necess�rio saber a casa de melhor jogada, s� seu valor.
			jogadaAtual=0;
			if(valor_deveSerMaximizado){
				valorMelhorJogada = tabuleiroTetralath::PERDA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS and !realizarPoda){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax_poda_alfa_beta(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorMelhorJogada <= valorJogada){
							valorMelhorJogada = valorJogada;
							realizarPoda = (valorMelhorJogada == tabuleiroTetralath::VITORIA);
						}
					}
					jogadaAtual++;
				}
			} else {
				valorMelhorJogada = tabuleiroTetralath::VITORIA;
				while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS and !realizarPoda){
					if(tabuleiro.jogar(jogadaAtual)){
						valorJogada = minimax_poda_alfa_beta(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
						tabuleiro.desfazerUltimaJogada();
						if(valorJogada <= valorMelhorJogada){
							valorMelhorJogada = valorJogada;
							realizarPoda = (valorMelhorJogada == tabuleiroTetralath::PERDA);
						}
					}
					jogadaAtual++;
				}
			}
		}
	}

	return valorMelhorJogada;
}
