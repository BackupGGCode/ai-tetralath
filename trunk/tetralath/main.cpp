/*
Para compilar no windows:
	g++ main.cpp ia.cpp tabuleiroTetralath.cpp casaTabuleiroTetralath.cpp -o main
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include "ia.h"
using namespace std;


/*
* Jogo tetralath com IA.
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
#define COMANDO_SEM_ACAO 'o' //Usado para inicializa��o. N�o deve ter a��o atribu�da.


/**************************************************
* Declara��es de m�todos definidos ap�s main.
*
*/

char esperarComandoUsuario(void);
void avisarAoFimDeCincoSegundos(bool *variavel_aviso_param);
void imprimirCoresWindows(void);
void imprimirTelaTabuleiro(int casaAtual_param, int pecasDaVez_param, tabuleiroTetralath *tabuleiro_param);
void imprimirTelaResultado(int cor_pecas_ganhadoras_param, int casaAtual_param, tabuleiroTetralath *tabuleiro_param);
int getIndiceCasaMovimento(int movimento_param, int casa_partida_param);
bool fazerJogada(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, int pecasDaVez_param);

/**************************************************
* Fun��o principal.
*
*/

int pecasDaVez = casaTabuleiroTetralath::PECAS_BRANCAS;
int main(){
	int casaCursor = 0;

	char comandoUsuario = COMANDO_SEM_ACAO;
	char movimentoUsuario = COMANDO_SEM_ACAO;

	bool jogoAcabou = false;

	ia jogadorArtificial = *(new ia());

	tabuleiroTetralath tabuleiro = *(new tabuleiroTetralath());

	Sleep(500); //Para que n�o saia jogando logo no in�cio.

	while(comandoUsuario != COMANDO_FECHAR and comandoUsuario != COMANDO_FECHAR_CAPS){
		Sleep(50); //Movimento n�o muito r�pido, permitindo melhor controle.
		if(!jogoAcabou){
			imprimirTelaTabuleiro(casaCursor, pecasDaVez, &tabuleiro);
			comandoUsuario = esperarComandoUsuario();
		}

		if(comandoUsuario == COMANDO_JOGAR and !jogoAcabou){
			jogoAcabou = fazerJogada(&tabuleiro, casaCursor, pecasDaVez);
		} else if((comandoUsuario == MOVIMENTO_CIMA or comandoUsuario == MOVIMENTO_BAIXO or comandoUsuario == MOVIMENTO_ESQUERDA or comandoUsuario == MOVIMENTO_DIREITA)
				  and !jogoAcabou){
			movimentoUsuario = comandoUsuario;
			casaCursor = getIndiceCasaMovimento(movimentoUsuario, casaCursor);
		}
	}

	system("cls");
	system("color 0f");

	return 0;
}


