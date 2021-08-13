#include "GerenciadorColisoes.h"

GerenciadorColisoes::GerenciadorColisoes():
	plistaEntidades(NULL),
	plistaPersonagens(NULL)
{
}

GerenciadorColisoes::~GerenciadorColisoes()
{
}

void GerenciadorColisoes::setListaEntidades(ListaEntidades* listaentidades)
{
	plistaEntidades = listaentidades;
}

void GerenciadorColisoes::setListaPersonagens(ListaPersonagens* listapersonagens)
{
	plistaPersonagens = listapersonagens;
}

void GerenciadorColisoes::incluaEntidade(Entidade* entidade)
{
	plistaEntidades->inclua(entidade);
}


void GerenciadorColisoes::checaColisoes()
{
	for (unsigned int i = 0; i < plistaPersonagens->tamanho(); i++)
	{
		for (unsigned int j = 0; j < plistaEntidades->tamanho(); j++)
		{
			checaColisao((*plistaPersonagens)[i], (*plistaEntidades)[j]);
		}
	}
}

void GerenciadorColisoes::checaColisao(Personagem* personagem, Entidade* entidade)
{
	float deltaX = entidade->getPosicao().x - personagem->getPosicao().x;
	float deltaY = entidade->getPosicao().y - personagem->getPosicao().y;
	float intersecaoX = abs(deltaX) - (personagem->getDimensoes().x / 2 + entidade->getDimensoes().x / 2);
	float intersecaoY = abs(deltaY) - (personagem->getDimensoes().y / 2 + entidade->getDimensoes().y / 2);

	if (intersecaoX < 0.f && intersecaoY < 0.f)
	{
		entidade->colidir(personagem);
	}
}
