#include "Atirador.h"
#include "Fase.h"
#include "Personagem.h"

Atirador::Atirador()
{
}

Atirador::~Atirador()
{
}

void Atirador::setFaseAtual(Fase* faseatual) {
	faseAtual = faseatual;
}

void Atirador::atiraProjetilHorizontal(Personagem* personagem)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	if (personagem->getOlharDireita())
	{
		novo->setPosicao(sf::Vector2f(personagem->getPosicao().x + personagem->getDimensoes().x / 2, personagem->getPosicao().y));
		novo->setVelocidade(sf::Vector2f(600.f, 0.f));
	}
	else
	{
		novo->setPosicao(sf::Vector2f(personagem->getPosicao().x - personagem->getDimensoes().x / 2, personagem->getPosicao().y));
		novo->setVelocidade(sf::Vector2f(-600.f, 0.f));
	}
	novo->setDimensoes(sf::Vector2f(10.f, 10.f));
	novo->setOrigem();
	novo->setJanela(faseAtual->getJanela());
	novo->setAmigavel(personagem->getAmigavel());
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase
}

void Atirador::atiraProjetilHorizontal(Personagem* personagem, float Altura)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	if (personagem->getOlharDireita())
	{
		novo->setPosicao(sf::Vector2f(personagem->getPosicao().x + personagem->getDimensoes().x / 2, Altura));
		novo->setVelocidade(sf::Vector2f(600.f, 0.f));
	}
	else
	{
		novo->setPosicao(sf::Vector2f(personagem->getPosicao().x - personagem->getDimensoes().x / 2, Altura));
		novo->setVelocidade(sf::Vector2f(-600.f, 0.f));
	}
	novo->setDimensoes(sf::Vector2f(10.f, 10.f));
	novo->setOrigem();
	novo->setJanela(faseAtual->getJanela());
	novo->setAmigavel(personagem->getAmigavel());
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase
}

void Atirador::atiraProjetilDirecionado(Personagem* personagem)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	float deltax = faseAtual->getFazendeira()->getPosicao().x - personagem->getPosicao().x;
	float deltay = faseAtual->getFazendeira()->getPosicao().y - personagem->getPosicao().y;
	float modulo = sqrt(deltax * deltax + deltay * deltay);

	novo->setPosicao(personagem->getPosicao());
	novo->setVelocidade(sf::Vector2f(400.f * deltax / modulo, 400.f * deltay / modulo));

	novo->setDimensoes(sf::Vector2f(20.f, 20.f));
	novo->setOrigem();
	novo->setJanela(faseAtual->getJanela());
	novo->setAmigavel(personagem->getAmigavel());
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase	
}
