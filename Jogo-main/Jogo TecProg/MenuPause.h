#pragma once
#include "Menu.h"

class Jogo;

class MenuPause : public Menu
{
private:
	int EstadoAtual;

public:
	MenuPause( int tamanho, Jogo* jg);
	~MenuPause();

	void setEstadoAtual(int estadoatual);
	int getEstadoAtual();
	void LoopMenu(char tecla);

	void Inicializa();
};

