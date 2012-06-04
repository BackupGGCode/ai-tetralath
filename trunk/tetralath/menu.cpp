#include "menu.h"
#include <windows.h>
#include <stdio.h>

/*
* Cria um novo menu, sem op��es ainda.
*/
menu::menu(){
	linhaOpcaoSelecionada = 0;
	colunaOpcaoSelecionada = 0;
	criarNovaLinha();
}

/*
* Cria uma nova op��o no menu, com as alternativas de argumento.
* @param _alternativas Vector de strings em que cada elemento � uma alternativa da nova op��o.
*						A nova op��o � sempre inserida na linha corrente.
*/
void menu::criarNovaOpcao(vector<string> _alternativas){
	int linha = linhas.size() - 1;

	linhas.at(linha).push_back(_alternativas);
	alternativasSelecionadas.at(linha).push_back(0);
}

/*
* Cria uma nova linha. Depois desta chamada e at� a pr�xima chamada todas novas op��es s�o inseridas nesta linha.
*/
void menu::criarNovaLinha(){
	vector<vector<string> > linha;
	vector<int> alternativas;
	linhas.push_back(linha);
	alternativasSelecionadas.push_back(alternativas);
}

/*
* Seleciona a op��o seguinte � selecionada, na ordem em que foram inseridas no menu.
* A sele��o � circular.
* A op��o selecionada � aquela em cujas alternativas pode-se navegar.
*/
void menu::selecionarOpcaoSeguinte(){
	int totalLinhas = linhas.size();
	int totalOpcoesLinha = linhas.at(linhaOpcaoSelecionada).size();

	if(totalOpcoesLinha-1 <= colunaOpcaoSelecionada){
		if(totalLinhas-1 <= linhaOpcaoSelecionada){
			colunaOpcaoSelecionada = 0;
			linhaOpcaoSelecionada = 0;
		} else {
			colunaOpcaoSelecionada = 0;
			linhaOpcaoSelecionada++;
		}
	} else {
		colunaOpcaoSelecionada++;
	}
}

/*
* Seleciona a op��o anterior � selecionada, na ordem em que foram inseridas no menu.
* A sele��o � circular.
* A op��o selecionada � aquela em cujas alternativas pode-se navegar.
*/
void menu::selecionarOpcaoAnterior(){
	int totalLinhas = linhas.size();
	int totalOpcoesLinha = linhas.at(linhaOpcaoSelecionada).size();

	if(colunaOpcaoSelecionada <= 0){
		if(linhaOpcaoSelecionada <= 0){
			linhaOpcaoSelecionada = totalLinhas-1;
			colunaOpcaoSelecionada = totalOpcoesLinha-1;
		} else {
			linhaOpcaoSelecionada--;
			colunaOpcaoSelecionada = totalOpcoesLinha-1;
		}
	} else {
		colunaOpcaoSelecionada--;
	}
	
}

/*
* Seleciona a alternativa seguinte � selecionada, na op��o que estiver selecionada.
* A sele��o � circular.
*/
void menu::selecionarAlternativaSeguinte(){
	int numeroAlternativasOpcaoSelecionada = getNumeroAlternativasOpcaoSelecionada();
	int indiceAlternativaSelecionada = getIndiceAlternativaSelecionada();

	if(numeroAlternativasOpcaoSelecionada-1 <= indiceAlternativaSelecionada){
		setIndiceAlternativaSelecionadaOpcaoSelecionada(0);
	} else {
		setIndiceAlternativaSelecionadaOpcaoSelecionada(indiceAlternativaSelecionada+1);
	}
}

/*
* Seleciona a alternativa anterior � selecionada, na op��o que estiver selecionada.
* A sele��o � circular.
*/
void menu::selecionarAlternativaAnterior(){
	int numeroAlternativasOpcaoSelecionada = getNumeroAlternativasOpcaoSelecionada();
	int indiceAlternativaSelecionada = getIndiceAlternativaSelecionada();

	if(indiceAlternativaSelecionada <= 0){
		setIndiceAlternativaSelecionadaOpcaoSelecionada(numeroAlternativasOpcaoSelecionada-1);
	} else {
		setIndiceAlternativaSelecionadaOpcaoSelecionada(indiceAlternativaSelecionada-1);
	}
}

/*
* @return Um vector de vectors de strings. Cada vector de vectors representa uma linha do menu e cada string que ele cont�m
*		  � uma op��o selecionada.
*/
vector<vector<string> > menu::getAlternativasSelecionadas(){
	vector<vector<string> > alternativas;
	vector<string> alternativasLinha;

	int linha;
	int coluna;
	for(linha=0; linha<linhas.size(); linha++){
		vector<string> alternativasLinha;
		for(coluna=0; coluna<linhas.at(linha).size(); coluna++){
			alternativasLinha.push_back(getNomeAlternativaSelecionadaOpcaoEm(linha, coluna));
		}
		alternativas.push_back(alternativasLinha);
	}
}

