#include "Quintal.h"
#include "Jogo.h"

Quintal::Quintal() :
	Fase(),
	porta()
{
}

Quintal::~Quintal()
{
	this->limparTudo();
}

void Quintal::inicializa()
{
	pGerenciadorGrafico->atualizaView(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO / 2));

	srand(time(NULL));

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);

	listaEntidades.inclua(static_cast <Entidade*> (&Background));
	Background.setTextura("textures/Background.png");
	Background.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Background.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO/2));
	Background.setGerenciadorGrafico(pGerenciadorGrafico);

	criaPlataformas();

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		Espinho* espinho = new Espinho();
		criaObstaculo(static_cast <Entidade*>(espinho), sf::Vector2f(COMPRIMENTO_ESPINHO,ALTURA_ESPINHO),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200, 
				ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_ESPINHO / 2)), "");
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		Teia* teia = new Teia();
		criaObstaculo(static_cast <Entidade*>(teia), sf::Vector2f(COMPRIMENTO_TEIA, ALTURA_TEIA),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_TEIA / 2)), "");
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Passaro* passaro = new Passaro();
		passaro->setFaseAtual(this);
		criaInimigo(static_cast<Personagem*>(passaro), sf::Vector2f(COMPRIMENTO_PASSARO, ALTURA_PASSARO),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_PASSARO / 2),
			"textures/Passaro_direita.png");
		passaro->setLimites(passaro->getPosicao().x, passaro->getPosicao().x + 300.f);
	
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Estatico* estatico = new Estatico();
		criaInimigo(static_cast<Personagem*>(estatico), sf::Vector2f(COMPRIMENTO_ESTATICO, ALTURA_ESTATICO),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO / 2)),
			"textures/Estatico_vulneravel.png");
	}

	porta.setJogo(pJogo);
	porta.setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast<Entidade*> (&porta));

	listaEntidades.inclua(static_cast <Entidade*> (pFazendeira));
	listaPersonagens.inclua(static_cast <Personagem*> (pFazendeira));

	if (pJogo->getMultiplayer())
	{
		listaEntidades.inclua(static_cast <Entidade*> (pBruxo));
		listaPersonagens.inclua(static_cast <Personagem*> (pBruxo));
	}
}

void Quintal::atualiza(float deltaTempo)
{
	if (getFazendeira()->getDesalocavel())
		cout << "Fazendeira desalocavel true" << endl;

	listaPersonagens.limpar();
	listaEntidades.limpar();

	if (getFazendeira() == NULL)
		cout << "Fazendeira nula" << endl;

	atualizaView();

	gerenciadorColisoes.checaColisoes();

	listaEntidades.atualiza(deltaTempo);

	listaEntidades.desenhar();
}

void Quintal::limparTudo()
{
	listaPersonagens.limparTudo();
	listaEntidades.limparTudo();
	//pView = NULL;
	pFazendeira = NULL;
	pBruxo = NULL;
	pJogo = NULL;
}


void Quintal::criaPlataformas()
{
	criaBordas();
	//Plataformas específicas
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(900.f + COMPRIMENTO_PLATAFORMA * i, 337.5f),
			"textures/Plataforma_meio.png");
	}
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(1500.f + COMPRIMENTO_PLATAFORMA * i, 337.5f),
			"textures/Plataforma_meio.png");
	}
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(500.f + COMPRIMENTO_PLATAFORMA * i, 517.5f),
			"textures/Plataforma_meio.png");
	}
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(1800.f + COMPRIMENTO_PLATAFORMA * i, 157.5f),
			"textures/Plataforma_meio.png");
	}
	
	for (int i = 0; i < 5; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(2000.f + COMPRIMENTO_PLATAFORMA * i, 517.5f),
			"textures/Plataforma_meio.png");
	}
}

void Quintal::recuperar()
{	
	listaEntidades.inclua(static_cast<Entidade*> (&Background));
	criaPlataformas();
	Background.setTextura("textures/Background.png");
	Background.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Background.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2));
	Background.setGerenciadorGrafico(pGerenciadorGrafico);
	porta.setJogo(pJogo);
	porta.setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast<Entidade*> (&porta));

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);
	
	pJogo->InicializaQuarto();

	recuperarProjeteis(this);
	recuperarEspinhos();
	recuperarEstaticos();
	recuperarPassaros();
	recuperarTeias();

	pFazendeira->setFaseAtual(this);
	listaEntidades.inclua(static_cast<Entidade*>(pFazendeira));
	listaPersonagens.inclua(static_cast <Personagem*> (pFazendeira));

	if (pJogo->getMultiplayer()) {
		pBruxo->setFaseAtual(this);
		listaEntidades.inclua(static_cast<Entidade*>(pBruxo));
		listaPersonagens.inclua(static_cast <Personagem*> (pBruxo));
	}
	else
		pBruxo = NULL;
}

void Quintal::recuperarPassaros()
{
	ifstream recuperadorPassaros("saves/Passaros.dat", ios::in);

	if (!recuperadorPassaros)
		cout << "Erro Passaros." << endl;

	while (!recuperadorPassaros.eof())
	{
		Passaro* novo = NULL;
		int vida;
		float posx, posy, limxdir, limxesq, cooldown;

		recuperadorPassaros >> vida >> posx >> posy >> limxdir >> limxesq >> cooldown;

		novo = new Passaro();
		novo->setVida(vida);
		novo->setLimites(limxesq, limxdir);
		novo->setCooldownAtaque(cooldown);
		novo->setFaseAtual(this);

		criaInimigo(static_cast <Personagem*> (novo), sf::Vector2f(COMPRIMENTO_PASSARO, ALTURA_PASSARO),
			sf::Vector2f(posx, posy), "textures/Passaro_direita.png");
	}

	recuperadorPassaros.close();
}


