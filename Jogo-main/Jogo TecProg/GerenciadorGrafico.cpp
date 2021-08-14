#include "GerenciadorGrafico.h"
#include "Jogo.h"

GerenciadorGrafico::GerenciadorGrafico():
	Janela(sf::VideoMode(static_cast <unsigned int>(COMPRIMENTO_RESOLUCAO), static_cast <unsigned int>(ALTURA_RESOLUCAO)),
			"Jogo"/*, sf::Style::Fullscreen*/),
    View(sf::Vector2f(COMPRIMENTO_RESOLUCAO/2, ALTURA_RESOLUCAO/2), sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO))
{
}

void GerenciadorGrafico::LoopJogo(Jogo* jogo, int estado)
{
    sf::Clock Tempo;
    int Estado = estado;

    while (isOpen())
    {
        sf::Event evento;
        while (getJanela().pollEvent(evento))
        {
            if (evento.type == sf::Event::TextEntered) {
                if (evento.text.unicode == 27)
                {
                    jogo->setEstadoAtual(Estado);
                    Estado = 6;
                    jogo->setEstado(6);
                }
                cout << evento.text.unicode << endl;
                jogo->MenusJogo(Estado, evento.text.unicode);
            }
            if (evento.type == sf::Event::Closed)
                getJanela().close();
            //cout << TeclaApertada() << endl;
        }

        clear();
        float DeltaTempo = Tempo.restart().asSeconds();
        if (DeltaTempo > 1.f / 20.f)
            DeltaTempo = 1.f / 20.f;

        jogo->Atualiza(DeltaTempo);
        Estado = jogo->getEstado();

        updateView();

        display();
    }
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

void GerenciadorGrafico::TeclaApertada(char* direita, char* esquerda, char* pulo, char* atira)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        *direita = 'D';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        *esquerda = 'A';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        *pulo = 'W';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        *atira = ' ';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (*direita == 'D')
            *direita = '>';
        else
            *direita = 'R';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (*esquerda == 'A')
            *esquerda = '<';
        else
            *esquerda = 'L';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if (*pulo == 'W')
            *pulo = 'J';
        else
            *pulo = 'U';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        if (*atira == ' ')
            *atira = 'S';
        else
            *atira = 'E';
    }
}

