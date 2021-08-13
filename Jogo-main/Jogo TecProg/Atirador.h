#pragma once
//#include "Entidade.h"
#include "stdafx.h"
//
//#include "Fase.h"
class Fase;
class Personagem;
//class Jogador;

class Atirador// :
	//public Entidade 
{
protected:
	Fase* faseAtual;
	
public:
	Atirador();
	~Atirador();

	void setFaseAtual(Fase* faseatual);

	void atiraProjetilHorizontal(Personagem* personagem);
	void atiraProjetilHorizontal(Personagem* personagem, float Altura);
	void atiraProjetilDirecionado(Personagem* personagem);
};

