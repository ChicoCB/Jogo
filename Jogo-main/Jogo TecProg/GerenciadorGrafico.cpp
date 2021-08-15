#include "GerenciadorGrafico.h"
#include "Jogo.h"

GerenciadorGrafico::GerenciadorGrafico() :
    Janela(sf::VideoMode(static_cast <unsigned int>(COMPRIMENTO_RESOLUCAO), static_cast <unsigned int>(ALTURA_RESOLUCAO)),
        "Jogo"/*, sf::Style::Fullscreen*/),
    View(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO / 2), sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO)),
    Carregou(false)
{
    Janela.setView(View);


}

void GerenciadorGrafico::LoopJogo(Jogo* jogo, int estado)
{
    sf::Clock Tempo;
    int Estado = estado;

    while (Janela.isOpen())
    {
        CarregarJogo(Carregou);
        sf::Event evento;
        while (Janela.pollEvent(evento))
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
                Janela.close();
        }

        Janela.clear();
        float DeltaTempo = Tempo.restart().asSeconds();
        if (DeltaTempo > 1.f / 20.f)
            DeltaTempo = 1.f / 20.f;

        jogo->Atualiza(DeltaTempo);
        Estado = jogo->getEstado();

        Janela.setView(View);

        Janela.display();
        //display();
    }
}

void GerenciadorGrafico::CarregarJogo(bool carregou)
{
    if (!carregou) {
        InicializaFontes();

        sf::Text Carregamento;
        Carregamento.setFillColor(sf::Color::Blue);
        Carregamento.setFont(Fontes["Arial"]);
        Carregamento.setString("Carregando Jogo...");
        Carregamento.setCharacterSize(24);
        Carregamento.setPosition(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 4, 350.f));
        Janela.draw(Carregamento);
        Janela.display();

        InicializaTexturas();
        InicializaSubTexturas();
        InicializaCores();

        Carregou = true;
    }
}

GerenciadorGrafico::~GerenciadorGrafico()
{
}

void GerenciadorGrafico::resetaView()
{
	atualizaView(COMPRIMENTO_RESOLUCAO/2, ALTURA_RESOLUCAO/2);
}

void GerenciadorGrafico::atualizaView(float x, float y)
{
	View.setCenter(sf::Vector2f(x, y));
}

void GerenciadorGrafico::criaCorpo(Entidade* pentidade, float dimx, float dimy, float posx, float posy, string text)
{
    sf::RectangleShape* Corpo = new sf::RectangleShape();

    Corpo->setSize(sf::Vector2f(dimx, dimy));
    Corpo->setPosition(sf::Vector2f(posx, posy));
    Corpo->setOrigin(dimx/2, dimy/2);
    Corpo->setTexture(&Texturas[text]);
    if (SubTexturas[text] != sf::IntRect(0,0,0,0))
        Corpo->setTextureRect(SubTexturas[text]);

    ListaCorpos.push_back(Corpo);

    if (pentidade != NULL)
        pentidade->setId(pentidade->getIdCorpoAtual());

    pentidade->incrementaIdCorpoAtual();
}


void GerenciadorGrafico::desenhar(Texto texto)
{
    sf::Text taux;

    taux.setFillColor(Cores[texto.getCor()]);
    taux.setCharacterSize(texto.getDimensao());
    taux.setString(texto.getMensagem());
    taux.setPosition(sf::Vector2f(texto.getPosicaoX(), texto.getPosicaoY()));
    taux.setFont(Fontes[texto.getFonte()]);

    Janela.draw(taux);
}

void GerenciadorGrafico::desenhar(sf::Text texto)
{
    Janela.draw(texto);
}

void GerenciadorGrafico::setDimensoes(int id, float x, float y)
{
    ListaCorpos[id]->setSize(sf::Vector2f(x, y));
    ListaCorpos[id]->setOrigin( x / 2,  y / 2);
}

float GerenciadorGrafico::getDimensoesX(int id)
{
    if (ListaCorpos[id] != NULL)
        return ListaCorpos[id]->getSize().x;
    else if (id < 0 || id >= ListaCorpos.size())
        cout << "Erro setPosicao" << endl;
    else
        cout << "ErrogetDimensoesX" << endl;

}

float GerenciadorGrafico::getDimensoesY(int id)
{
    if (ListaCorpos[id] != NULL)
        return ListaCorpos[id]->getSize().y;
    else if (id < 0 || id >= ListaCorpos.size())
        cout << "Erro setPosicao" << endl;
    else
        cout << "ErrogetDimensoesY" << endl;

}

