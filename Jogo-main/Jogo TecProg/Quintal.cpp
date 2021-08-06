#include "Quintal.h"

Quintal::Quintal() :
	porta()
{
}

Quintal::~Quintal()
{
}

void Quintal::inicializa()
{
	srand(time(NULL));

	listaEntidades.inclua(static_cast <Entidade*> (&Cenario));
	//gerenciadorFisica.setListaEntidades(&listaEntidades);
	
	Fazendeira.inicializa();
	Fazendeira.setJanela(Janela);
	Fazendeira.setFaseAtual(this);
	Fazendeira.setDimensoes(sf::Vector2f(COMPRIMENTO_JOGADOR, ALTURA_JOGADOR));
	Fazendeira.setOrigem();
	Fazendeira.setPosicao(sf::Vector2f(640.f, 320.f));
	Fazendeira.setTextura("textures/Fazendeira.png");
	Fazendeira.setTeclas(sf::Keyboard::D, sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::Space);
	Fazendeira.setVelocidade(400.f);
	Fazendeira.setAlturaPulo(250.f);
	gerenciadorFisica.setFazendeira(&Fazendeira);
	gerenciadorFisica.incluaPersonagem(&Fazendeira);

	Cenario.setJanela(Janela);
	Cenario.setTextura("textures/Background.png");
	Cenario.setDimensoes(sf::Vector2f(COMPRIMENTO_CENARIO, ALTURA_RESOLUCAO));
	Cenario.setPosicao(sf::Vector2f(0.f, 0.f));

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

	/*
	/for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaFantasma(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200, 
						rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_FANTASMA / 2));
	}
	*/

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaPassaro(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			rand() % static_cast<int>(ALTURA_RESOLUCAO / 2) + ALTURA_FANTASMA / 2));
	}

	for (int i = 0; i < rand() % 4 + 3; i++)
	{
		criaEstatico(sf::Vector2f(rand() % (static_cast<int>(COMPRIMENTO_CENARIO - 400)) + 200,
			rand() % static_cast<int>(ALTURA_RESOLUCAO) - (ALTURA_PLATAFORMA + ALTURA_ESTATICO/2)));
	}

	porta.setJanela(Janela);
	porta.setJogo(jogo);
	listaEntidades.inclua(static_cast<Entidade*> (&porta));
	gerenciadorFisica.incluaEntidade(static_cast<Entidade*> (&porta));

	listaEntidades.inclua(static_cast <Entidade*> (&Fazendeira));
}

void Quintal::desenhar()
{
	listaEntidades.desenhar();
}

void Quintal::atualiza(float deltaTempo)
{
	atualizaView();

	gerenciadorFisica.checaColisoes();

	listaEntidades.atualiza(deltaTempo);

	desenhar();
}

void Quintal::criaPassaro(sf::Vector2f posicao)
{
	Passaro* novo = NULL;
	novo = new Passaro();

	novo->setFaseAtual(this);
	novo->setPosicao(posicao);
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_ESPINHO, ALTURA_ESPINHO));
	novo->setOrigem();
	novo->inicializa();
	novo->setVida(3);
	novo->setVelocidade(200.f);
	novo->setJanela(Janela);
	novo->setTextura("textures/Passaro_direita.png");
	novo->setColidePlataforma(true);

	//ListaPassaros.push_back(novo);
	listaEntidades.inclua(static_cast <Entidade*> (novo));
	gerenciadorFisica.incluaPersonagem(novo);
	gerenciadorFisica.incluaEntidade(static_cast <Entidade*>(novo));
}

/*
void Quintal::criaFantasma(sf::Vector2f posicao)
{
	Fantasma* novo = NULL;
	novo = new Fantasma();

	novo->setPosicao(posicao);
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_FANTASMA,ALTURA_FANTASMA));
	novo->setOrigem();
	novo->setJanela(Janela);
	novo->setTextura("textures/Fantasma_direita.png");

	//ListaFantasmas.push_back(novo);
	listaEntidades.inclua(static_cast <Entidade*>(novo));
	gerenciadorFisica.incluaEntidade(static_cast <Entidade*>(novo));
	gerenciadorFisica.incluaPersonagem(novo);

	novo->setColidePlataforma(false);
	novo->inicializa();
	novo->setVelocidade(200.f);
	novo->setVida(4);
}
*/

void Quintal::criaTeia(sf::Vector2f posicao)
{
	Teia* novo = NULL;
	novo = new Teia();

	//Setar posi��o aleatoriamente
	novo->setPosicao(posicao);
	novo->setDimensoes(sf::Vector2f(COMPRIMENTO_TEIA, ALTURA_TEIA));
	novo->setOrigem();
	novo->setJanela(Janela);
	novo->setTextura("");
	//novo->setLentidao(0.9f);

	//ListaTeias.push_back(novo);
	listaEntidades.inclua(static_cast <Entidade*>(novo));
	//listaObstaculos.push_back(static_cast<Obstaculo*>(novo));
	gerenciadorFisica.incluaEntidade(static_cast <Entidade*>(novo));
}

void Quintal::criaPlataformas(){

	//Plataforma principal de baixo.
	criaChao();

	//Plataformas espec�ficas
	for (int i = 0; i < 10; i++){

		criaPlataforma(sf::Vector2f(900.f + COMPRIMENTO_PLATAFORMA * i, 337.5f));
		criaPlataforma(sf::Vector2f(1500.f + COMPRIMENTO_PLATAFORMA*i, 337.5f));
		criaPlataforma(sf::Vector2f(500.f + COMPRIMENTO_PLATAFORMA*i, 517.5f));
		criaPlataforma(sf::Vector2f(1800.f + COMPRIMENTO_PLATAFORMA*i, 157.5f));
		//criaPlataforma(sf::Vector2f(1800.f + COMPRIMENTO_PLATAFORMA*i, 1.f*(ALTURA_RESOLUCAO/4.f - ALTURA_PLATAFORMA)/4.f + 0.f*ALTURA_PLATAFORMA + ALTURA_PLATAFORMA/2.f));

	}
	for (int i = 0; i < 5; i++){
		criaPlataforma(sf::Vector2f(2000.f + COMPRIMENTO_PLATAFORMA*i, 517.5f));
		//criaPlataforma(sf::Vector2f(2000.f + COMPRIMENTO_PLATAFORMA * i, 2.f*(ALTURA_RESOLUCAO/4.f - ALTURA_PLATAFORMA)/4.f + 1.f*ALTURA_PLATAFORMA + ALTURA_PLATAFORMA/2.f));
	}
}
