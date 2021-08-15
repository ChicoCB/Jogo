#include "Menu.h"
#include "Jogo.h"

int Menu::IdTextoAtual = 0;

Menu::Menu( int tamanho, Jogo* jg): IdTexto(0), PlanoFundo()
{
	if (!Fonte.loadFromFile("arial.ttf"))
		cout << "Erro ao carregar fonte." << endl;

	jogo = jg;
	Indice = 0;
	Tamanho = tamanho;
}

Menu::~Menu()
{
}

void Menu::incrementaIdTextoAtual()
{
	IdTextoAtual++;
}

void Menu::setId(int id)
{
	IdTexto = id;
}

int Menu::getIdTextoAtual()
{
	return IdTextoAtual;
}

int Menu::getId()
{
	return IdTexto;
}

void Menu::moverCima()
{

	if (Indice <= 0)
		Indice = 0;
	else
	{
		menu[Indice].setFillColor(sf::Color::Green);
		Indice--;
		menu[Indice].setFillColor(sf::Color::Red);
	}

}

void Menu::moverBaixo()
{
	if (Indice >= Tamanho - 1)
		Indice = Tamanho - 1;
	else
	{
		menu[Indice].setFillColor(sf::Color::Green);
		Indice++;
		menu[Indice].setFillColor(sf::Color::Red);
	}
}

void Menu::desenhar()
{
	for (int i = 0; i < Tamanho; i++) {
		pGerenciadorGrafico->desenhar(menu[i]);
	}
}
