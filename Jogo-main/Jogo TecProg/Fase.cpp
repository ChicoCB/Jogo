#include "Fase.h"
#include "Jogo.h"
#include "Jogador.h"

Fase::Fase():
	Ente(),
	//pView(NULL),
	pFazendeira(NULL),
	pBruxo(NULL),
	pJogo(NULL)
{
}

Fase::~Fase()
{
}

void Fase::criaPlataforma(sf::Vector2f posicao, const string textura)
{
	Plataforma* nova = NULL;
	nova = new Plataforma();
	nova->setDimensoes(sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_PLATAFORMA));
	nova->setPosicao(posicao);
	//nova->setOrigem();
	nova->setTextura(textura);
	nova->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*> (nova));
}

void Fase::criaPlataforma(sf::Vector2f posicao, const string textura, sf::Vector2f tamanho)
{
	Plataforma* nova = NULL;
	nova = new Plataforma();
	nova->setDimensoes(sf::Vector2f(tamanho));
	nova->setPosicao(posicao);
	//nova->setOrigem();
	nova->setTextura(textura);
	nova->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*> (nova));
}

void Fase::criaBordas()
{
	Plataforma* nova = NULL;
	nova = new Plataforma();
	nova->getCorpo().setFillColor(sf::Color::Transparent);
	nova->setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_PLATAFORMA));
	nova->setPosicao(sf::Vector2f(COMPRIMENTO_CENARIO / 2, ALTURA_RESOLUCAO - ALTURA_PLATAFORMA / 2));
	nova->setGerenciadorGrafico(pGerenciadorGrafico);

	listaEntidades.inclua(static_cast <Entidade*> (nova));

	criaPlataforma(sf::Vector2f(-COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2), "textures/Plataforma_meio.png", sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO));
	criaPlataforma(sf::Vector2f(COMPRIMENTO_CENARIO + COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2), "", sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO));
}

void Fase::criaEspinho(sf::Vector2f posicao, const string textura)
{
	Espinho* novo = NULL; 
	novo = new Espinho();

	//Passar por parâmetro na função e cria genericamente
	novo->setPosicao(posicao);
	novo->setTextura(textura);

	//Construtora bastaria
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO));

	//Genérico de todo obstáculo
	novo->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*>(novo));
}

void Fase::criaTeia(sf::Vector2f posicao, const string textura)
{
	Teia* novo = NULL;
	novo = new Teia();

	//Passar por parâmetro na função e cria genericamente
	novo->setPosicao(posicao);
	novo->setTextura("");

	//Construtora bastaria
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_TEIA, ALTURA_TEIA));

	//Genérico de todo obstáculo
	novo->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*>(novo));
}

void Fase::setChefaoMorreu(bool chefaomorreu)
{
}

/*
	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		Estatico* novo = NULL;
		novo = new Estatico();
		criaInimigo(novo, sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO/2)),
			"textures/Estatico_vulneravel.png");
	}
*/

void Fase::criaEstatico(sf::Vector2f posicao, const string textura)
{
	Estatico* novo = NULL;
	novo = new Estatico();

	//Passar por parâmetro na função e cria genericamente
	novo->setPosicao(posicao);
	novo->setTextura(textura);

	//Construtora bastaria
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESTATICO, ALTURA_ESTATICO));
	novo->setVida(4);
	novo->setVelocidade(100.f);

	//Genérico de todo personagem
	novo->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*> (novo));
	listaPersonagens.inclua(static_cast <Personagem*> (novo));
}

Jogador* Fase::getFazendeira()
{
	return pFazendeira;
}

void Fase::setFazendeira(Jogador* fazendeira)
{
	pFazendeira = fazendeira;
}

void Fase::setBruxo(Jogador* bruxo)
{
	pBruxo = bruxo;
}

