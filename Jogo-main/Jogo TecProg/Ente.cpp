#include "Ente.h"

Ente::Ente()
{
}

Ente::~Ente()
{
}

void Ente::setJanela(sf::RenderWindow* janela)
{
	Janela = janela;
}

sf::RenderWindow* Ente::getJanela()
{
	return Janela;
}