/*
* A fun��o executa em tempo muito menor ao pedido para o aviso.
* Ela cria uma espera de 5 segundos e, ao final da espera, coloca TRUE em variavel_aviso_param.
* @param variavel_aviso_param Ponteiro cujo conte�do ser� asseguradamente TRUE ap�s tempo_segundos_param.
*/
unsigned int __stdcall esperar(void *variavel_aviso_param){
	Sleep(5000);
	bool *enderecoVariavelAviso = (bool*) variavel_aviso_param;
	*enderecoVariavelAviso = TRUE;
	return 0;
}
void avisarAoFimDeCincoSegundos(bool *variavel_aviso_param){
	_beginthreadex(0, 0, &esperar, (void *) variavel_aviso_param, 0, 0);
}
/*
* Passou no teste se os tempos estiverem certos e (x) 1<=x<=6 n�o repetir.
*/
/*void testeEspera(){
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
* Espera por comando do usu�rio e o retorna, quando for feito.
* @return O comando digitado pelo usu�rio. N�o retorna comandos com CAPS, prefere sempre sua vers�o em lower case.
*/
char esperarComandoUsuario(void){
	char comandoUsuario = COMANDO_SEM_ACAO;

	while(comandoUsuario == COMANDO_SEM_ACAO){
		if(GetAsyncKeyState(VK_LEFT) or GetAsyncKeyState(MOVIMENTO_ESQUERDA) or GetAsyncKeyState(MOVIMENTO_ESQUERDA_CAPS)){
			comandoUsuario = MOVIMENTO_ESQUERDA;
		} else if(GetAsyncKeyState(VK_UP) or GetAsyncKeyState(MOVIMENTO_CIMA) or GetAsyncKeyState(MOVIMENTO_CIMA_CAPS)){
			comandoUsuario = MOVIMENTO_CIMA;
		} else if(GetAsyncKeyState(VK_RIGHT) or GetAsyncKeyState(MOVIMENTO_DIREITA) or GetAsyncKeyState(MOVIMENTO_DIREITA_CAPS)){
			comandoUsuario = MOVIMENTO_DIREITA;
		} else if(GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState(MOVIMENTO_BAIXO) or GetAsyncKeyState(MOVIMENTO_BAIXO_CAPS)){
			comandoUsuario = MOVIMENTO_BAIXO;
		} else if(GetAsyncKeyState(COMANDO_JOGAR) or GetAsyncKeyState(COMANDO_JOGAR_CAPS) or GetAsyncKeyState(COMANDO_JOGAR_ALTERNATIVO)){
			comandoUsuario = COMANDO_JOGAR;
		} else if(GetAsyncKeyState(COMANDO_FECHAR) or GetAsyncKeyState(COMANDO_FECHAR_CAPS)){
			comandoUsuario = COMANDO_FECHAR;
		}
	}

	return comandoUsuario;
}

/*
* Realiza uma jogada. Mostra a tela do resultado, se o jogo acabar.
* @param tabuleiro_param O tabuleiro no qual a jogada � feita.
* @param casaAtual_param A casa do tabuleiro na qual a jogada � feita.
* @param pecasDaVez_param A cor das pe�as que far�o a jogada. Esta cor � trocada caso a jogada tenha sucesso.
* @return bool indicando se o jogo acabou.
*/
bool fazerJogada(tabuleiroTetralath *tabuleiro_param, int casaAtual_param, int pecasDaVez_param){
	bool conseguiuJogar;
	bool jogoAcabou = false;

	int CASA_INEXISTENTE = -1;

	conseguiuJogar = tabuleiro_param->jogar(casaAtual_param, pecasDaVez_param);
	if(conseguiuJogar){
		(pecasDaVez_param == casaTabuleiroTetralath::PECAS_BRANCAS) ? 
			pecasDaVez = casaTabuleiroTetralath::PECAS_PRETAS : pecasDaVez = casaTabuleiroTetralath::PECAS_BRANCAS;
		if(tabuleiro_param->pecasDaMesmaCorGanharam(tabuleiro_param->recuperarNomeCasaUltimaJogada())){
			jogoAcabou = true;
			imprimirTelaResultado(tabuleiro_param->recuperarCorPecasUltimaJogada(), CASA_INEXISTENTE, tabuleiro_param);
		} else if(tabuleiro_param->pecasDaMesmaCorPerderam(tabuleiro_param->recuperarNomeCasaUltimaJogada())){
			jogoAcabou = true;
			tabuleiro_param->recuperarCorPecasUltimaJogada() == casaTabuleiroTetralath::PECAS_BRANCAS?
				imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS, CASA_INEXISTENTE, tabuleiro_param) : imprimirTelaResultado(casaTabuleiroTetralath::PECAS_BRANCAS, CASA_INEXISTENTE, tabuleiro_param);
		} else if(tabuleiro_param->houveEmpate()){
			imprimirTelaResultado(casaTabuleiroTetralath::PECAS_PRETAS+casaTabuleiroTetralath::PECAS_BRANCAS+5, CASA_INEXISTENTE, tabuleiro_param);
		}
	}

	return jogoAcabou;
}

