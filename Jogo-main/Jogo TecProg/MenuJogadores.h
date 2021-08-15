#pragma once
#include "Menu.h"

class Jogo;

class MenuJogadores : public Menu
{
private:

	int LimiteBaixo, LimiteCima;

public:
	MenuJogadores( int tamanho, Jogo* jg);
	~MenuJogadores();

	void LoopMenu(char tecla);
	void Inicializa();
};

