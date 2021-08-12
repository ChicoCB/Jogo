#pragma once
#include "Fase.h"
//#include "Entidade.h"

class Atirador// :
	//public Entidade 
{
protected:
	Fase* faseAtual;
	
public:
	Atirador();
	~Atirador();

	void setFaseAtual(Fase* faseatual);

	void atiraProjetilHorizontal(bool olharDireita, sf::Vector2f Posicao, sf::Vector2f Dimensao);
	void atiraProjetilHorizontal(bool olharDireita, sf::Vector2f Posicao, sf::Vector2f Dimensao, float Altura);
	void atiraProjetilDirecionado(bool olharDireita, sf::Vector2f Posicao, sf::Vector2f Dimensao);
};

