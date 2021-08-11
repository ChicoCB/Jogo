#pragma once
#include "Menu.h"
#include "stdafx.h"

class MenuColocacao : public Menu
{
private:
	bool Digitando;
	//int Limite;
	sf::String Nome1;
	sf::String Nome2;
	sf::String Nome3;
	sf::String Nome4;

public:
	MenuColocacao(unsigned int comprimento, unsigned int altura, int tamanho, Jogo* jg);
	~MenuColocacao();

	//void setEditavel(bool editavel);

	void LoopMenu(sf::Event* evento);
};

