#pragma once
#include "Fase.h"
#include "Passaro.h"
#include "Espinho.h"
#include "Fantasma.h"
#include "Estatico.h"
#include "GerenciadorFisica.h"
#include "Porta.h"

class Jogo;

class Quintal : public Fase
{
private:
	Porta porta;

public:
	Quintal();
	~Quintal();

	void inicializa();
	void desenhar();
	void atualiza(float deltaTempo);

	void criaPassaro(sf::Vector2f posicao);
	void criaPlataformas();

	void recuperar();
	void recuperarPassaros();
};

