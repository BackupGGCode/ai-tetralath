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

int escolhaCorPecasUsuario(void);

void conferirFimDoJogo();
void avisarAoFimDeCincoSegundos(bool *variavel_aviso_param);

bool conferirFimDoJogo(tabuleiroTetralath *tabuleiro_param);
bool fazerJogadaUsuario(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, bool *ehVezDoUsuario_param);


/**************************************************
* Vari�veis globais.
*
*/

interface_gui gui;

/**************************************************
* Fun��o principal.
*
*/
int main(){
	int casaCursor = 0;
	int casaJogadaIA;

	char comandoUsuario = COMANDO_SEM_ACAO;
	char movimentoUsuario = COMANDO_SEM_ACAO;

	bool usuarioEhBrancas = false;
	bool condicaoParadaMinimax = false;
	bool jogoAcabou = false;
	bool ehVezDoUsuario = true;

	ia jogadorArtificial = *(new ia());

	gui = (*new interface_gui());

	tabuleiroTetralath tabuleiro = *(new tabuleiroTetralath(true));

	Sleep(500); //Para que n�o saia jogando logo no in�cio.

	if(escolhaCorPecasUsuario() == casaTabuleiroTetralath::PECAS_BRANCAS){
		ehVezDoUsuario = true;
		usuarioEhBrancas = true;
		gui.imprimirTelaTabuleiro(casaCursor, &tabuleiro);
	} else {
		usuarioEhBrancas = false;
		ehVezDoUsuario = false;
	}

	/*
	* In�cio do jogo.
	*/
	while(comandoUsuario != COMANDO_FECHAR){
		Sleep(50); //Movimento n�o muito r�pido, permitindo melhor controle.

		if(ehVezDoUsuario){
			comandoUsuario = gui.esperarComandoUsuario();
		}

		if(comandoUsuario == COMANDO_JOGAR and !jogoAcabou and ehVezDoUsuario){
			jogoAcabou = fazerJogadaUsuario(&tabuleiro, casaCursor, &ehVezDoUsuario);
		} else if((comandoUsuario == MOVIMENTO_CIMA or comandoUsuario == MOVIMENTO_BAIXO or comandoUsuario == MOVIMENTO_ESQUERDA or comandoUsuario == MOVIMENTO_DIREITA)
					and !jogoAcabou and ehVezDoUsuario){
			movimentoUsuario = comandoUsuario;
			casaCursor = tabuleiro.getIndiceCasaMovimento(movimentoUsuario, casaCursor);
		} else if(comandoUsuario == COMANDO_DESFAZER_JOGADA){
			tabuleiro.desfazerUltimaJogada(); //Desfaz jogada do usu�rio...
			tabuleiro.desfazerUltimaJogada(); //... e da IA.
		}

		if(!jogoAcabou){
			gui.imprimirTelaTabuleiro(casaCursor, &tabuleiro);
		}

		if(!jogoAcabou and !ehVezDoUsuario){
			avisarAoFimDeCincoSegundos(&condicaoParadaMinimax);
			gui.imprimirTelaAguardarJogada();
			if(usuarioEhBrancas){
				casaJogadaIA = jogadorArtificial.comecar_minimax(tabuleiro, &condicaoParadaMinimax, ia::JOGADA_MAX, casaTabuleiroTetralath::PECAS_PRETAS);
			} else {
				casaJogadaIA = jogadorArtificial.comecar_minimax(tabuleiro, &condicaoParadaMinimax, ia::JOGADA_MAX, casaTabuleiroTetralath::PECAS_BRANCAS);
			}
			tabuleiro.jogar(casaJogadaIA);
			ehVezDoUsuario = true;
			jogoAcabou = conferirFimDoJogo(&tabuleiro);
		}

		if(!jogoAcabou){
			gui.imprimirTelaTabuleiro(casaCursor, &tabuleiro);
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
	*variavel_aviso_param = false;
	_beginthreadex(0, 0, &esperar, (void *) variavel_aviso_param, 0, 0);
}

/*
* Realiza uma jogada. Mostra a tela do resultado, se o jogo acabar.
* @param tabuleiro_param O tabuleiro no qual a jogada � feita.
* @param casaAtual_param A casa do tabuleiro na qual a jogada � feita.
* @param ehVezDoUsuario_param N�o � feita verifica��o desta vari�vel. Ela apenas � setada como false, caso o usu�rio consiga jogar.
* @param tabuleirosPassados_param Array com os tabuleiros que j� foram usados, para poder desfazer jogadas.
* @param numeroJogadasFeitas_param Quantas jogadas est�o no array tabuleirosPassados_param.
* @return bool indicando se o jogo acabou.
*/
bool fazerJogadaUsuario(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, bool *ehVezDoUsuario_param){
	bool conseguiuJogar;
	bool jogoAcabou = false;

	int CASA_INEXISTENTE = -1;

	conseguiuJogar = tabuleiro_param->jogar(casaAtual_param);
	if(conseguiuJogar){
		*ehVezDoUsuario_param = false;
		jogoAcabou = conferirFimDoJogo(tabuleiro_param);
	}

	return jogoAcabou;
}

/*
* Gerencia a escolha da cor de pe�as que o usu�rio deseja.
* @return Booleano indicando se o usu�rio deve come�ar (se escolheu as brancas).
*/
int escolhaCorPecasUsuario(void){
	char opcaoRealcarInterface = COMANDO_ESCOLHER_BRANCAS;
	char comandoUsuario;
	bool usuarioEscolheuBrancas = true;
	interface_gui gui = *(new interface_gui());
	gui.imprimirTelaInicio(opcaoRealcarInterface);
	do{
		Sleep(50); //Movimento n�o muito r�pido, permitindo melhor controle.
		comandoUsuario = gui.esperarComandoUsuario();
		if(comandoUsuario == COMANDO_PERCORRER_ALTERNATIVAS){
			if(!usuarioEscolheuBrancas){
				opcaoRealcarInterface = COMANDO_ESCOLHER_BRANCAS;
				usuarioEscolheuBrancas = true;
			} else {
				opcaoRealcarInterface = COMANDO_ESCOLHER_PRETAS;
				usuarioEscolheuBrancas = false;
			}
		}
		gui.imprimirTelaInicio(opcaoRealcarInterface);
	} while(comandoUsuario != COMANDO_FECHAR and comandoUsuario != COMANDO_ESCOLHER);
	return usuarioEscolheuBrancas;
}

/*
* Deve ser chamada ao fim de uma jogada.
* Ir� conferir se o jogo acabou e dir� de quem � a vit�ria.
* Se o jogo acabou, j� imprime a tela de resultado.
* @param tabuleiro_param Tabuleiro do jogo.
* @return Booleano indicando se o jogo acabou.
*/
bool conferirFimDoJogo(tabuleiroTetralath *tabuleiro_param){
	int CASA_INEXISTENTE = -1;
	bool jogoAcabou = false;
	tabuleiro_param->pecasDaMesmaCorGanharam(tabuleiro_param->recuperarNomeCasaUltimaJogada());
	bool brancasGanharam = (tabuleiro_param->pecasDaMesmaCorGanharam(tabuleiro_param->recuperarNomeCasaUltimaJogada())
						   and tabuleiro_param->casaOcupadaPorPecaBranca(tabuleiro_param->recuperarNomeCasaUltimaJogada()))
						   or (tabuleiro_param->pecasDaMesmaCorPerderam(tabuleiro_param->recuperarNomeCasaUltimaJogada()) 
						   and !tabuleiro_param->casaOcupadaPorPecaBranca(tabuleiro_param->recuperarNomeCasaUltimaJogada()));
	bool pretasGanharam = (tabuleiro_param->pecasDaMesmaCorGanharam(tabuleiro_param->recuperarNomeCasaUltimaJogada()) 
						   and !tabuleiro_param->casaOcupadaPorPecaBranca(tabuleiro_param->recuperarNomeCasaUltimaJogada()))
						   or (tabuleiro_param->pecasDaMesmaCorPerderam(tabuleiro_param->recuperarNomeCasaUltimaJogada()) 
						   and tabuleiro_param->casaOcupadaPorPecaBranca(tabuleiro_param->recuperarNomeCasaUltimaJogada()));
	if(brancasGanharam){
		jogoAcabou = true;
		gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_BRANCAS, CASA_INEXISTENTE, tabuleiro_param);
	} else if(pretasGanharam){
		jogoAcabou = true;
		gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS, CASA_INEXISTENTE, tabuleiro_param);
	} else if(tabuleiro_param->houveEmpate()){
		jogoAcabou = true;
		gui.imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS+casaTabuleiroTetralath::PECAS_BRANCAS+5, CASA_INEXISTENTE, tabuleiro_param);
	}
	return jogoAcabou;
}