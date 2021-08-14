#include "GerenciadorGrafico.h"
#include "Jogo.h"

//int GerenciadorGrafico::IdAtual = 0;

GerenciadorGrafico::GerenciadorGrafico() :
    Janela(sf::VideoMode(static_cast <unsigned int>(COMPRIMENTO_RESOLUCAO), static_cast <unsigned int>(ALTURA_RESOLUCAO)),
        "Jogo"/*, sf::Style::Fullscreen*/),
    View(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO / 2), sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO)),
    IdAtual(0)
{
    Janela.setView(View);
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
                jogo->MenusJogo(Estado, evento.text.unicode);
            }
            if (evento.type == sf::Event::Closed)
                getJanela().close();
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

/*
vector<sf::RectangleShape*>& GerenciadorGrafico::getListaCorpos()
{
    return ListaCorpos;
}
*/

void GerenciadorGrafico::criaCorpo(Entidade* pentidade, float dimx, float dimy, float posx, float posy, string text)
{
    sf::Texture* Textura = new sf::Texture();
    sf::RectangleShape* Corpo = new sf::RectangleShape();

    Corpo->setSize(sf::Vector2f(dimx, dimy));
    Corpo->setPosition(sf::Vector2f(posx, posy));
    Corpo->setOrigin(dimx/2, dimy/2);

    if (!Textura->loadFromFile(text))
        cerr << "Erro. Nao foi possivel carregar a textura de uma Entidade." << endl;
    Corpo->setTexture(Textura);
   // Corpo->setTextureRect(sf::IntRect(150, 300, 300, 300));

    ListaCorpos.push_back(Corpo);

    pentidade->setId(IdAtual);

    IdAtual++;
}

void GerenciadorGrafico::setDimensoes(int id, float x, float y)
{
    ListaCorpos[id]->setSize(sf::Vector2f(x, y));
}

float GerenciadorGrafico::getDimensoesX(int id)
{
    return ListaCorpos[id]->getSize().x;
}

float GerenciadorGrafico::getDimensoesY(int id)
{
    return ListaCorpos[id]->getSize().y;
}

void GerenciadorGrafico::setPosicao(int id, float x, float y)
{
    ListaCorpos[id]->setPosition(sf::Vector2f(x, y));
}

float GerenciadorGrafico::getPosicaoX(int id)
{
    return ListaCorpos[id]->getPosition().x;
}

float GerenciadorGrafico::getPosicaoY(int id)
{
    return ListaCorpos[id]->getPosition().y;
}


void GerenciadorGrafico::desenhar(Entidade* pentidade)
{
    if (pentidade != NULL) 
    {
        //cout << "id: " << pentidade->getId() << endl;
        //if (ListaCorpos[pentidade->getId()] != NULL)
        //   Janela.draw(*ListaCorpos[pentidade->getId()]);
       // else
           Janela.draw(pentidade->getCorpo());
    }

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

void GerenciadorGrafico::movimenta(Entidade* pentidade, sf::Vector2f movimento)
{
    if (pentidade != NULL)
    {
       // if (ListaCorpos[pentidade->getId()] != NULL)
        //    ListaCorpos[pentidade->getId()]->move(movimento);
        pentidade->getCorpo().move(movimento);

    }

    else
    {
        cout << "Erro - entidade nula." << endl;
        exit(1);
    }
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

