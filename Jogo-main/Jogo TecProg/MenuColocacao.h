#pragma once
#include "Menu.h"
#include "stdafx.h"
#include <sstream>

class Jogo;

class MenuColocacao : public Menu
{
private:
	bool Digitando;
	string Nome;
	int Limite;
	int EstadoAnterior;

public:
	MenuColocacao(  int tamanho, Jogo* jg);
	~MenuColocacao();

	//void setEditavel(bool editavel);

	void Recupera();
	void Inicializa();

	void setEditavel(bool Editavel);
	void setEstadoAnterior(int estadoanterior);

	void LoopMenu(char tecla);
};

