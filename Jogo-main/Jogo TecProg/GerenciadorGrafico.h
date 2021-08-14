#pragma once
#include "stdafx.h"
#include "Entidade.h"

class Jogo;

class GerenciadorGrafico
{
private:

	int IdAtual;
	vector<sf::RectangleShape*> ListaCorpos;

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

	//vector<sf::RectangleShape*>& getListaCorpos();

	void criaCorpo(Entidade* pentidade, float dimx, float dimy, float posx, float posy, string textura);
	
	void setDimensoes(int id, float x, float y);
	float getDimensoesX(int id);
	float getDimensoesY(int id);

	void setPosicao(int id, float x, float y);
	float getPosicaoX(int id);
	float getPosicaoY(int id);

	//float getMovimentoX(int id);
	//float getMovimentoY(int id);

	void desenhar(Entidade* pentidade);
	void desenhar(sf::Text texto);
	void fechar();

	void movimenta(Entidade* pentidade, sf::Vector2f movimento);

	void display();
	void clear();
	bool isOpen();
	//void pollEvent(sf::Event* evento);
	void LoopJogo(Jogo* jogo, int estado);

	void TeclaApertada(char* direita, char* esquerda, char *pulo, char *atira);
};


