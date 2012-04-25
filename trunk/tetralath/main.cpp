/*
Para compilar no windows:
	g++ main.cpp ia.cpp tabuleiroTetralath.cpp casaTabuleiroTetralath.cpp -o main
*/

#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "interface_gui.h"
using namespace std;

/*
* Jogo tetralath com IA.
*/

/**************************************************
* Declara��es de m�todos definidos ap�s main.
*
*/

void inverterCorPecas(int *pecas_param);
void avisarAoFimDeCincoSegundos(bool *variavel_aviso_param);
bool fazerJogadaUsuario(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, int pecasDaVez_param, bool *ehVezDoUsuario_param,
						tabuleiroTetralath* tabuleirosPassados_param[], int *numeroJogadasFeitas_param);


/**************************************************
* Vari�veis globais.
*
*/

interface_gui gui;
int pecasDaVez;

/**************************************************
* Fun��o principal.
*
*/
int main(){
	int CASA_INEXISTENTE = -1;
	int casaCursor = 0;
	int numeroJogadasFeitas = 0;

	char comandoUsuario = COMANDO_SEM_ACAO;
	char movimentoUsuario = COMANDO_SEM_ACAO;

	bool condicaoParadaMinimax = false;
	bool jogoAcabou = false;
	bool ehVezDoUsuario = true;

	ia jogadorArtificial = *(new ia());
	
	gui = *(new interface_gui());
	
	tabuleiroTetralath tabuleiro = *(new tabuleiroTetralath());
	tabuleiroTetralath* tabuleirosPassados[tabuleiroTetralath::NUMERO_CASAS+1];

	pecasDaVez = casaTabuleiroTetralath::PECAS_BRANCAS;
	
	Sleep(500); //Para que n�o saia jogando logo no in�cio.
	
	/*
	* Escolha das pe�as do usu�rio.
	*/
	char opcaoRealcarInterface = COMANDO_ESCOLHER_BRANCAS;
	int pecasEscolhidas = casaTabuleiroTetralath::PECAS_BRANCAS;
	gui.imprimirTelaInicio(opcaoRealcarInterface);
	do{
		Sleep(50); //Movimento n�o muito r�pido, permitindo melhor controle.
		comandoUsuario = gui.esperarComandoUsuario();
		if(comandoUsuario == COMANDO_PERCORRER_ALTERNATIVAS){
			inverterCorPecas(&pecasEscolhidas);
			if(pecasEscolhidas == casaTabuleiroTetralath::PECAS_BRANCAS){
				opcaoRealcarInterface = COMANDO_ESCOLHER_BRANCAS;
			} else {
				opcaoRealcarInterface = COMANDO_ESCOLHER_PRETAS;
			}
		} else if(comandoUsuario == COMANDO_ESCOLHER){
			pecasDaVez = pecasEscolhidas;
		}
		gui.imprimirTelaInicio(opcaoRealcarInterface);
	} while(comandoUsuario != COMANDO_FECHAR and comandoUsuario != COMANDO_ESCOLHER);

	/*
	* In�cio do jogo.
	*/
	while(comandoUsuario != COMANDO_FECHAR){
		Sleep(50); //Movimento n�o muito r�pido, permitindo melhor controle.
		comandoUsuario = gui.esperarComandoUsuario();
		
		if(!jogoAcabou){
			gui.imprimirTelaTabuleiro(casaCursor, pecasDaVez, &tabuleiro);
		}

		if(comandoUsuario != COMANDO_DESFAZER_JOGADA){
			if(comandoUsuario == COMANDO_JOGAR and !jogoAcabou and ehVezDoUsuario){
				jogoAcabou = fazerJogadaUsuario(&tabuleiro, casaCursor, pecasDaVez, &ehVezDoUsuario, tabuleirosPassados, &numeroJogadasFeitas);
			} else if((comandoUsuario == MOVIMENTO_CIMA or comandoUsuario == MOVIMENTO_BAIXO or comandoUsuario == MOVIMENTO_ESQUERDA or comandoUsuario == MOVIMENTO_DIREITA)
					and !jogoAcabou and ehVezDoUsuario){
				movimentoUsuario = comandoUsuario;
				casaCursor = tabuleiro.getIndiceCasaMovimento(movimentoUsuario, casaCursor);
			}
	
			if(!jogoAcabou and !ehVezDoUsuario){
				gui.imprimirTelaTabuleiro(casaCursor, pecasDaVez, &tabuleiro);
				condicaoParadaMinimax = false;
				avisarAoFimDeCincoSegundos(&condicaoParadaMinimax);
				tabuleirosPassados[numeroJogadasFeitas] = new tabuleiroTetralath(tabuleiro);
				tabuleiro = jogadorArtificial.comecar_minimax(tabuleiro, &condicaoParadaMinimax, ia::JOGADA_MAX, casaTabuleiroTetralath::PECAS_PRETAS); //Aten��o! A jogada � feita dentro de comecar_minimax.
				inverterCorPecas(&pecasDaVez);
				numeroJogadasFeitas++;
				ehVezDoUsuario = true;
				gui.imprimirTelaTabuleiro(casaCursor, pecasDaVez, &tabuleiro);
				if(tabuleiro.pecasDaMesmaCorGanharam(tabuleiro.recuperarNomeCasaUltimaJogada())){
					jogoAcabou = true;
					gui.imprimirTelaResultado(tabuleiro.recuperarCorPecasUltimaJogada(), CASA_INEXISTENTE, &tabuleiro);
				} else if(tabuleiro.pecasDaMesmaCorPerderam(tabuleiro.recuperarNomeCasaUltimaJogada())){
					jogoAcabou = true;
					tabuleiro.recuperarCorPecasUltimaJogada() == casaTabuleiroTetralath::PECAS_BRANCAS?
					gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS, CASA_INEXISTENTE, &tabuleiro) : gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_BRANCAS, CASA_INEXISTENTE, &tabuleiro);
				} else if(tabuleiro.houveEmpate()){
					gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS+casaTabuleiroTetralath::PECAS_BRANCAS+5, CASA_INEXISTENTE, &tabuleiro);
				}
			}
		} else {
			if(0 < numeroJogadasFeitas){
				tabuleiro = *(tabuleirosPassados[numeroJogadasFeitas - 1]);
				numeroJogadasFeitas--;
				inverterCorPecas(&pecasDaVez);
			}
		}
	}

	system("cls");
	system("color 0f");

	return 0;
}


