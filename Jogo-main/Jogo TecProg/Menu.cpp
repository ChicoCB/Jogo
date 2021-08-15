#include "Menu.h"
#include "Jogo.h"



Menu::Menu( int tamanho, Jogo* jg): PlanoFundo()
{
	// (!Fonte.loadFromFile("arial.ttf"))
	//	cout << "Erro ao carregar fonte." << endl;
	jogo = jg;
	Indice = 0;
	Tamanho = tamanho;
}

Menu::~Menu()
{
}


void Menu::moverCima()
{

	if (Indice <= 0)
		Indice = 0;
	else
	{
		Textos[Indice].setCor("Verde");
		Indice--;
		Textos[Indice].setCor("Vermelho");
	}

}

void Menu::moverBaixo()
{
	if (Indice >= Tamanho - 1)
		Indice = Tamanho - 1;
	else
	{
		Textos[Indice].setCor("Verde");
		Indice++;
		Textos[Indice].setCor("Vermelho");
	}
}

void Menu::desenhar()
{
	for (int i = 0; i < Tamanho; i++) {
		//pGerenciadorGrafico->desenhar(menu[i]);

		if (Textos != NULL)
			pGerenciadorGrafico->desenhar(Textos[i]);
	}
}
