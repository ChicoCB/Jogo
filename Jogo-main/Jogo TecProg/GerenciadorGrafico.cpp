#include "GerenciadorGrafico.h"

GerenciadorGrafico::GerenciadorGrafico():
	Janela(sf::VideoMode(static_cast <unsigned int>(COMPRIMENTO_RESOLUCAO), static_cast <unsigned int>(ALTURA_RESOLUCAO)),
			"Jogo"/*, sf::Style::Fullscreen*/),
    View(sf::Vector2f(COMPRIMENTO_RESOLUCAO/2, ALTURA_RESOLUCAO/2), sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO))
{
}

GerenciadorGrafico::~GerenciadorGrafico()
{
}

sf::RenderWindow& GerenciadorGrafico::getJanela()
{
	return Janela;
}

sf::View& GerenciadorGrafico::getView()
{
	return View;
}

void GerenciadorGrafico::updateView()
{
	Janela.setView(View);
}

void GerenciadorGrafico::resetaView()
{
	atualizaView(sf::Vector2f(COMPRIMENTO_RESOLUCAO/2, ALTURA_RESOLUCAO/2));
}

void GerenciadorGrafico::atualizaView(sf::Vector2f posicao)
{
	View.setCenter(posicao);
}


void GerenciadorGrafico::desenhar(Entidade* pentidade)
{
	if (pentidade != NULL)
		Janela.draw(pentidade->getCorpo());
	else
	{
		cout << "Erro - entidade nula." << endl;
		exit(1);
	}
}

void GerenciadorGrafico::desenhar(sf::Text texto)
{
	Janela.draw(texto);
}

void GerenciadorGrafico::fechar()
{
	Janela.close();
}

void GerenciadorGrafico::display()
{
	Janela.display();
}

void GerenciadorGrafico::clear()
{
	Janela.clear();
}

bool GerenciadorGrafico::isOpen()
{
	return Janela.isOpen();
}

/*
void GerenciadorGrafico::pollEvent(sf::Event* evento)
{
	Janela.pollEvent(evento);
}
*/
