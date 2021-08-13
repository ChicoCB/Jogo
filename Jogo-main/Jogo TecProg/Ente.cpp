#include "Ente.h"

Ente::Ente():
	Janela(NULL)
{
}

Ente::~Ente()
{
	Janela = NULL;
}

void Ente::setJanela(sf::RenderWindow* janela)
{
	Janela = janela;
}

sf::RenderWindow* Ente::getJanela()
{
	return Janela;
}
