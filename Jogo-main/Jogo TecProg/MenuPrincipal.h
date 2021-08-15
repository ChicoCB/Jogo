#pragma once
#include "Menu.h"

class Jogo;

class MenuPrincipal : public Menu
{
private:

public:
	MenuPrincipal( int tamanho, Jogo* jg);
	~MenuPrincipal();

	void LoopMenu(char tecla);
};

