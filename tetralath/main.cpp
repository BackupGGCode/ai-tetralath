
#include "jogoTetralath.h"
#include "jogadorMaquina.h"
#include "jogadorHumano.h"
#include <stdlib.h>

using namespace std;

/*
* Jogo tetralath com IA.
*/

/**************************************************
* Declara��es de m�todos definidos ap�s main.
*
*/


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
	/*int c;
	for(c=0; c<256; c++){
		printf("%d=%c\n",c,c);
	}
	system("pause");*/

	gui = (*new interface_gui());

	jogadorTetralath *jogadorUm; 
	jogadorTetralath *jogadorDois;

	menu menuInicioJogo;

	vector<string> opcoesJogadores;
	vector<string> nomesColunas;

	opcoesJogadores.push_back("HUMANO");
	opcoesJogadores.push_back("MAQUINA");

	menuInicioJogo.criarNovaOpcao(opcoesJogadores);
	menuInicioJogo.criarNovaOpcao(opcoesJogadores);

	nomesColunas.push_back("Jogador 1");
	nomesColunas.push_back("Jogador 2");
	menuInicioJogo.nomearColunas(nomesColunas);

	gui.imprimirTelaMenus(&menuInicioJogo);

	vector<vector<string> > opcoesEscolhidas = menuInicioJogo.getAlternativasSelecionadas();
	bool escolheu_opcoesValidas = false;

	jogadorUm = (opcoesEscolhidas.at(0).at(0) == "HUMANO"? 
					(jogadorTetralath*) (new jogadorHumano(&gui, casaTabuleiroTetralath::PECAS_BRANCAS)) : 
					(jogadorTetralath*) (new jogadorMaquina(*(new ia(ia::MINIMAX)), casaTabuleiroTetralath::PECAS_BRANCAS)));

	jogadorDois = (opcoesEscolhidas.at(0).at(1) == "HUMANO"? 
						(jogadorTetralath*) (new jogadorHumano(&gui, casaTabuleiroTetralath::PECAS_PRETAS)) : 
						(jogadorTetralath*) (new jogadorMaquina(*(new ia(ia::MINIMAX)), casaTabuleiroTetralath::PECAS_PRETAS)));

	jogoTetralath jogo = *(new jogoTetralath(*(new tabuleiroTetralath(true)), jogadorUm, jogadorDois));
	jogo.iniciarJogo(&gui);

	system("color 0f");

	return 0;
}
