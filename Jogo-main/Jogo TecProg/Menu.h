#pragma once
#include "Ente.h"
#include "stdafx.h" 
#include "Cenario.h"
#include "Texto.h"

class Jogo;

class Menu : public Ente
{
protected:
	int Indice, Tamanho;

	Texto* Textos;
	Jogo* jogo;
	Cenario PlanoFundo;

public:
	Menu(int tamanho, Jogo* jg);
	~Menu();

	void moverCima();
	void moverBaixo();
	void desenhar();
};


