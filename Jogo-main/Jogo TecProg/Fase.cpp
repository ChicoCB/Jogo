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

void Fase::criaObstaculo(Entidade* pentidade, sf::Vector2f dimensao, sf::Vector2f posicao, const string textura)
{
	pentidade->setDimensoes(dimensao);
	pentidade->setPosicao(posicao);
	pentidade->setTextura(textura);

	pentidade->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*>(pentidade));
}

void Fase::criaInimigo(Personagem* ppersonagem, sf::Vector2f dimensao, sf::Vector2f posicao, const string textura)
{
	ppersonagem->setDimensoes(dimensao);
	ppersonagem->setPosicao(posicao);
	ppersonagem->setTextura(textura);

	ppersonagem->setGerenciadorGrafico(pGerenciadorGrafico);
	listaEntidades.inclua(static_cast <Entidade*>(ppersonagem));
	listaPersonagens.inclua(static_cast <Personagem*> (ppersonagem));

}

void Fase::criaBordas()
{
	Plataforma* chao = new Plataforma();
	criaObstaculo(chao, sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_PLATAFORMA),
		sf::Vector2f(COMPRIMENTO_CENARIO / 2, ALTURA_RESOLUCAO - ALTURA_PLATAFORMA / 2),
		"textures/Pseudo_Invisivel.png");

	Plataforma* esquerda = new Plataforma();
	criaObstaculo(esquerda, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO),
		sf::Vector2f(-COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2),
		"");
	Plataforma* direita = new Plataforma();
	criaObstaculo(direita, sf::Vector2f(COMPRIMENTO_PLATAFORMA, ALTURA_RESOLUCAO),
		sf::Vector2f(COMPRIMENTO_CENARIO + COMPRIMENTO_PLATAFORMA / 2, ALTURA_RESOLUCAO / 2),
		"");
}

void Fase::setChefaoMorreu(bool chefaomorreu)
{
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
	else if (pFazendeira->getPosicao().x > COMPRIMENTO_CENARIO - COMPRIMENTO_RESOLUCAO / 2)
		pGerenciadorGrafico->atualizaView(sf::Vector2f(COMPRIMENTO_CENARIO - COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO/2));
	else
		pGerenciadorGrafico->atualizaView(sf::Vector2f(COMPRIMENTO_RESOLUCAO / 2, ALTURA_RESOLUCAO/2));
}

void Fase::incluaProjetil(Projetil* projetil)
{
	cout << "Projetil incluso" << endl;
	listaEntidades.inclua(projetil);
}

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

void Fase::recuperarProjeteis(Fase* fase, const string textura)
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
		novo->setVelocidade(sf::Vector2f(velx, vely));
		novo->setPosicao(sf::Vector2f(posx, posy));
		novo->setDimensoes(sf::Vector2f(10.f, 10.f));
		novo->setAmigavel(amigavel);
		novo->setGerenciadorGrafico(pGerenciadorGrafico);
		novo->setTextura(textura);
		novo->setFaseAtual(fase);
		incluaProjetil(novo);
	}

	recuperadorProjeteis.close();
}

void Fase::recuperarEstaticos(const string textura)
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

		novo->setVida(vida);
		novo->setCooldownAtaque(cooldown);

		criaInimigo(static_cast <Personagem*> (novo), sf::Vector2f(COMPRIMENTO_ESTATICO, ALTURA_ESTATICO),
			sf::Vector2f(posx, posy), textura);
	}

	recuperadorEstaticos.close();
}

void Fase::recuperarEspinhos(const string textura)
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

		criaObstaculo(static_cast <Entidade*>(novo), sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO),
			sf::Vector2f(posx, posy), textura);
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

		criaObstaculo(static_cast <Entidade*>(novo), sf::Vector2f(COMPRIMENTO_TEIA, ALTURA_TEIA),
			sf::Vector2f(posx, posy), "");
	}

	recuperadorTeias.close();
}