void Fase::atualizaView()
{
	if (pFazendeira->getPosicao().x > COMPRIMENTO_RESOLUCAO / 2 && pFazendeira->getPosicao().x < COMPRIMENTO_CENARIO - COMPRIMENTO_RESOLUCAO / 2)
		pGerenciadorGrafico->atualizaView(sf::Vector2f(pFazendeira->getPosicao().x, ALTURA_RESOLUCAO/2));
		//pView->setCenter(sf::Vector2f(pFazendeira->getPosicao().x, ALTURA_RESOLUCAO/2));
	else if (pFazendeira->getPosicao().x > COMPRIMENTO_CENARIO - COMPRIMENTO_RESOLUCAO / 2)
		pGerenciadorGrafico->atualizaView(sf::Vector2f(COMPRIMENTO_CENARIO - COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO/2));
		//pView->setCenter(sf::Vector2f(COMPRIMENTO_CENARIO - COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO/2));
	else
		pGerenciadorGrafico->atualizaView(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO/2));
		//pView->setCenter(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO/2));
}

void Fase::incluaProjetil(Projetil* projetil)
{
	listaEntidades.inclua(projetil);
}

/*
void Fase::setView(sf::View* view)
{
	pView = view;
}
*/


void Fase::setJogo(Jogo* jg)
{
	pJogo = jg;
}

Jogo* Fase::getJogo()
{
	return pJogo;
}

void Fase::salvar()
{
	listaEntidades.salvar();
}

void Fase::recuperarProjeteis()
{
	ifstream recuperadorProjeteis("saves/Projeteis.dat", ios::in);

	if (!recuperadorProjeteis)
		cout << "Erro Projeteis." << endl;

	while (!recuperadorProjeteis.eof())
	{
		Projetil* novo = NULL;
		float posx, posy, velx, vely;
		bool amigavel;

		recuperadorProjeteis >> posx >> posy >> velx >> vely >> amigavel;

		novo = new Projetil();

		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setVelocidade(sf::Vector2f(velx, vely));
		novo->setDimensoes(sf::Vector2f(10.f, 10.f));
		novo->setAmigavel(amigavel);
		novo->setGerenciadorGrafico(pGerenciadorGrafico);

		incluaProjetil(novo);
	}

	recuperadorProjeteis.close();
}

void Fase::recuperarEstaticos()
{
	ifstream recuperadorEstaticos("saves/Estaticos.dat", ios::in);

	if (!recuperadorEstaticos)
		cout << "Erro Estaticos." << endl;

	while (!recuperadorEstaticos.eof())
	{
		Estatico* novo = NULL;
		int vida;
		float posx, posy, cooldown;

		recuperadorEstaticos >> vida >> posx >> posy >> cooldown;

		novo = new Estatico();

		novo->setPosicao(sf::Vector2f(posx,posy));
		novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESTATICO, ALTURA_ESTATICO));
		novo->setVida(vida);
		novo->setVelocidade(100.f);
		novo->setGerenciadorGrafico(pGerenciadorGrafico);
		novo->setTextura("textures/Estatico_vulneravel.png");
		novo->setCooldownAtaque(cooldown);

		listaEntidades.inclua(static_cast <Entidade*> (novo));
		listaPersonagens.inclua(static_cast <Personagem*> (novo));
	}

	recuperadorEstaticos.close();
}

void Fase::recuperarEspinhos()
{
	ifstream recuperadorEspinhos("saves/Espinhos.dat", ios::in);

	if (!recuperadorEspinhos)
		cout << "Erro Espinhos." << endl;

	while (!recuperadorEspinhos.eof())
	{
		Espinho* novo = NULL;
		float posx, posy;

		recuperadorEspinhos >> posx >> posy;

		novo = new Espinho();

		novo->setPosicao(sf::Vector2f(posx,posy));
		novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO));
		novo->setGerenciadorGrafico(pGerenciadorGrafico);

		listaEntidades.inclua(static_cast <Entidade*>(novo));
	}

	recuperadorEspinhos.close();
}

void Fase::recuperarTeias()
{
	ifstream recuperadorTeias("saves/Teias.dat", ios::in);

	if (!recuperadorTeias)
		cout << "Erro Teias." << endl;

	while (!recuperadorTeias.eof())
	{
		Teia* novo = NULL;
		float posx, posy;

		recuperadorTeias >> posx >> posy;

		novo = new Teia();

		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setDimensoes(sf::Vector2f(COMPRIMENTO_TEIA, ALTURA_TEIA));
		novo->setGerenciadorGrafico(pGerenciadorGrafico);

		listaEntidades.inclua(static_cast <Entidade*>(novo));
	}

	recuperadorTeias.close();
}


