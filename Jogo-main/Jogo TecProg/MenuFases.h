#pragma once
#include "Menu.h"

class Jogo;

class MenuFases : public Menu
{
private:

public:
	MenuFases( int tamanho, Jogo* jg);
	~MenuFases();

	void LoopMenu(char tecla);
};

