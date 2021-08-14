#pragma once
#include "stdafx.h"
#include "Entidade.h"

class Jogo;

class GerenciadorGrafico
{
private:

	sf::RenderWindow Janela;
	sf::View View;
	sf::Event evento;
	sf::Clock Tempo;
		
public:
	GerenciadorGrafico();
	~GerenciadorGrafico();

	sf::RenderWindow& getJanela();

	sf::View& getView();
	void updateView();
	void resetaView();
	void atualizaView(sf::Vector2f posicao);

	void desenhar(Entidade* pentidade);
	void desenhar(sf::Text texto);
	void fechar();

	void display();
	void clear();
	bool isOpen();
	//void pollEvent(sf::Event* evento);
	void LoopJogo(Jogo* jogo, int estado);

	void TeclaApertada(char* direita, char* esquerda, char *pulo, char *atira);
};


