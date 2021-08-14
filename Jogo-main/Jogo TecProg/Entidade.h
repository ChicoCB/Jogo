#pragma once
#include "stdafx.h"
#include "Ente.h"

class Personagem;
class GerenciadorGrafico;

class Entidade : public Ente
{
protected:
	sf::Vector2f DimensoesCorpo;
	//float DimensaoX, DimensaoY;

	sf::Vector2f Movimento;
	//float MovimentoX, MovimentoY;

	sf::Vector2f Posicao;
	//float PosicaoX, PosicaoY;

	sf::RectangleShape Corpo;//
	sf::Texture Textura;//

	int IdCorpo;
	bool Desalocavel;
	
public:
	Entidade();
	virtual ~Entidade();

	void setDimensoes(sf::Vector2f dimensoes);
	//void setDimensoes(float x, float y);

	sf::Vector2f getDimensoes();
	float getDimensoesX();
	float getDimensoesY();
		
;
	void setPosicao(sf::Vector2f posicao);
	//void setPosicao(float x, float y);
	sf::Vector2f getPosicao();
	float getPosicaoX();
	float getPosicaoY();

	sf::Vector2f getMovimento();
	float getMovimentoX();
	float getMovimentoY();

	void setDesalocavel(bool desalocavel);
	bool getDesalocavel();

	sf::RectangleShape& getCorpo();

	void setTextura(const string textura);

	void setId(int id);
	int getId();

	//void movimenta(float movimentox, float movimentoy);
	void movimenta(sf::Vector2f movimento);
	void desenhar();

	virtual void colidir(Personagem* personagem);
	virtual void atualiza(float deltaTempo);
	virtual void salvar();
};