/*
* A fun��o executa em tempo muito menor ao pedido para o aviso.
* Ela cria uma espera de 5 segundos e, ao final da espera, coloca TRUE em variavel_aviso_param.
* @param variavel_aviso_param Ponteiro cujo conte�do ser� TRUE ap�s tempo_segundos_param.
*/
unsigned int __stdcall esperar(void *variavel_aviso_param){
	Sleep(5000);
	bool *enderecoVariavelAviso = (bool*) variavel_aviso_param;
	*enderecoVariavelAviso = TRUE;
	return 0;
}
void avisarAoFimDeCincoSegundos(bool *variavel_aviso_param){
	_beginthreadex(0, 0, &esperar, (void *) variavel_aviso_param, 0, 0);
	/*
	pid_t pid;
	pid_t pid_filho = 0;
	pid = fork();
	if(pid == pid_filho){
		Sleep(5000);
		*variavel_aviso_param = true;
		exit(0);
	}
	*/
}
/*
* Passou no teste se os tempos estiverem certos e (x) 1<=x<=6 n�o repetir.
* N�o pode repetir, pois apenas o pai pode sair de avisarAoFimDeCincoSegundos.
* Os filhos devem ser terminados, de modo que n�o seja poss�vel voltarem � main!
*/
/*void testesAvisarAoFimDeCincoSegundos(){
	bool avisoUm = FALSE;
	bool avisoDois = FALSE;
	bool avisoTres = FALSE;
	
	avisarAoFimDeCincoSegundos(&avisoUm);
	printf("(1) avisoUm cont�m %d\n", avisoUm);
	avisarAoFimDeCincoSegundos(&avisoDois);
	printf("(2) avisoDois cont�m %d\n", avisoDois);
	avisarAoFimDeCincoSegundos(&avisoTres);
	printf("(3) avisoTres cont�m %d\n", avisoTres);
	system("pause");
	printf("(4) avisoUm cont�m %d\n", avisoUm);
	printf("(5) avisoDois cont�m %d\n", avisoDois);
	printf("(6) avisoTres cont�m %d\n", avisoTres);
	system("pause");
}*/



