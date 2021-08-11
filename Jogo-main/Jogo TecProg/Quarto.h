#pragma once
#include "Fase.h"
#include "Espinho.h"
#include "Fantasma.h"
#include "Estatico.h"
#include "GerenciadorFisica.h"
#include "Chefao.h"

class Jogo;

class Quarto : public Fase
{
private:

public:
	Quarto();
	~Quarto();

	void inicializa();
	void desenhar();
	void atualiza(float deltaTempo);

	void recuperar();
	void recuperarFantasmas();
	void recuperarChefao();

	void criaFantasma(sf::Vector2f posicao);
	void criaChefao(sf::Vector2f posicao);
	void criaPlataformas();
};

