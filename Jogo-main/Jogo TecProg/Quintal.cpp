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
	pView->setCenter(sf::Vector2f(COMPRIMENTO_RESOLUCAO/2, ALTURA_RESOLUCAO/2));

	srand(time(NULL));

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);

	listaEntidades.inclua(static_cast <Entidade*> (&Cenario));
	Cenario.setTextura("textures/Background.png");
	Cenario.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Cenario.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO/2));
	Cenario.setGerenciadorGrafico(pGerenciadorGrafico);

	criaPlataformas();

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		criaEspinho(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO-400)) + 200,
			ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_ESPINHO/2)));
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		criaTeia(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_TEIA / 2)));
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaPassaro(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_FANTASMA / 2));
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaEstatico(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO/2)),
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
	pView = NULL;
	pFazendeira = NULL;
	pBruxo = NULL;
	pJogo = NULL;
}

void Quintal::criaPassaro(sf::Vector2f posicao)
{
	Passaro* novo = NULL;
	novo = new Passaro();

	novo->setFaseAtual(this);
	novo->setPosicao(posicao);
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO));
	novo->setVida(3);
	novo->setVelocidade(200.f);
	novo->setTextura("textures/Passaro_direita.png");
	novo->setLimiteXEsq(posicao.x);
	novo->setLimiteXDir(posicao.x + 300.0f);
	novo->setGerenciadorGrafico(pGerenciadorGrafico);

	listaEntidades.inclua(static_cast <Entidade*> (novo));
	listaPersonagens.inclua(static_cast <Personagem*> (novo));
}


void Quintal::criaPlataformas()
{
	criaBordas();

	//Plataformas específicas
	for (int i = 0; i < 10; i++){

		criaPlataforma(sf::Vector2f(900.f + COMPRIMENTO_PLATAFORMA * i, 337.5f));
		criaPlataforma(sf::Vector2f(1500.f + COMPRIMENTO_PLATAFORMA*i, 337.5f));
		criaPlataforma(sf::Vector2f(500.f + COMPRIMENTO_PLATAFORMA*i, 517.5f));
		criaPlataforma(sf::Vector2f(1800.f + COMPRIMENTO_PLATAFORMA*i, 157.5f));
	}
	for (int i = 0; i < 5; i++)
		criaPlataforma(sf::Vector2f(2000.f + COMPRIMENTO_PLATAFORMA*i, 517.5f));

	criaPlataforma(sf::Vector2f(-COMPRIMENTO_PLATAFORMA/2, ALTURA_RESOLUCAO/2), "", sf::Vector2f(COMPRIMENTO_PLATAFORMA,ALTURA_RESOLUCAO));
	criaPlataforma(sf::Vector2f(COMPRIMENTO_CENARIO+COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2), "", sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO));
}

void Quintal::recuperar()
{	
	listaEntidades.inclua(static_cast<Entidade*> (&Cenario));
	criaPlataformas();
	Cenario.setTextura("textures/Background.png");
	Cenario.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Cenario.setPosicao(sf::Vector2f(COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2));
	Cenario.setGerenciadorGrafico(pGerenciadorGrafico);
	porta.setJogo(pJogo);
	porta.setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast<Entidade*> (&porta));

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);
	
	pJogo->InicializaQuarto();

	recuperarProjeteis();
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
		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setLimiteXDir(limxdir);
		novo->setLimiteXEsq(limxesq);
		novo->setCooldownAtaque(cooldown);
		novo->setVelocidade(200.f);
		novo->setGerenciadorGrafico(pGerenciadorGrafico);
		novo->setTextura("textures/Passaro_direita.png");
		novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO));
		novo->setFaseAtual(this);

		listaEntidades.inclua(static_cast<Entidade*>(novo));
		listaPersonagens.inclua(static_cast <Personagem*> (novo));
	}

	recuperadorPassaros.close();
}


