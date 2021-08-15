#pragma once
#include "Ente.h"
#include "stdafx.h" 
#include "Cenario.h"

class Jogo;

class Menu : public Ente
{
protected:
	int Indice, Tamanho, IdTexto;
	static int IdTextoAtual;

	Cenario PlanoFundo;
	Jogo* jogo;

	sf::Text* menu;
	sf::Font Fonte;

public:
	Menu(int tamanho, Jogo* jg);
	~Menu();

	void incrementaIdTextoAtual();
	void setId(int id);
	int getIdTextoAtual();
	int getId();

	void moverCima();
	void moverBaixo();
	void desenhar();
};


