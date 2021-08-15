#pragma once
#include "Menu.h"

class Jogo;

class MenuJogadores : public Menu
{
private:

public:
	MenuJogadores( int tamanho, Jogo* jg);
	~MenuJogadores();

	void LoopMenu(char tecla);
};

