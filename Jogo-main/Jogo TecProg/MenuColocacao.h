#pragma once
#include "Menu.h"
#include "stdafx.h"
#include <sstream>

class Jogo;

class MenuColocacao : public Menu
{
private:
	bool Digitando;
	sf::String Nome;
	int Limite;

public:
	MenuColocacao(unsigned int comprimento, unsigned int altura, int tamanho, Jogo* jg);
	~MenuColocacao();

	//void setEditavel(bool editavel);

	void Inicializa();

	void setEditavel(bool Editavel);

	void LoopMenu(sf::Event* evento);
};

