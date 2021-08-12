#include "Porta.h"
#include "Jogo.h"

Porta::Porta():Obstaculo()
{
	this->setPosicao(sf::Vector2f(COMPRIMENTO_CENARIO - 150.f , ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + 50.f)));
	this->setDimensoes(sf::Vector2f(50.f, 100.f));
	this->setOrigem();
	this->setTextura("");
}

Porta::~Porta()
{
}


void Porta::setJogo(Jogo* jg)
{
	jogo = jg;
}

void Porta::colidir(Personagem* personagem)
{
	if (personagem->getAmigavel())
	{
		if (jogo->getEstado() == 4)
		{
			jogo->getFazendeira()->setFaseAtual(&jogo->getQuarto());
			jogo->getFazendeira()->setPosicao(sf::Vector2f(200.f, 200.f));
			if (jogo->getMultiplayer())
			{
				jogo->getBruxo()->setFaseAtual(&jogo->getQuarto());
				jogo->getBruxo()->setPosicao(sf::Vector2f(200.f, 200.f));
			}

			jogo->setEstado(5);
		}
		else 
		{
			jogo->getMenuColocacao().setEditavel(true);
			jogo->setEstado(3);	
		}
	}
}
