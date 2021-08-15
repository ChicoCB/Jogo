#include "GerenciadorGrafico.h"
#include "Jogo.h"

GerenciadorGrafico::GerenciadorGrafico() :
    Janela(sf::VideoMode(static_cast <unsigned int>(COMPRIMENTO_RESOLUCAO), static_cast <unsigned int>(ALTURA_RESOLUCAO)),
        "Jogo"/*, sf::Style::Fullscreen*/),
    View(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO / 2), sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO))
    //IdCorpoAtual(0)
{
    Janela.setView(View);

    cout << "Antes de bugar";

    InicializaTexturas();
    InicializaSubstexturas();
    InicializaFontes();
    InicializaCores();
}

void GerenciadorGrafico::LoopJogo(Jogo* jogo, int estado)
{
    sf::Clock Tempo;
    int Estado = estado;

    while (Janela.isOpen())
    {
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
    sf::Texture* Textura = new sf::Texture();

    sf::RectangleShape* Corpo = new sf::RectangleShape();

    Corpo->setSize(sf::Vector2f(dimx, dimy));
    Corpo->setPosition(sf::Vector2f(posx, posy));
    Corpo->setOrigin(dimx/2, dimy/2);
    Corpo->setTexture(&Texturas[text]);

    if (text == "textures/Fazendeira.png")
        Corpo->setTextureRect(SubTexturas["Fazendeira_4"]);
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

void GerenciadorGrafico::mudaAnimacao(int id, string frame)
{
    ListaCorpos[id]->setTextureRect(SubTexturas[frame]);
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

void GerenciadorGrafico::CarregaTextura(string textura)
{
    sf::Texture Textura;
    if (!Textura.loadFromFile(textura))
        cerr << "Erro. Nao foi possivel carregar a textura de uma Entidade." << endl;
    Texturas[textura] = Textura;
}

void GerenciadorGrafico::InicializaTexturas()
{
    CarregaTextura("");
    CarregaTextura("textures/Fazendeira.png");
    CarregaTextura("textures/Fazendeira_fila.png");
    CarregaTextura("textures/Bruxo.png");
    CarregaTextura("textures/Background.png");
    CarregaTextura("textures/Background_quarto.jpg");
    CarregaTextura("textures/Estante_meio.png");
    CarregaTextura("textures/Estatico_vulneravel.png");
    CarregaTextura("textures/Estatico_vulneravel_quarto.png");
    CarregaTextura("textures/Fantasma_direita.png");
    CarregaTextura("textures/Passaro_direita.png");
    CarregaTextura("textures/Plataforma_meio.png");
    CarregaTextura("textures/Pseudo_Invisivel.png");
    // CarregaTextura("textures/Fazendeira.png");
   //  CarregaTextura("textures/Fazendeira.png");

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

void GerenciadorGrafico::InicializaSubstexturas()
{
    SubTexturas["textures/Fazendeira.png"] = sf::IntRect(285, 0, 660, 820); SubTexturas["Fazendeira_2"] = sf::IntRect(1045, 0, 660, 820); SubTexturas["Fazendeira_3"] = sf::IntRect(1800, 0, 630, 820);
    SubTexturas["Fazendeira_4"] = sf::IntRect(2540, 0, 640, 820); SubTexturas["Fazendeira_5"] = sf::IntRect(3280, 0, 640, 820); SubTexturas["Fazendeira_6"] = sf::IntRect(4025, 0, 640, 820);
    SubTexturas["Fazendeira_7"] = sf::IntRect(0, 875, 640, 820); SubTexturas["Fazendeira_8"] = sf::IntRect(745, 875, 640, 820); SubTexturas["Fazendeira_9"] = sf::IntRect(1485, 875, 900, 820);
    SubTexturas["Fazendeira_10"] = sf::IntRect(2495, 875, 900, 820); SubTexturas["Fazendeira_11"] = sf::IntRect(3490, 820, 680, 820); SubTexturas["Fazendeira_12"] = sf::IntRect(4270, 820, 680, 820);

    SubTexturas["textures/Bruxo.png"] = sf::IntRect(145, 0, 530, 820); SubTexturas["Bruxo_2"] = sf::IntRect(820, 0, 530, 820); SubTexturas["Bruxo_3"] = sf::IntRect(1495, 0, 530, 820);
    SubTexturas["Bruxo_4"] = sf::IntRect(2130, 0, 530, 820); SubTexturas["Bruxo_5"] = sf::IntRect(2765, 0, 530, 820); SubTexturas["Bruxo_6"] = sf::IntRect(3405, 0, 530, 820);
    SubTexturas["Bruxo_7"] = sf::IntRect(0, 930, 480, 820); SubTexturas["Bruxo_8"] = sf::IntRect(630, 930, 480, 820); SubTexturas["Bruxo_9"] = sf::IntRect(1260, 930, 700, 820);
    SubTexturas["Bruxo_10"] = sf::IntRect(2100, 930, 700, 820); SubTexturas["Bruxo_11"] = sf::IntRect(2855, 950, 520, 820); SubTexturas["Bruxo_12"] = sf::IntRect(3460, 950, 520, 820);
}







