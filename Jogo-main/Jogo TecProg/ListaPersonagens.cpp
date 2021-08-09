#include "ListaPersonagens.h"

ListaPersonagens::ListaPersonagens()
{
}

ListaPersonagens::~ListaPersonagens()
{
}

void ListaPersonagens::inclua(Personagem* personagem)
{
	listaPersonagens.incluaTipo(personagem);
}

void ListaPersonagens::atualiza(float deltaTempo)
{
	listaPersonagens.atualiza(deltaTempo);
}

void ListaPersonagens::desenhar()
{
	listaPersonagens.desenhar();
}

int ListaPersonagens::getTamanho()
{
	return listaPersonagens.getTamanho();
}

Personagem* ListaPersonagens::indice(int i)
{
	return listaPersonagens.indice(i);
}
