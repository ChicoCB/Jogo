#include "Atirador.h"

Atirador::Atirador()
{
}

Atirador::~Atirador()
{
}

void Atirador::setFaseAtual(Fase* faseatual) {
	faseAtual = faseatual;
}

void Atirador::atiraProjetilHorizontal(bool olharDireita, sf::Vector2f Posicao, sf::Vector2f Dimensao)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	novo->setPosicao(Posicao);

	if (olharDireita)
	{
		novo->setVelocidade(sf::Vector2f(600.f, 0.f));
	}
	else
	{
		novo->setVelocidade(sf::Vector2f(-600.f, 0.f));
	}
	novo->setDimensoes(sf::Vector2f(10.f, 10.f));
	novo->setOrigem();
	novo->setJanela(faseAtual->getJanela());
	novo->setAmigavel(false);
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase
}

void Atirador::atiraProjetilHorizontal(bool olharDireita, sf::Vector2f Posicao, sf::Vector2f Dimensao, float Altura)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	if (olharDireita)
	{
		novo->setPosicao(sf::Vector2f(Posicao.x + Dimensao.x / 2, Altura));
		novo->setVelocidade(sf::Vector2f(600.f, 0.f));
	}
	else
	{
		novo->setPosicao(sf::Vector2f(Posicao.x - Dimensao.x / 2, Altura));
		novo->setVelocidade(sf::Vector2f(-600.f, 0.f));
	}
	novo->setDimensoes(sf::Vector2f(10.f, 10.f));
	novo->setOrigem();
	novo->setJanela(faseAtual->getJanela());
	novo->setAmigavel(false);
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase
}

void Atirador::atiraProjetilDirecionado(bool olharDireita, sf::Vector2f Posicao, sf::Vector2f Dimensao)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	float deltax = faseAtual->getFazendeira()->getPosicao().x - Posicao.x;
	float deltay = faseAtual->getFazendeira()->getPosicao().y - Posicao.y;
	float modulo = sqrt(deltax * deltax + deltay * deltay);

	novo->setPosicao(Posicao);
	novo->setVelocidade(sf::Vector2f(400.f * deltax / modulo, 400.f * deltay / modulo));

	novo->setDimensoes(sf::Vector2f(20.f, 20.f));
	novo->setOrigem();
	novo->setJanela(faseAtual->getJanela());
	novo->setAmigavel(false);
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase	
}
