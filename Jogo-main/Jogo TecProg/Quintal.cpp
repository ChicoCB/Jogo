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
	srand(time(NULL));

	pGerenciadorGrafico->atualizaView( COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO / 2 );

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);

	Background.setGerenciadorGrafico(pGerenciadorGrafico);
	pGerenciadorGrafico->criaCorpo(&Background, COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO,
		COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2, "textures/Background.png");
	listaEntidades.inclua(static_cast <Entidade*> (&Background));

	criaPlataformas();

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		Espinho* espinho = new Espinho();
		criaObstaculo(static_cast <Entidade*>(espinho),  COMPRIMENTO_ESPINHO,ALTURA_ESPINHO ,
			 rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200, 
				ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_ESPINHO / 2) , "");
	}

	for (int i = 0; i < rand() % 6 + 3; i++)
	{
		Teia* teia = new Teia();
		criaObstaculo(static_cast <Entidade*>(teia),  COMPRIMENTO_TEIA, ALTURA_TEIA ,
			 rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + ALTURA_TEIA / 2 ), "");
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Passaro* passaro = new Passaro();
		passaro->setFaseAtual(this);
		criaInimigo(static_cast<Personagem*>(passaro),  COMPRIMENTO_PASSARO, ALTURA_PASSARO ,
			 rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_PASSARO / 2 ,
			"textures/Passaro_direita.png");
		passaro->setLimites(passaro->getPosicaoX() , passaro->getPosicaoX() + 300.f);
	
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Estatico* estatico = new Estatico();
		criaInimigo(static_cast<Personagem*>(estatico),  COMPRIMENTO_ESTATICO, ALTURA_ESTATICO ,
			 rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
				rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO / 2  ),
			"textures/Estatico_vulneravel.png");
	}

	
	porta.setGerenciadorGrafico(pGerenciadorGrafico);
	pGerenciadorGrafico->criaCorpo(&porta, 50.f, 100.f, COMPRIMENTO_CENARIO - 150.f,
		ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + 50.f), "");
	porta.setJogo(pJogo);
	listaEntidades.inclua(static_cast<Entidade*> (&porta));

	listaEntidades.inclua(static_cast <Entidade*> (pJogador1));
	listaPersonagens.inclua(static_cast <Personagem*> (pJogador1));

	if (pJogo->getMultiplayer())
	{
		listaEntidades.inclua(static_cast <Entidade*> (pJogador2));
		listaPersonagens.inclua(static_cast <Personagem*> (pJogador2));
	}
}

void Quintal::atualiza(float deltaTempo)
{
	listaPersonagens.limpar();
	listaEntidades.limpar();

	if (getJogador1() == NULL)
		cout << "Jogador1 nula" << endl;

	atualizaView();

	gerenciadorColisoes.checaColisoes();

	listaEntidades.atualiza(deltaTempo);

	listaEntidades.desenhar();
}

void Quintal::limparTudo()
{
	listaPersonagens.limparTudo();
	listaEntidades.limparTudo();
	pJogador1 = NULL;
	pJogador2 = NULL;
	pJogo = NULL;
}
void Quintal::criaPlataforma(float posx, float posy)
{
	Plataforma* plataforma = new Plataforma();
	criaObstaculo(plataforma, COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA,
		posx, posy, "textures/Plataforma_meio.png");
}

void Quintal::criaPlataformas()
{
	criaBordas();
	//Plataformas específicas
	for (int i = 0; i < 10; i++) {
		criaPlataforma(900.f + COMPRIMENTO_PLATAFORMA * i, 337.5f);
	}
	for (int i = 0; i < 10; i++) {
		criaPlataforma(1500.f + COMPRIMENTO_PLATAFORMA * i, 337.5f);
	}
	for (int i = 0; i < 10; i++) {
		criaPlataforma(500.f + COMPRIMENTO_PLATAFORMA * i, 517.5f);
	}
	for (int i = 0; i < 10; i++) {
		criaPlataforma(1800.f + COMPRIMENTO_PLATAFORMA * i, 157.5f);
	}

	for (int i = 0; i < 5; i++) {
		criaPlataforma(2000.f + COMPRIMENTO_PLATAFORMA * i, 517.5f);
	}
}

void Quintal::recuperar()
{	
	Background.setGerenciadorGrafico(pGerenciadorGrafico);
	pGerenciadorGrafico->criaCorpo(&Background, COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO,
		COMPRIMENTO_RESOLUCAO, ALTURA_RESOLUCAO / 2, "textures/Background.png");
	listaEntidades.inclua(static_cast <Entidade*> (&Background));

	criaPlataformas();

	porta.setGerenciadorGrafico(pGerenciadorGrafico);
	pGerenciadorGrafico->criaCorpo(&porta, 50.f, 100.f, COMPRIMENTO_CENARIO - 150.f,
		ALTURA_RESOLUCAO - (ALTURA_PLATAFORMA + 50.f), "");
	porta.setJogo(pJogo);
	listaEntidades.inclua(static_cast<Entidade*> (&porta));

	gerenciadorColisoes.setListaEntidades(&listaEntidades);
	gerenciadorColisoes.setListaPersonagens(&listaPersonagens);
	
	pJogo->InicializaQuarto();

	recuperarProjeteis(this);
	recuperarEspinhos();
	recuperarEstaticos();
	recuperarPassaros();
	recuperarTeias();

	pJogador1->setFaseAtual(this);
	listaEntidades.inclua(static_cast<Entidade*>(pJogador1));
	listaPersonagens.inclua(static_cast <Personagem*> (pJogador1));

	if (pJogo->getMultiplayer()) {
		pJogador2->setFaseAtual(this);
		listaEntidades.inclua(static_cast<Entidade*>(pJogador2));
		listaPersonagens.inclua(static_cast <Personagem*> (pJogador2));
	}
	else
		pJogador2 = NULL;
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

		criaInimigo(static_cast <Personagem*> (novo),  COMPRIMENTO_PASSARO, ALTURA_PASSARO ,
			 posx, posy , "textures/Passaro_direita.png");
	}

	recuperadorPassaros.close();
}


