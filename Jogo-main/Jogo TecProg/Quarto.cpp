#include "Quarto.h"
#include "Jogo.h"

Quarto::Quarto() :
	Fase(), ChefaoMorreu(false)
{
}

Quarto::~Quarto()
{
	this->limparTudo();
}

void Quarto::inicializa()
{
	//pView->setCenter(sf::Vector2f(COMPRIMENTO_RESOLUCAO/2, ALTURA_RESOLUCAO/2));
	pGerenciadorGrafico->atualizaView(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO / 2));

	srand(time(NULL));

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);

	listaEntidades.inclua(static_cast <Entidade*> (&Background));

	Background.setTextura("textures/Background_quarto.jpg");
	Background.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Background.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2));
	Background.setGerenciadorGrafico(pGerenciadorGrafico);

	criaPlataformas();

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Fantasma* fantasma = new Fantasma();
		criaInimigo(static_cast<Personagem*>(fantasma), sf::Vector2f(COMPRIMENTO_FANTASMA, ALTURA_FANTASMA),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_FANTASMA / 2),
			"textures/Fantasma_direita.png");
		fantasma->setLimitesX(fantasma->getPosicao().x, fantasma->getPosicao().x +200.0f);
		
	}
	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Estatico* estatico = new Estatico();
		criaInimigo(static_cast<Personagem*>(estatico), sf::Vector2f(COMPRIMENTO_ESTATICO, ALTURA_ESTATICO),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO / 2)),
			"textures/Estatico_vulneravel_quarto.png");
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		Teia* teia = new Teia();
		criaObstaculo(static_cast <Entidade*>(teia), sf::Vector2f(COMPRIMENTO_TEIA, ALTURA_TEIA),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_TEIA / 2)), "");
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		Espinho* espinho = new Espinho();
		criaObstaculo(static_cast <Entidade*>(espinho), sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO),
			sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_ESPINHO / 2)), "");
	}
	
	//criaChefao(sf::Vector2f(2000.f,600.f));

	Chefao* chefao = NULL;
	chefao = new Chefao();
	chefao->setFaseAtual(this);
	criaInimigo(static_cast <Personagem*>(chefao), sf::Vector2f(COMPRIMENTO_CHEFAO, ALTURA_CHEFAO),
				sf::Vector2f(2000.f, 600.f), "");


	if (pFazendeira == NULL)
		cout << "Eh null" << endl;

	listaEntidades.inclua(static_cast <Entidade*> (pFazendeira));
	listaPersonagens.inclua(static_cast <Personagem*> (pFazendeira));
	if (pJogo->getMultiplayer())
	{
		listaEntidades.inclua(static_cast <Entidade*> (pBruxo));
		listaPersonagens.inclua(static_cast <Personagem*> (pBruxo));
	}

}

void Quarto::desenhar()
{
	listaEntidades.desenhar();
}

void Quarto::atualiza(float deltaTempo)
{
	listaPersonagens.limpar();
	listaEntidades.limpar();

	atualizaView();

	gerenciadorColisoes.checaColisoes();

	listaEntidades.atualiza(deltaTempo);

	if (ChefaoMorreu)
	{
		cout << "Sumonando porta." << endl;
		ChefaoMorreu = false;
		Porta* cabideiro;

		cabideiro = new Porta();

		cabideiro->setJogo(pJogo);
		cabideiro->setGerenciadorGrafico(pGerenciadorGrafico);
		
		listaEntidades.inclua(static_cast<Entidade*> (cabideiro));
	}

	desenhar();
}

void Quarto::limparTudo()
{
	listaPersonagens.limparTudo();
	listaEntidades.limparTudo();
	//pView = NULL;
	pFazendeira = NULL;
	pBruxo = NULL;
	pJogo = NULL;
}

void Quarto::recuperar()
{
	listaEntidades.inclua(static_cast<Entidade*> (&Background));

	criaPlataformas();
	Background.setTextura("textures/Background_quarto.jpg");
	Background.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Background.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2));
	Background.setGerenciadorGrafico(pGerenciadorGrafico);

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);
	recuperarProjeteis(this);
	recuperarEstaticos();
	recuperarFantasmas();
	recuperarTeias();
	recuperarEspinhos();
	recuperarChefao();

	pFazendeira->setFaseAtual(this);
	listaEntidades.inclua(static_cast<Entidade*>(pFazendeira));
	listaPersonagens.inclua(static_cast <Personagem*> (pFazendeira));
	if (pJogo->getMultiplayer()) {
		pBruxo->setFaseAtual(this);
		listaEntidades.inclua(static_cast<Entidade*>(pBruxo));
		listaPersonagens.inclua(static_cast <Personagem*> (pBruxo));
	}
	else
	{
		pBruxo = NULL;
	}

}

void Quarto::recuperarFantasmas()
{
	ifstream recuperadorFantasmas("saves/Fantasmas.dat", ios::in);

	if (!recuperadorFantasmas)
		cout << "Erro Fantasmas." << endl;

	while (!recuperadorFantasmas.eof())
	{
		Fantasma* novo = NULL;
		int vida;
		float posx, posy, limxdir, limxesq, cooldown;

		recuperadorFantasmas >> vida >> posx >> posy >> limxdir >> limxesq >> cooldown;

		novo = new Fantasma();
		novo->setVida(vida);
		novo->setLimitesX(limxesq, limxdir);
		novo->setCooldownAtaque(cooldown);

		criaInimigo(static_cast <Personagem*> (novo), sf::Vector2f(COMPRIMENTO_FANTASMA, ALTURA_FANTASMA),
			sf::Vector2f(posx, posy), "textures/Fantasma_direita.png");

	}

	recuperadorFantasmas.close();
}

void Quarto::recuperarChefao()
{
	ifstream recuperadorChefao("saves/Chefao.dat", ios::in);

	if (!recuperadorChefao)
		cout << "Erro Chefao." << endl;

	if (recuperadorChefao.eof())
		ChefaoMorreu = true;

	while (!recuperadorChefao.eof())
	{
		Chefao* novo = NULL;
		int vida;
		float posx, posy, cooldown;

		recuperadorChefao >> vida >> posx >> posy >> cooldown;

		novo = new Chefao();
		novo->setVida(vida);
		novo->setCooldownAtaque(cooldown);
		novo->setFaseAtual(this);

		criaInimigo(static_cast <Personagem*> (novo), sf::Vector2f(COMPRIMENTO_CHEFAO, ALTURA_CHEFAO),
			sf::Vector2f(posx, posy), "");

	}

}

void Quarto::setChefaoMorreu(bool chefaomorreu)
{
	ChefaoMorreu = chefaomorreu;
}

void Quarto::criaPlataformas()
{
	criaBordas();
	//Plataformas específicas
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(900.f + COMPRIMENTO_PLATAFORMA * i, 337.5f),
			"textures/Estante_meio.png");
	}
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(1500.f + COMPRIMENTO_PLATAFORMA * i, 337.5f),
			"textures/Estante_meio.png");
	}
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(500.f + COMPRIMENTO_PLATAFORMA * i, 517.5f),
			"textures/Estante_meio.png");
	}
	for (int i = 0; i < 10; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(1800.f + COMPRIMENTO_PLATAFORMA * i, 157.5f),
			"textures/Estante_meio.png");
	}

	for (int i = 0; i < 5; i++) {
		Plataforma* plataforma = new Plataforma();
		criaObstaculo(plataforma, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA),
			sf::Vector2f(2000.f + COMPRIMENTO_PLATAFORMA * i, 517.5f),
			"textures/Estante_meio.png");
	}
}

