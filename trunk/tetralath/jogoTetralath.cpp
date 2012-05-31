#include <iostream>

#include "jogoTetralath.h"

using namespace std;

/*
* Cria um novo jogo, com base no seu tipo, e o retorna.
* @param _tipoJogo Define o tipo de jogo, se entre dois humanos, humano e pc ou pc contra pc.
* @param _jogadorUm O jogador que far� a primeira jogada.
* @param _jogadorDois O jogador que far� a segunda jogada.
*/
jogoTetralath::jogoTetralath(jogadorTetralath *_jogadorUm, jogadorTetralath *_jogadorDois){
	jogadorUm = _jogadorUm;
	jogadorDois = _jogadorDois;
}

/*
* Inicia o jogo. Esta fun��o s� retornar� quando o jogo estiver terminado.
* @param _interfaceUsuario A interface_gui usada para comunica��o com o usu�rio.
* @return O jogador que ganhou o jogo.
*/
jogadorTetralath* jogoTetralath::iniciarJogo(interface_gui _interfaceUsuario){
	interfaceUsuario = _interfaceUsuario;
	return jogadorUm;
}