void imprimirEspacos(int _quantidadeEspacos){
	printf(" |");
	for(int espacosImpressos=0; espacosImpressos<_quantidadeEspacos; espacosImpressos++){
		printf(" ");
	}
	
}

/*
* Imprime este menu na tela, evidenciando a op��o escolhida e suas alternativas.
*/
void menu::imprimir(){
	int ESPACOS_CELULA = 20;
	int linha;
	int coluna;
	printf("\n\t\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
	for(int nomeColuna=0; nomeColuna<nomesColunas.size(); nomeColuna++){
		printf("%s",nomesColunas.at(nomeColuna).c_str());
		imprimirEspacos(ESPACOS_CELULA - nomesColunas.at(nomeColuna).size());
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
	printf("\n\t\t\t");
	for(linha=0; linha<linhas.size(); linha++){
		if(linha == linhaOpcaoSelecionada){
			for(int colunaAtual=0; colunaAtual<colunaOpcaoSelecionada; colunaAtual++){ imprimirEspacos(ESPACOS_CELULA); }
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
			selecionarAlternativaSeguinte();
			printf(" %s", getNomeAlternativaSelecionadaOpcaoEm(linhaOpcaoSelecionada, colunaOpcaoSelecionada).c_str());
			selecionarAlternativaAnterior();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
		}
		printf("\n\t\t\t");
		for(coluna=0; coluna<linhas.at(linha).size(); coluna++){
			if(linha == linhaOpcaoSelecionada && coluna == colunaOpcaoSelecionada){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
				printf("[");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | FOREGROUND_INTENSITY);
				printf("%s",getNomeAlternativaSelecionadaOpcaoEm(linha, coluna).c_str());
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
				printf("]");
				imprimirEspacos(ESPACOS_CELULA - getNomeAlternativaSelecionadaOpcaoEm(linha, coluna).size() - 2);
			} else {
				printf("%s",getNomeAlternativaSelecionadaOpcaoEm(linha, coluna).c_str());
				imprimirEspacos(ESPACOS_CELULA - getNomeAlternativaSelecionadaOpcaoEm(linha, coluna).size());
			}
		}
		printf("\n\t\t\t");
		if(linha == linhaOpcaoSelecionada){
			for(int colunaAtual=0; colunaAtual<colunaOpcaoSelecionada; colunaAtual++){ imprimirEspacos(ESPACOS_CELULA); }
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
			selecionarAlternativaAnterior();
			printf(" %s", getNomeAlternativaSelecionadaOpcaoEm(linhaOpcaoSelecionada, colunaOpcaoSelecionada).c_str());
			selecionarAlternativaSeguinte();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN);
		}
	}
	printf("\n\n\n\n");
}


/*
* D� nomes �s colunas do menu.
* @param _nomesColunas Vetor de strings em que cada string � o nome de uma coluna.
*/
void menu::nomearColunas(vector<string> _nomesColunas){
	nomesColunas = _nomesColunas;
}

/*
* @return O n�mero de alternativas da op��o selecionada.
*/
int menu::getNumeroAlternativasOpcaoSelecionada(){
	return linhas.at(linhaOpcaoSelecionada).at(colunaOpcaoSelecionada).size();
}

/*
* @return O �ndice da alternativa selecionada na op��o selecionada.
*/
int menu::getIndiceAlternativaSelecionada(){
	return alternativasSelecionadas.at(linhaOpcaoSelecionada).at(colunaOpcaoSelecionada);
}

/*
* Modifica a alternativa selecionada da op��o selecionada.
* @param _alternativa A alternativa que ser� selecionada.
* ATEN��O: a fun��o n�o � robusta! Verifique os limites!!
*/
void menu::setIndiceAlternativaSelecionadaOpcaoSelecionada(int _alternativa){
	alternativasSelecionadas.at(linhaOpcaoSelecionada).at(colunaOpcaoSelecionada) = _alternativa;
}

/*
* @param _linha A linha em que a op��o vai ser procurada.
* @param _coluna A coluna em que a op��o vai ser procurada.
* @return A alternativa que foi selecionada da op��o na linha e coluna fornecidas.
* ATEN��O: a fun��o n�o � robusta! Verifique os limites!!
*/
string menu::getNomeAlternativaSelecionadaOpcaoEm(int _linha, int _coluna){
	return linhas.at(_linha).at(_coluna).at(alternativasSelecionadas.at(_linha).at(_coluna));
}