/*
* Realiza uma jogada. Mostra a tela do resultado, se o jogo acabar.
* @param tabuleiro_param O tabuleiro no qual a jogada � feita.
* @param casaAtual_param A casa do tabuleiro na qual a jogada � feita.
* @param pecasDaVez_param A cor das pe�as que far�o a jogada. Esta cor � trocada caso a jogada tenha sucesso.
* @param ehVezDoUsuario_param N�o � feita verifica��o desta vari�vel. Ela apenas � setada como false, caso o usu�rio consiga jogar.
* @param tabuleirosPassados_param Array com os tabuleiros que j� foram usados, para poder desfazer jogadas.
* @param numeroJogadasFeitas_param Quantas jogadas est�o no array tabuleirosPassados_param.
* @return bool indicando se o jogo acabou.
*/
bool fazerJogadaUsuario(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, int pecasDaVez_param, bool *ehVezDoUsuario_param,
						tabuleiroTetralath* tabuleirosPassados_param[], int *numeroJogadasFeitas_param){
	bool conseguiuJogar;
	bool jogoAcabou = false;

	int CASA_INEXISTENTE = -1;

	tabuleirosPassados_param[*numeroJogadasFeitas_param] = new tabuleiroTetralath(tabuleiro_param);

	conseguiuJogar = tabuleiro_param->jogar(casaAtual_param, pecasDaVez_param);
	if(conseguiuJogar){
		*numeroJogadasFeitas_param = *numeroJogadasFeitas_param + 1;
		*ehVezDoUsuario_param = false;
		inverterCorPecas(&pecasDaVez);
		if(tabuleiro_param->pecasDaMesmaCorGanharam(tabuleiro_param->recuperarNomeCasaUltimaJogada())){
			jogoAcabou = true;
			gui.imprimirTelaResultado(tabuleiro_param->recuperarCorPecasUltimaJogada(), CASA_INEXISTENTE, tabuleiro_param);
		} else if(tabuleiro_param->pecasDaMesmaCorPerderam(tabuleiro_param->recuperarNomeCasaUltimaJogada())){
			jogoAcabou = true;
			tabuleiro_param->recuperarCorPecasUltimaJogada() == casaTabuleiroTetralath::PECAS_BRANCAS?
				gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS, CASA_INEXISTENTE, tabuleiro_param) : gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_BRANCAS, CASA_INEXISTENTE, tabuleiro_param);
		} else if(tabuleiro_param->houveEmpate()){
			gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS+casaTabuleiroTetralath::PECAS_BRANCAS+5, CASA_INEXISTENTE, tabuleiro_param);
		}
	}

	return jogoAcabou;
}

/*
* Realiza uma jogada da IA. Mostra a tela do resultado, se o jogo acabar.
* @param tabuleiro_param O tabuleiro no qual a jogada � feita.
* @param casaAtual_param A casa do tabuleiro na qual a jogada � feita.
* @param pecasDaVez_param A cor das pe�as que far�o a jogada. Esta cor � trocada caso a jogada tenha sucesso.
* @param ehVezDoUsuario_param N�o � feita verifica��o desta vari�vel. Ela apenas � setada como false, caso o usu�rio consiga jogar.
* @param tabuleirosPassados_param Array com os tabuleiros que j� foram usados, para poder desfazer jogadas.
* @param numeroJogadasFeitas_param Quantas jogadas est�o no array tabuleirosPassados_param.
* @return bool indicando se o jogo acabou.
*/
/*bool fazerJogadaIA(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, int pecasDaVez_param, bool *ehVezDoUsuario_param,
				   tabuleiroTetralath* tabuleirosPassados_param[], int *numeroJogadasFeitas_param){
	gui.imprimirTelaTabuleiro(casaCursor, pecasDaVez, &tabuleiro);
	condicaoParadaMinimax = false;
	avisarAoFimDeCincoSegundos(&condicaoParadaMinimax);
	tabuleirosPassados[numeroJogadasFeitas] = new tabuleiroTetralath(tabuleiro);
	tabuleiro = jogadorArtificial.comecar_minimax(tabuleiro, &condicaoParadaMinimax, ia::JOGADA_MAX, casaTabuleiroTetralath::PECAS_PRETAS); //Aten��o! A jogada � feita dentro de comecar_minimax.
	inverterCorPecas(&pecasDaVez);
	numeroJogadasFeitas++;
	ehVezDoUsuario = true;
	gui.imprimirTelaTabuleiro(casaCursor, pecasDaVez, &tabuleiro);
	if(tabuleiro.pecasDaMesmaCorGanharam(tabuleiro.recuperarNomeCasaUltimaJogada())){
		jogoAcabou = true;
		gui.imprimirTelaResultado(tabuleiro.recuperarCorPecasUltimaJogada(), CASA_INEXISTENTE, &tabuleiro);
	} else if(tabuleiro.pecasDaMesmaCorPerderam(tabuleiro.recuperarNomeCasaUltimaJogada())){
		jogoAcabou = true;
		tabuleiro.recuperarCorPecasUltimaJogada() == casaTabuleiroTetralath::PECAS_BRANCAS?
		gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS, CASA_INEXISTENTE, &tabuleiro) : gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_BRANCAS, CASA_INEXISTENTE, &tabuleiro);
	} else if(tabuleiro.houveEmpate()){
		gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS+casaTabuleiroTetralath::PECAS_BRANCAS+5, CASA_INEXISTENTE, &tabuleiro);
	}
	}*/

/*
* Inverte a cor das pe�as passadas. Se forem brancas, ser�o pretas. Se forem pretas, ser�o brancas.
* @param pecas_param Cor das pe�as a ser invertida.
*/
void inverterCorPecas(int *pecas_param){
	(*pecas_param == casaTabuleiroTetralath::PECAS_BRANCAS) ? 
			*pecas_param = casaTabuleiroTetralath::PECAS_PRETAS : *pecas_param = casaTabuleiroTetralath::PECAS_BRANCAS;
}