void GerenciadorGrafico::setPosicao(int id, float x, float y)
{

    if (id == NULL)
        cout << "Erro setPosicao" << endl;
    else if (id < 0 || id >= ListaCorpos.size())
        cout << "Erro setPosicao" << endl;
    else {
        
    }
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

void GerenciadorGrafico::setSubTextura(int id, string subtext)
{
    ListaCorpos[id]->setTextureRect(SubTexturas[subtext]);
}



void GerenciadorGrafico::desenhar(int id, bool desalocavel)
{
        //if (ListaCorpos[id] != NULL)
    if (desalocavel == false)
        Janela.draw(*ListaCorpos[id]);
    else
        delete (ListaCorpos[id]);
}

void GerenciadorGrafico::fechar()
{
    Janela.close();
}

void GerenciadorGrafico::movimenta(int id, float x, float y)
{

     if (ListaCorpos[id] != NULL)
         ListaCorpos[id]->move(sf::Vector2f(x, y));
}

void GerenciadorGrafico::TeclaApertada(char* direita, char* esquerda, char* pulo, char* atira)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        *direita = 'D';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        *esquerda = 'A';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        *pulo = 'W';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        *atira = ' ';
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (*direita == 'D')
            *direita = '>';
        else
            *direita = 'R';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (*esquerda == 'A')
            *esquerda = '<';
        else
            *esquerda = 'L';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (*pulo == 'W')
            *pulo = 'J';
        else
            *pulo = 'U';
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (*atira == ' ')
            *atira = 'S';
        else
            *atira = 'E';
    }
}

void GerenciadorGrafico::CarregaTextura(string textura)
{
    sf::Texture Textura;
    if (!Textura.loadFromFile(textura))
        cerr << "Erro. Nao foi possivel carregar a textura de uma Entidade." << endl;
    Texturas[textura] = Textura;
}

void GerenciadorGrafico::InicializaTexturas()
{
    //CarregaTextura("");
    CarregaTextura("textures/Fazendeira.png");
    CarregaTextura("textures/Bruxo.png");
    CarregaTextura("textures/Background.png");
    CarregaTextura("textures/Background_quarto.jpg");
    CarregaTextura("textures/Pseudo_Invisivel.png");
    CarregaTextura("textures/Plataforma_Quintal.png");
    CarregaTextura("textures/Plataforma_Quarto.png");
    CarregaTextura("textures/Monstro_Moita.png");
    CarregaTextura("textures/Monstro_Roupas.png");
    CarregaTextura("textures/Teia.png");
    CarregaTextura("textures/Espinhos_Galhos.png");
    CarregaTextura("textures/Espinhos_Materiais.png");
    CarregaTextura("textures/Passaro.png");
    CarregaTextura("textures/Fantasma.png");
    CarregaTextura("textures/Bicho_Papao.png");
    CarregaTextura("textures/Projeteis.png");
    CarregaTextura("textures/Inicio_Fim.png");

}


void GerenciadorGrafico::InicializaFontes()
{
    sf::Font Fonte;
    if (!Fonte.loadFromFile("arial.ttf"))
        cout << "Erro ao carregar fonte." << endl;
    Fontes["Arial"] = Fonte;

}

void GerenciadorGrafico::InicializaCores()
{
    Cores["Vermelho"] = sf::Color::Red;
    Cores["Verde"] = sf::Color::Green;
    Cores["Azul"] = sf::Color::Blue;
    Cores["Transparente"] = sf::Color::Transparent;

}

