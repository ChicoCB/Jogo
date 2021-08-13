#pragma once
#include "stdafx.h"
#include "Ente.h"

class Personagem;
class GerenciadorGrafico;

class Entidade : public Ente
{
protected:
	sf::Vector2f DimensoesCorpo;
	sf::Vector2f Movimento;
	sf::Vector2f Posicao;
	sf::RectangleShape Corpo;
	sf::Texture Textura;

	bool Desalocavel;
	
public:
	Entidade();
	virtual ~Entidade();

	void setDimensoes(sf::Vector2f dimensoes);
	sf::Vector2f getDimensoes();
	void setPosicao(sf::Vector2f posicao);
	sf::Vector2f getPosicao();
	void setDesalocavel(bool desalocavel);
	bool getDesalocavel();
	sf::Vector2f getMovimento();
	sf::RectangleShape& getCorpo();
	void setTextura(const string textura);

	void movimenta(sf::Vector2f movimento);
	void desenhar();

	virtual void colidir(Personagem* personagem);
	virtual void atualiza(float deltaTempo);
	virtual void salvar();
};

