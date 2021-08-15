#pragma once
#include "stdafx.h"
#include "Entidade.h"
#include "Texto.h"

class Jogo;

class GerenciadorGrafico
{
private:

	vector<sf::RectangleShape*> ListaCorpos;

	map<string, sf::Texture> Texturas;
	map<string, sf::IntRect> SubTexturas;
	map<string, sf::Font> Fontes;
	map<string, sf::Color> Cores;

	bool Carregou;

	sf::RenderWindow Janela;
	sf::View View;
		
public:
	GerenciadorGrafico();
	~GerenciadorGrafico();

	void LoopJogo(Jogo* jogo, int estado);
	void CarregarJogo(bool carregou);

	void resetaView();
	void atualizaView(float x, float y);
	void fechar();

	//void criaTexto(int id, float dim, float posx, float posy, string texto, string cor, string fonte);
	void desenhar(Texto texto);
	void desenhar(sf::Text texto);

	void criaCorpo(Entidade* pentidade, float dimx, float dimy, float posx, float posy, string textura);
	void movimenta(int id, float x, float y);
	void desenhar(int id, bool desalocavel);

	void setDimensoes(int id, float x, float y);
	float getDimensoesX(int id);
	float getDimensoesY(int id);

	void setPosicao(int id, float x, float y);
	float getPosicaoX(int id);
	float getPosicaoY(int id);

	void setSubTextura(int id, string subtext);

	void TeclaApertada(char* direita, char* esquerda, char *pulo, char *atira);

	void CarregaTextura(string textura);
	void InicializaTexturas();
	void InicializaSubTexturas();
	void InicializaFontes();
	void InicializaCores();
};


