#include "Jogador.h"
#include "Fase.h"

int Jogador::Pontuacao = 0;

Jogador::Jogador():Personagem()
{
}

Jogador::~Jogador()
{
}

/*
void Jogador::setPontuacao(int pontuacao)
{
	Pontuacao = pontuacao;
}

int Jogador::getPontuacao()
{
	return Pontuacao;
}
*/

void Jogador::incrementaPontuacao()
{
	Pontuacao += 10;
}

int Jogador::getPontuacao()
{
	return Pontuacao;
}

void Jogador::inicializa()
{
	Pontuacao = 0;
	CooldownAtaque = 0.f;
	CooldownAtaqueMax = 0.5f;
	Amigavel = true;
	colidePlataforma = true;
	Neutralizavel = true;
	CooldownInvencibilidade = 0;
	CooldownInvencibilidadeMax = -1;
}

void Jogador::colidir()
{
}

void Jogador::atualiza(float deltaTempo)
{
	Movimento.x = 0.f;

	if (sf::Keyboard::isKeyPressed(Direita))
	{
		Movimento.x += Velocidade;
		olharDireita = true;
	}
	if (sf::Keyboard::isKeyPressed(Esquerda))
	{
		Movimento.x -= Velocidade;
		olharDireita = false;
	}
	if (podePular && sf::Keyboard::isKeyPressed(Pulo))
	{
		podePular = false;
		Movimento.y = -sqrt(2 * 981.f * alturaPulo);
	}
	if (sf::Keyboard::isKeyPressed(Atira) && this->podeAtacar())
	{
		atiraProjetil();
	}

	Movimento.y += 981.f * deltaTempo;
	CooldownAtaque += deltaTempo;

	this->movimenta(Movimento * deltaTempo);
}

void Jogador::setTeclas(sf::Keyboard::Key direita, sf::Keyboard::Key esquerda, sf::Keyboard::Key pulo, sf::Keyboard::Key atira)
{
	Direita = direita;
	Esquerda = esquerda;
	Pulo = pulo;
	Atira = atira;
}

void Jogador::setFaseAtual(Fase* faseatual)
{
	faseAtual = faseatual;
}

void Jogador::atiraProjetil()
{
	Projetil* novo = NULL;
	
	
	//if (faseAtual->getPiscinaProjeteis().empty()) 
		novo = new Projetil();
	/*else 
	{
		novo = faseAtual->getPiscinaProjeteis().back();
		faseAtual->getPiscinaProjeteis().pop_back();
	}
	*/

	if (olharDireita)
	{
		novo->setPosicao(sf::Vector2f(this->getPosicao().x + this->getDimensoes().x / 2, this->getPosicao().y));
		novo->setVelocidade(sf::Vector2f(800.f, 0.f));
	}
	else
	{
		novo->setPosicao(sf::Vector2f(this->getPosicao().x - this->getDimensoes().x / 2, this->getPosicao().y));
		novo->setVelocidade(sf::Vector2f(-800.f, 0.f));
	}
	novo->setDimensoes(sf::Vector2f(10.f, 10.f));
	novo->setOrigem();
	novo->setJanela(Janela);
	novo->setAmigavel(true);
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);
	//novo->setNaPiscina(false);

	//cout << "x: " << novo->getVelocidade().x << endl;

	//if (faseAtual->getPiscinaProjeteis().empty())
		faseAtual->incluaProjetil(novo); //Incluído na fase
}

void Jogador::salvar()
{
		ofstream gravadorJogador("saves/Jogadores.dat", ios::app);

		if (!gravadorJogador)
			cout << "Erro." << endl;

		gravadorJogador << this->getVida() << ' '
			<< this->getPosicao().x << ' '
			<< this->getPosicao().y << ' '
			<< this->getMovimento().x << ' '
			<< this->getMovimento().y << ' '
			<< this->CooldownAtaque << endl;

		gravadorJogador.close();
}


