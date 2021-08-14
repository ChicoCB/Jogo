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

	listaEntidades.inclua(static_cast <Entidade*> (&Cenario));

	Cenario.setTextura("textures/Background_quarto.jpg");
	Cenario.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Cenario.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2));
	Cenario.setGerenciadorGrafico(pGerenciadorGrafico);

	criaPlataformas();

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaFantasma(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200, 
						rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_FANTASMA / 2));
	}
	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaEstatico(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO/2)),
			"textures/Estatico_vulneravel_quarto.png");
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		criaTeia(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_TEIA / 2)));
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		criaEspinho(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO-400)) + 200,
			ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_ESPINHO/2)));
	}
	
	criaChefao(sf::Vector2f(2000.f,600.f));

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
	listaEntidades.inclua(static_cast<Entidade*> (&Cenario));
	criaPlataformas();
	Cenario.setTextura("textures/Background_quarto.jpg");
	Cenario.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Cenario.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2));
	Cenario.setGerenciadorGrafico(pGerenciadorGrafico);

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);
	recuperarProjeteis();
	recuperarEstaticos();
	recuperarFantasmas();
	recuperarTeias();
	recuperarEspinhos();
	recuperarChefao();
	recuperarPorta();

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
		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setLimiteXDir(limxdir);
		novo->setLimiteXEsq(limxesq);
		novo->setCooldownAtaque(cooldown);
		novo->setVelocidade(200.f);
		novo->setGerenciadorGrafico(pGerenciadorGrafico);
		novo->setTextura("textures/Fantasma_direita.png");
		novo->setColidePlataforma(false);
		novo->setDimensoes(sf::Vector2f(COMPRIMENTO_FANTASMA, ALTURA_FANTASMA));

		listaEntidades.inclua(static_cast<Entidade*>(novo));
		listaPersonagens.inclua(static_cast <Personagem*> (novo));
	}

	recuperadorFantasmas.close();
}

void Quarto::recuperarChefao()
{
	ifstream recuperadorChefao("saves/Chefao.dat", ios::in);

	if (!recuperadorChefao)
		cout << "Erro Chefao." << endl;

	while (!recuperadorChefao.eof())
	{
		Chefao* novo = NULL;
		int vida;
		float posx, posy, cooldown;

		recuperadorChefao >> vida >> posx >> posy >> cooldown;

		novo = new Chefao();
		novo->setVida(vida);
		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setCooldownAtaque(cooldown);
		novo->setVelocidade(50.f);
		novo->setGerenciadorGrafico(pGerenciadorGrafico);
		novo->setTextura("");
		novo->setColidePlataforma(true);
		novo->setDimensoes(sf::Vector2f(COMPRIMENTO_CHEFAO, ALTURA_CHEFAO));
		novo->setFaseAtual(this);

		listaEntidades.inclua(static_cast<Entidade*>(novo));
		listaPersonagens.inclua(static_cast <Personagem*> (novo));
	}

	recuperadorChefao.close();
}

void Quarto::recuperarPorta()
{
	ifstream recuperadorPorta("saves/Porta.dat", ios::in);

	if (!recuperadorPorta)
		cout << "Erro Porta." << endl;

	while (!recuperadorPorta.eof())
	{
		Porta* novo = NULL;
		float posx, posy;

		recuperadorPorta >> posx >> posy;

		novo = new Porta();

		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setDimensoes(sf::Vector2f(50.0f, 100.0f));
		novo->setGerenciadorGrafico(pGerenciadorGrafico);
		novo->setJogo(pJogo);

		listaEntidades.inclua(static_cast <Entidade*>(novo));
	}
	recuperadorPorta.close();
}

void Quarto::setChefaoMorreu(bool chefaomorreu)
{
	ChefaoMorreu = chefaomorreu;
}

void Quarto::criaFantasma(sf::Vector2f posicao)
{
	Fantasma* novo = NULL;
	novo = new Fantasma();

	novo->setPosicao(posicao);
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_FANTASMA, ALTURA_FANTASMA));
	novo->setGerenciadorGrafico(pGerenciadorGrafico);
	novo->setTextura("textures/Fantasma_direita.png");
	novo->setLimiteXEsq(posicao.x);
	novo->setLimiteXDir(posicao.x + 200.0f);

	listaEntidades.inclua(static_cast <Entidade*>(novo));
	listaPersonagens.inclua(static_cast <Personagem*> (novo));

	novo->setColidePlataforma(false);
	novo->setVelocidade(200.f);
	novo->setVida(2);
}

void Quarto::criaChefao(sf::Vector2f posicao)
{
	Chefao* novo = NULL;
	novo = new Chefao();

	novo->setFaseAtual(this);
	novo->setPosicao(posicao);
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_CHEFAO, ALTURA_CHEFAO));
	novo->setVida(3);
	novo->setVelocidade(50.f);
	novo->setTextura("");
	novo->setColidePlataforma(true);
	novo->setGerenciadorGrafico(pGerenciadorGrafico);

	listaEntidades.inclua(static_cast <Entidade*> (novo));
	listaPersonagens.inclua(static_cast <Personagem*> (novo));
}

void Quarto::criaPlataformas()
{
	for (int i = 0; i < 10; i++)
	{

		criaPlataforma(sf::Vector2f(900.f + COMPRIMENTO_PLATAFORMA * i, 337.5f), "textures/Estante_meio.png");
		criaPlataforma(sf::Vector2f(1500.f + COMPRIMENTO_PLATAFORMA * i, 337.5f), "textures/Estante_meio.png");
		criaPlataforma(sf::Vector2f(500.f + COMPRIMENTO_PLATAFORMA * i, 517.5f), "textures/Estante_meio.png");
		criaPlataforma(sf::Vector2f(1800.f + COMPRIMENTO_PLATAFORMA * i, 157.5f), "textures/Estante_meio.png");
	}

	for (int i = 0; i < 5; i++)
		criaPlataforma(sf::Vector2f(2000.f + COMPRIMENTO_PLATAFORMA * i, 517.5f), "textures/Estante_meio.png");

	criaBordas();
	criaPlataforma(sf::Vector2f(-COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2), "", sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO));
	criaPlataforma(sf::Vector2f(COMPRIMENTO_CENARIO + COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2), "", sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO));
}