/*
* Dado um movimento e um �ndice de casa, decide para qual �ndice de casa o cursor do tabuleiro deve ser movido.
* @param movimento_param Caractere que decide o �ndice.
* @param casa_partida_param Casa da qual deseja-se obter o vizinho.
* @return �ndice a ser passado para imprimir. Se n�o houver vizinho para o movimento, retorna a casa passada como argumento.
*/
int getIndiceCasaMovimento(int movimento_param, int casa_partida_param){
	int casa_destino = casa_partida_param;
	if(movimento_param == MOVIMENTO_CIMA or movimento_param == MOVIMENTO_CIMA_CAPS){ //Movimenta para o vizinho A, se existir.
		if(casa_partida_param == 0 or casa_partida_param == 1 or casa_partida_param == 2 or casa_partida_param == 3 or casa_partida_param == 4 or
		   casa_partida_param == 5 or casa_partida_param == 11 or casa_partida_param == 18 or casa_partida_param == 26){
			casa_destino = casa_partida_param;
		} else if(casa_partida_param <= 10){
			casa_destino = casa_partida_param - 6;
		} else if(casa_partida_param <= 17){
			casa_destino = casa_partida_param - 7;
		} else if(casa_partida_param <= 25){
			casa_destino = casa_partida_param - 8;
		} else if(casa_partida_param <= 34){
			casa_destino = casa_partida_param - 9;
		} else if(casa_partida_param <= 42){
			casa_destino = casa_partida_param - 9;
		} else if(casa_partida_param <= 49){
			casa_destino = casa_partida_param - 8;
		} else if(casa_partida_param <= 55){
			casa_destino = casa_partida_param - 7;
		} else if(casa_partida_param <= 60){
			casa_destino = casa_partida_param - 6;
		}
	} else if(movimento_param == MOVIMENTO_BAIXO or movimento_param == MOVIMENTO_BAIXO_CAPS){ //Movimenta para o vizinho F, se existir.
		if(casa_partida_param == 56 or casa_partida_param == 57 or casa_partida_param == 58 or casa_partida_param == 59 or casa_partida_param == 60 or
		   casa_partida_param == 34 or casa_partida_param == 42 or casa_partida_param == 49 or casa_partida_param == 55){
			casa_destino = casa_partida_param;
		} else if(casa_partida_param <= 4){
			casa_destino = casa_partida_param + 6;
		} else if(casa_partida_param <= 10){
			casa_destino = casa_partida_param + 7;
		} else if(casa_partida_param <= 17){
			casa_destino = casa_partida_param + 8;
		} else if(casa_partida_param <= 25){
			casa_destino = casa_partida_param + 9;
		} else if(casa_partida_param <= 34){
			casa_destino = casa_partida_param + 9;
		} else if(casa_partida_param <= 42){
			casa_destino = casa_partida_param + 8;
		} else if(casa_partida_param <= 49){
			casa_destino = casa_partida_param + 7;
		} else if(casa_partida_param <= 55){
			casa_destino = casa_partida_param + 6;
		}
	} else if(movimento_param == MOVIMENTO_ESQUERDA or movimento_param == MOVIMENTO_ESQUERDA_CAPS){ //Movimenta para o vizinho C, se existir.
		if(casa_partida_param == 0 or casa_partida_param == 5 or casa_partida_param == 11 or casa_partida_param == 18 or casa_partida_param == 26 or
		   casa_partida_param == 35 or casa_partida_param == 43 or casa_partida_param == 50 or casa_partida_param == 56){
			casa_destino = casa_partida_param;
		} else {
			casa_destino = casa_partida_param - 1;
		}
	} else if(movimento_param == MOVIMENTO_DIREITA or movimento_param == MOVIMENTO_DIREITA_CAPS){ //Movimenta para o vizinho D, se existir.
		if(casa_partida_param == 4 or casa_partida_param == 10 or casa_partida_param == 17 or casa_partida_param == 25 or casa_partida_param == 34 or
		   casa_partida_param == 42 or casa_partida_param == 49 or casa_partida_param == 55 or casa_partida_param == 60){
			casa_destino = casa_partida_param;
		} else {
			casa_destino = casa_partida_param + 1;
		}
	} else {
		casa_destino = casa_partida_param;
	}
	return casa_destino;
}

