#include "Entidade.h"
#include "Personagem.h"
#include "GerenciadorGrafico.h"

int Entidade::IdCorpoAtual = 0;

Entidade::Entidade():
	Ente(),
	Desalocavel(false),
	MovimentoX(0),
	MovimentoY(0),
	IdCorpo(0)
{
}

Entidade::~Entidade()
{
}
 
void Entidade::setDimensoes(float x, float y)
{
	pGerenciadorGrafico->setDimensoes(IdCorpo, x, y);
}


float Entidade::getDimensoesX()
{
	return pGerenciadorGrafico->getDimensoesX(IdCorpo);
}

float Entidade::getDimensoesY()
{
	return pGerenciadorGrafico->getDimensoesY(IdCorpo);
}

void Entidade::setPosicao(float x, float y)
{
	pGerenciadorGrafico->setPosicao(IdCorpo, x, y);
}

float Entidade::getPosicaoX()
{
	return pGerenciadorGrafico->getPosicaoX(IdCorpo);
}

float Entidade::getPosicaoY()
{
	return pGerenciadorGrafico->getPosicaoY(IdCorpo);
}


void Entidade::setMovimento(float x, float y)
{
	MovimentoX = x;
	MovimentoY = y;
}

float Entidade::getMovimentoX()
{
	return MovimentoX;
}

float Entidade::getMovimentoY()
{
	return MovimentoY;
}

void Entidade::setDesalocavel(bool desalocavel)
{
	Desalocavel = desalocavel;
}

bool Entidade::getDesalocavel()
{
	return Desalocavel;
}

void Entidade::incrementaIdCorpoAtual()
{
	IdCorpoAtual++;
}

void Entidade::setId(int id)
{
	IdCorpo = id;
}

int Entidade::getIdCorpoAtual()
{
	return IdCorpoAtual;
}

int Entidade::getId()
{
	return IdCorpo;
}

void Entidade::setSubTextura(string subtext)
{
	pGerenciadorGrafico->setSubTextura(IdCorpo, subtext);
}

void Entidade::colidir(Personagem* personagem)
{
}

void Entidade::movimenta(float movimentox, float movimentoy)
{
	pGerenciadorGrafico->movimenta(IdCorpo, movimentox, movimentoy);

}

void Entidade::atualiza(float deltaTempo)
{
}

void Entidade::desenhar()
{
	pGerenciadorGrafico->desenhar(IdCorpo, Desalocavel);
}

void Entidade::salvar()
{
}
