#include "Entidade.h"
#include "Personagem.h"
#include "GerenciadorGrafico.h"


Entidade::Entidade():
	Ente(),
	Desalocavel(false)
{
}

Entidade::~Entidade()
{
}

sf::RectangleShape& Entidade::getCorpo()
{
	return Corpo;
	//return gerenciadorGrafico.
}

void Entidade::setDimensoes(sf::Vector2f dimensoes)
{
	DimensoesCorpo = dimensoes;
	Corpo.setSize(DimensoesCorpo);
	Corpo.setOrigin(DimensoesCorpo.x / 2, DimensoesCorpo.y / 2);
}

/*
void Entidade::setDimensoes(float x, float y)
{
	pGerenciadorGrafico->setDimensoes(IdCorpo, x, y);
}
*/


sf::Vector2f Entidade::getDimensoes()
{
	return DimensoesCorpo;
}

/*
float Entidade::getDimensoesX()
{
	return pGerenciadorGrafico->getDimensoesX(IdCorpo);
}

float Entidade::getDimensoesY()
{
	return pGerenciadorGrafico->getDimensoesY(IdCorpo);
}
*/


void Entidade::setPosicao(sf::Vector2f posicao)
{
	Posicao = posicao;
	Corpo.setPosition(Posicao);
}
/*
void Entidade::setPosicao(float x, float y)
{
	pGerenciadorGrafico->setPosicao(IdCorpo, x, y);
}
*/


sf::Vector2f Entidade::getPosicao()
{
	Posicao = Corpo.getPosition();
	return Posicao;
}

/*
float Entidade::getPosicaoX()
{
	return pGerenciadorGrafico->getPosicaoX(IdCorpo);
}

float Entidade::getPosicaoY()
{
	return pGerenciadorGrafico->getPosicaoY(IdCorpo);
}
*/


sf::Vector2f Entidade::getMovimento()
{
	return Movimento;
}
/*
float Entidade::getMovimentoX()
{
	return MovimentoX;
}

float Entidade::getMovimentoY()
{
	return MovimentoY;
}
*/


void Entidade::setDesalocavel(bool desalocavel)
{
	Desalocavel = desalocavel;
}

bool Entidade::getDesalocavel()
{
	return Desalocavel;
}

void Entidade::setTextura(const string textura)
{
	if (!Textura.loadFromFile(textura))
        cerr << "Erro. Nao foi possivel carregar a textura de uma Entidade." << endl;

	Corpo.setTexture(&Textura);
}

void Entidade::setId(int id)
{
	IdCorpo = id;
}

int Entidade::getId()
{
	return IdCorpo;
}

void Entidade::colidir(Personagem* personagem)
{
}
/*
void Entidade::movimenta(float movimentox, float movimentoy)
{
	pGerenciadorGrafico->movimenta(this, movimentox, movimentoy);

}
*/


void Entidade::movimenta(sf::Vector2f movimento)
{
	pGerenciadorGrafico->movimenta(this, movimento);
	//Corpo.move(movimento);
}

void Entidade::atualiza(float deltaTempo)
{
}

void Entidade::desenhar()
{
	pGerenciadorGrafico->desenhar(this);
}

void Entidade::salvar()
{
}