/*
* Imprime a tela do jogo.
* @param casaAtual_param A casa em que est� o cursor.
* @param pecasDaVez_param A cor das pe�as que est�o jogando.
* @param tabuleiro_param O tabuleiro que ser� impresso.
*/
void imprimirTelaTabuleiro(int casaAtual_param, int pecasDaVez_param, tabuleiroTetralath *tabuleiro_param){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
	system("cls");
	printf("\t\t\t\t TEXTLATH\n\n");
	printf("\t\t\t O tetralath em modo texto!\n");

	if(pecasDaVez_param == casaTabuleiroTetralath::PECAS_BRANCAS){
		printf("\n\n\t\t\tEh a vez das pecas BRANCAS");
	} else {
		printf("\n\n\t\t\tEh a vez das pecas PRETAS");
	}

	printf("\n\n\n\n");
	tabuleiro_param->imprimir(casaAtual_param);
	printf("\n\n\n\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
	printf("[W] ou [SETA CIMA] MOVER PARA CASA NA DIAGONAL ESQUERDA SUPERIOR (CIMA)\n");
	printf("[S] ou [SETA BAIXO] MOVER PARA CASA NA DIAGONAL DIREITA INFEROR (BAIXO)\n");
	printf("[A] ou [SETA ESQUERDA] MOVER PARA CASA A ESQUERDA\n");
	printf("[D] ou [SETA DIREITA] MOVER PARA CASA A DIREITA\n");
	printf("[J] ou [BARRA ESPACO] JOGAR\n");
	printf("[Q] SAIR\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
}

/*
* Imprime a tela do resultado de um jogo.
* @param cor_pecas_ganhadoras_param A cor das pe�as que ganharam o jogo. Qualquer valor diferente de PECAS_PRETAS e PECAS_BRANCAS � empate.
* @param casaAtual_param A casa em que est� o cursor.
* @param tabuleiro_param O tabuleiro que ser� impresso.
*/
void imprimirTelaResultado(int cor_pecas_ganhadoras_param, int casaAtual_param, tabuleiroTetralath *tabuleiro_param){
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("\t\t\t\t TEXTLATH\n\n");
	printf("\t\t\t O tetralath em modo texto!\n");

	printf("\n\n\t\t\t\tFim do jogo!");

	printf("\n\n\n\n");
	tabuleiro_param->imprimir(casaAtual_param);
	printf("\n\n\n\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
	if(cor_pecas_ganhadoras_param == casaTabuleiroTetralath::PECAS_BRANCAS){
		printf("\t\t\tAs pecas BRANCAS ganharam!");
	} else if(cor_pecas_ganhadoras_param == casaTabuleiroTetralath::PECAS_PRETAS){
		printf("\t\t\tAs pecas PRETAS ganharam!");
	} else {
		printf("\t\t\t   Houve empate!");
	}
	printf("\n\n\n\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
	printf("[Q] SAIR\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
}


/*
* Imprime todas as cores poss�veis no prompt no windows (S� funciona no windows!!!!!!).
*/
void imprimirCoresWindows(void){
	system("cls");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	printf("FOREGROUND_RED\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	printf("FOREGROUND_BLUE\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	printf("FOREGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
	printf("FOREGROUND_RED | FOREGROUND_BLUE\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
	printf("FOREGROUND_RED | FOREGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("FOREGROUND_BLUE | FOREGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("FOREGROUND_RED | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("FOREGROUND_BLUE | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("FOREGROUND_GREEN | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED);
	printf("BACKGROUND_RED\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
	printf("BACKGROUND_BLUE\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN);
	printf("BACKGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE);
	printf("BACKGROUND_RED | BACKGROUND_BLUE\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN);
	printf("BACKGROUND_RED | BACKGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN);
	printf("BACKGROUND_BLUE | BACKGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
	printf("BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_INTENSITY);
	printf("BACKGROUND_RED | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	printf("BACKGROUND_BLUE | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("BACKGROUND_GREEN | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	printf("BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}