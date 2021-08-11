#include "MenuColocacao.h"

MenuColocacao::MenuColocacao(unsigned int comprimento, unsigned int altura, int tamanho, Jogo* jg):
	Menu(comprimento, altura, tamanho, jg)
{
	sf::Text TextoPontuacao;
	TextoPontuacao.setFillColor(sf::Color::Green);
	TextoPontuacao.setCharacterSize(24);
	TextoPontuacao.setString("Pontuacao:");
	TextoPontuacao.setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 150));
	TextoPontuacao.setFont(Fonte);
	menu = new sf::Text[Tamanho];
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setCharacterSize(24);
	menu[0].setString("0 - Vazio");
	menu[0].setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 200));
	menu[0].setFont(Fonte);
	menu[1].setFillColor(sf::Color::Green);
	menu[1].setCharacterSize(24);
	menu[1].setString("0 - Vazio");
	menu[1].setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 250));
	menu[1].setFont(Fonte);
	menu[2].setFillColor(sf::Color::Green);
	menu[2].setCharacterSize(24);
	menu[2].setString("0 - Vazio");
	menu[2].setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 300));
	menu[2].setFont(Fonte);
	menu[3].setFillColor(sf::Color::Green);
	menu[3].setCharacterSize(24);
	menu[3].setString("0 - Vazio");
	menu[3].setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 350));
	menu[3].setFont(Fonte);
	menu[4].setFillColor(sf::Color::Green);
	menu[4].setCharacterSize(24);
	menu[4].setString("Salvar Pontuação");
	menu[4].setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 450));
	menu[4].setFont(Fonte);
	menu[5].setFillColor(sf::Color::Green);
	menu[5].setCharacterSize(24);
	menu[5].setString("Apagar Tudo");
	menu[5].setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 550));
	menu[5].setFont(Fonte);

	Digitando = false;
}

MenuColocacao::~MenuColocacao()
{
}

void MenuColocacao::LoopMenu(sf::Event* evento)
{
	//if (!Digitando)

	//else
	if (Digitando){
		switch (Indice)
		{
			case 0:
				if (evento->type == sf::Event::TextEntered)
				{
					Nome1.insert(Nome1.getSize(), evento->text.unicode);
					cout << "Entrou" << endl;

					if (evento->text.unicode == sf::Keyboard::BackSpace)
						Nome1.erase(Nome1.getSize() - 1);
					if (evento->text.unicode == sf::Keyboard::T)
					{
						menu[0].setString(Nome1);
						menu[0].setFillColor(sf::Color::Blue);
						menu[4].setFillColor(sf::Color::Red);
						Indice = 4;
						Digitando = false;
					}
				}
			break;
		}
	}
	if (evento->type == sf::Event::KeyPressed)
	{
		if (evento->key.code == sf::Keyboard::Key::W)
				moverCima();
		if (evento->key.code == sf::Keyboard::Key::S)
				moverBaixo();
		if (evento->key.code == sf::Keyboard::Key::Enter)
		{
			switch (Indice)
			{
				case 0:
					Digitando = true;
				break;
			case 1:
				
				break;
			case 2:
			{
		
				
			}
			case 5:
				menu[0].setString("0 - Vazio");
				menu[1].setString("0 - Vazio");
				menu[2].setString("0 - Vazio");
				menu[3].setString("0 - Vazio");
				break;

			break;
			}
		}
	}
}
