#include "abertura.h"
#include "tabuleiroTetralath.h"
#include <stdio.h>
#include <stdlib.h>

/*
* Defini��es de aberturas.
*/
int abertura::DUPLA[] = {26, 27, 30, 32, 29};
int abertura::TRIANGULO_AGRESSIVO[] = {23, 39, 46, 47, 49, 42, 41};
int abertura::DUPLA_FILEIRA_AGRESSIVA[] = {22, 23, 39, 46, 47, 53, 32, 49};


/*************************************************************
* � partir daqui, todos os m�todos s�o P�BLICOS
**************************************************************/

/*
* Cria nova abertura.
* @param _tipo Diz o tipo, um dentre os definidos nesta classe.
*/
abertura::abertura(int _tipo){
	tipo = _tipo;
	indiceUltimaJogada = 0;
	switch(tipo){
		case ABERTURA_DUPLA: casas.assign(DUPLA, DUPLA+5);
			break;
		case ABERTURA_TRIANGULO_AGRESSIVO: casas.assign(TRIANGULO_AGRESSIVO, TRIANGULO_AGRESSIVO+7);
			break;
		case ABERTURA_DUPLA_FILEIRA_AGRESSIVA: casas.assign(DUPLA_FILEIRA_AGRESSIVA, DUPLA_FILEIRA_AGRESSIVA+8);
			break;
	}
}

/*
* @return nome da pr�xima casa em que se deve jogar. Caso o limite j� tenha sido excedido, retorna CASA_INEXISTENTE.
* ATEN��O: cada chamada a esta fun��o � considerada uma jogada. Assim, chamadas sucessivas retornam
* casas em posi��es cont�guas, nunca retornam a mesma.
*/
int abertura::getNomeProximaJogada(){
	if(casas.size() == indiceUltimaJogada){
		return CASA_INEXISTENTE;
	} else {
		return casas.at(indiceUltimaJogada);
	}
}

/*
* Incrementa o contador da jogada atual.
*/
void abertura::jogar(){
	indiceUltimaJogada++;
}

/*
* @param _tabuleiro Tabuleiro em que o teste ser� feito.
* @return Booleano indicando se � poss�vel utilizar esta abertura no tabuleiro dado, se as casas
*					que ela necessita est�o livres.
* Obs.: O teste considera a pr�xima jogada a ser feita desta abertura.
* Obs2.: Esta fun��o considera somente as casas do vetor casas, n�o considerada transla��es e rota��es.
*/
bool abertura::aplicavelAoTabuleiro(tabuleiroTetralath *_tabuleiro){
	bool aplicavel = true;

	if(casas.size() == indiceUltimaJogada){
		aplicavel = false;
	}
	for(int numeroCasa=indiceUltimaJogada; numeroCasa<casas.size(); numeroCasa++){
		if(_tabuleiro->casaOcupada(casas.at(numeroCasa))){
			aplicavel = false;
		}
	}

	return aplicavel;
}


/*************************************************************
* � partir daqui, todos os m�todos s�o PRIVADOS
**************************************************************/