void GerenciadorGrafico::InicializaSubTexturas()
{
    SubTexturas["textures/Fazendeira.png"] = sf::IntRect(285, 0, 660, 820); SubTexturas["Fazendeira_2"] = sf::IntRect(1045, 0, 660, 820); SubTexturas["Fazendeira_3"] = sf::IntRect(1800, 0, 630, 820);
    SubTexturas["Fazendeira_4"] = sf::IntRect(2540, 0, 640, 820); SubTexturas["Fazendeira_5"] = sf::IntRect(3280, 0, 640, 820); SubTexturas["Fazendeira_6"] = sf::IntRect(4025, 0, 640, 820);
    SubTexturas["Fazendeira_7"] = sf::IntRect(0, 875, 640, 820); SubTexturas["Fazendeira_8"] = sf::IntRect(745, 875, 640, 820); SubTexturas["Fazendeira_9"] = sf::IntRect(1485, 875, 900, 820);
    SubTexturas["Fazendeira_10"] = sf::IntRect(2495, 875, 900, 820); SubTexturas["Fazendeira_11"] = sf::IntRect(3490, 820, 680, 820); SubTexturas["Fazendeira_12"] = sf::IntRect(4270, 820, 680, 820);

    SubTexturas["textures/Bruxo.png"] = sf::IntRect(145, 0, 530, 820); SubTexturas["Bruxo_2"] = sf::IntRect(820, 0, 530, 820); SubTexturas["Bruxo_3"] = sf::IntRect(1495, 0, 530, 820);
    SubTexturas["Bruxo_4"] = sf::IntRect(2130, 0, 530, 820); SubTexturas["Bruxo_5"] = sf::IntRect(2765, 0, 530, 820); SubTexturas["Bruxo_6"] = sf::IntRect(3405, 0, 530, 820);
    SubTexturas["Bruxo_7"] = sf::IntRect(0, 930, 480, 820); SubTexturas["Bruxo_8"] = sf::IntRect(630, 930, 480, 820); SubTexturas["Bruxo_9"] = sf::IntRect(1260, 930, 700, 820);
    SubTexturas["Bruxo_10"] = sf::IntRect(2100, 930, 700, 820); SubTexturas["Bruxo_11"] = sf::IntRect(2855, 950, 520, 820); SubTexturas["Bruxo_12"] = sf::IntRect(3460, 950, 520, 820);

    SubTexturas["textures/Plataforma_Quintal.png"] = sf::IntRect(0, 0, 620, 630); SubTexturas["Plataforma_Quintal_2"] = sf::IntRect(660, 0, 620, 630); SubTexturas["Plataforma_Quintal_3"] = sf::IntRect(1320, 10, 620, 630);
    SubTexturas["Plataforma_Quintal_4"] = sf::IntRect(1995, 0, 620, 630); SubTexturas["Plataforma_Quintal_5"] = sf::IntRect(2675, 0, 620, 630);

    SubTexturas["textures/Plataforma_Quarto.png"] = sf::IntRect(0, 0, 630, 650); SubTexturas["Plataforma_Quarto_2"] = sf::IntRect(725,10, 620, 630); SubTexturas["Plataforma_Quarto_3"] = sf::IntRect(1450, 10, 620, 630);
    SubTexturas["Plataforma_Quarto_4"] = sf::IntRect(2175, 10, 620, 630); SubTexturas["Plataforma_Quarto_5"] = sf::IntRect(2915, 10, 620, 630);

    SubTexturas["textures/Monstro_Moita.png"] = sf::IntRect(0, 140, 880, 480); SubTexturas["Monstro_Moita_2"] = sf::IntRect(880, 140, 880, 480); SubTexturas["Monstro_Moita_3"] = sf::IntRect(1770, 0, 1020, 620);
    SubTexturas["textures/Monstro_Roupas.png"] = sf::IntRect(0, 140, 880, 480); SubTexturas["Monstro_Roupas_2"] = sf::IntRect(880, 140, 880, 480); SubTexturas["Monstro_Roupas_3"] = sf::IntRect(1770, 0, 1020, 620);

    SubTexturas["textures/Teia.png"] = sf::IntRect(0, 0, 490, 490); SubTexturas["Teia_2"] = sf::IntRect(615, 0, 490, 490);

    SubTexturas["Espinhos_Galhos_2"] = sf::IntRect(0, 0, 760, 475); SubTexturas["textures/Espinhos_Galhos.png"] = sf::IntRect(870, 0, 760, 475);
    SubTexturas["Espinhos_Materiais_2"] = sf::IntRect(0, 0, 760, 475); SubTexturas["textures/Espinhos_Materiais.png"] = sf::IntRect(770, 0, 760, 475);

    SubTexturas["textures/Passaro.png"] = sf::IntRect(0, 0, 630, 525); SubTexturas["Passaro_2"] = sf::IntRect(750,  0, 630, 525);
    SubTexturas["Passaro_3"] = sf::IntRect(1475, 0, 630, 525); SubTexturas["Passaro_4"] = sf::IntRect(2220,  0, 630, 525);

    SubTexturas["textures/Fantasma.png"] = sf::IntRect(0, 0, 630, 500); SubTexturas["Fantasma_2"] = sf::IntRect(780, 0, 630, 500);

    SubTexturas["textures/Bicho_Papao.png"] = sf::IntRect(405, 10, 1565, 1580); SubTexturas["Bicho_Papao_2"] = sf::IntRect(2280, 0, 1565, 1580); SubTexturas["Bicho_Papao_3"] = sf::IntRect(4120, 10, 1280, 1725);
    SubTexturas["Bicho_Papao_4"] = sf::IntRect(5665, 10, 1565, 1580); SubTexturas["Bicho_Papao_5"] = sf::IntRect(7500, 0, 1565, 1580); SubTexturas["Bicho_Papao_6"] = sf::IntRect(9345, 0, 1280, 1725);;
    SubTexturas["Bicho_Papao_7"] = sf::IntRect(0, 290, 110, 130);

    SubTexturas["textures/Projeteis.png"] = sf::IntRect(0, 0, 126, 134); SubTexturas["Projeteis_2"] = sf::IntRect(170,  0, 126, 134); SubTexturas["Projeteis_3"] = sf::IntRect(340,  0, 156, 134);
    SubTexturas["Projeteis_4"] = sf::IntRect(535,  0, 155, 134); SubTexturas["Projeteis_5"] = sf::IntRect(735,  0, 140, 134); SubTexturas["Projeteis_6"] = sf::IntRect(918, 0, 140, 134);
    SubTexturas["Projeteis_7"] = sf::IntRect(1101, 0, 100, 134); SubTexturas["Projeteis_8"] = sf::IntRect(1240, 0, 140, 134); SubTexturas["Projeteis_9"] = sf::IntRect(1390, 0, 140, 134);

    SubTexturas["textures/Inicio_Fim.png"] = sf::IntRect(0, 500, 520, 580); SubTexturas["Inicio_Fim_2"] = sf::IntRect(820, 110, 835, 1360); SubTexturas["Inicio_Fim_3"] = sf::IntRect(1950, 135, 225, 1300);
    SubTexturas["Inicio_Fim_4"] = sf::IntRect(2475, 135, 225, 1300); SubTexturas["Inicio_Fim_5"] = sf::IntRect(3000, 0, 620, 1580);

    
}







