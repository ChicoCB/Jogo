#include "Jogo.h"

const float Jogo::Altura = 720;
const float Jogo::Comprimento = 1280;

Jogo::Jogo() :
    Janela(sf::VideoMode(static_cast <unsigned int> (Comprimento),static_cast <unsigned int> (Altura)), "Jogo", sf::Style::Fullscreen),
    View(sf::Vector2f(640.f, 360.f), sf::Vector2f(Comprimento, Altura))
{
	Executar();
}

Jogo::~Jogo()
{
}

const float Jogo::getAltura()
{
    return Altura;
}

const float Jogo::getComprimento()
{
    return Comprimento;
}

void Jogo::Atualiza()
{
    Fase_Quintal.atualiza();
}

void Jogo::Inicializa()
{
    Janela.setView(View);

    InicializaFases();
}

void Jogo::InicializaFases()
{
    Fase_Quintal.setJanela(&Janela);
    Fase_Quintal.setView(&View);
    Fase_Quintal.Inicializa();
}

void Jogo::Executar()
{
    Inicializa();
        
    LoopJogo();
}

void Jogo::LoopJogo()
{
    while (Janela.isOpen())
    {
        sf::Event evento;
        while (Janela.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                Janela.close();
        }
    
        Janela.clear();

        Atualiza();
        
        Janela.setView(View);
        Janela.display();

    }
}
