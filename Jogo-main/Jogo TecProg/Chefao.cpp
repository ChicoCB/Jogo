#include "Chefao.h"
#include "Fase.h"

Chefao::Chefao(): Inimigo(), Atirador()
{
	CooldownAtaqueMax = 1;
}

Chefao::~Chefao()
{
}

void Chefao::colidir(Personagem* personagem)
{
	if (personagem->getAmigavel())
	{
		cout << "Colidiu chefao" << endl;
		personagem->setVida(0);
		personagem->setDesalocavel(true);
	}
}

void Chefao::inicializa()
{
}

/*
void Chefao::setFaseAtual(Fase* faseatual)
{
	faseAtual = faseatual;
}

*/

void Chefao::atualiza(float deltaTempo)
{
	if (Desalocavel)
		faseAtual->setChefaoMorreu(true);

	Movimento = sf::Vector2f(0.f, 0.f);

	float deltax = faseAtual->getFazendeira()->getPosicao().x - this->getPosicao().x;
	float modulo = sqrt(deltax*deltax);

	if (modulo != 0.f)
		Movimento.x += Velocidade * deltax / modulo;
	Movimento.y += 981.f * deltaTempo;
	
	if (Movimento.x > 0)
		olharDireita = true;
	else
		olharDireita = false;

	CooldownAtaque += deltaTempo;

	if (this->podeAtacar())
	{
		this->atiraProjeteis();
		CooldownAtaque = 0;
	}

	this->movimenta(Movimento * deltaTempo);
}

/*
void Chefao::atiraProjetil(float altura)
{
	Projetil* novo = NULL;

	novo = new Projetil();

	if (olharDireita)
	{
		novo->setPosicao(sf::Vector2f(this->getPosicao().x + this->getDimensoes().x / 2, altura));
		novo->setVelocidade(sf::Vector2f(600.f, 0.f));
	}
	else
	{
		novo->setPosicao(sf::Vector2f(this->getPosicao().x - this->getDimensoes().x / 2, altura));
		novo->setVelocidade(sf::Vector2f(-600.f, 0.f));
	}
	novo->setDimensoes(sf::Vector2f(10.f, 10.f));
	novo->setOrigem();
	novo->setJanela(Janela);
	novo->setAmigavel(false);
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase
}

void Chefao::atiraProjetil2()
{
	Projetil* novo = NULL;

	novo = new Projetil();

	float deltax = faseAtual->getFazendeira()->getPosicao().x - this->getPosicao().x;
	float deltay = faseAtual->getFazendeira()->getPosicao().y - this->getPosicao().y;
	float modulo = sqrt(deltax * deltax + deltay * deltay);

	novo->setPosicao(sf::Vector2f(this->getPosicao().x, this->getPosicao().y));
	novo->setVelocidade(sf::Vector2f(400.f * deltax / modulo, 400.f * deltay / modulo));

	novo->setDimensoes(sf::Vector2f(20.f, 20.f));
	novo->setOrigem();
	novo->setJanela(Janela);
	novo->setAmigavel(false);
	novo->setDesalocavel(false);
	novo->setFaseAtual(faseAtual);

	faseAtual->incluaProjetil(novo); //Incluído na fase

}
*/


void Chefao::atiraProjeteis()
{
	atiraProjetilHorizontal(this, getPosicao().y);
	atiraProjetilHorizontal(this, getPosicao().y +  getDimensoes().y/2);
	atiraProjetilHorizontal(this, getPosicao().y - getDimensoes().y/2);
	atiraProjetilDirecionado(this, 20.0f);
	/*
	atiraProjetil2();
	atiraProjetil(this->getPosicao().y + this->getDimensoes().y / 2);
	atiraProjetil(this->getPosicao().y);
	atiraProjetil(this->getPosicao().y - this->getDimensoes().y / 2);
	*/

}

void Chefao::salvar()
{
	if (!this->getDesalocavel())
	{
		ofstream gravadorChefao("saves/Chefao.dat", ios::app);

		if (!gravadorChefao)
			cout << "Erro." << endl;

		gravadorChefao << this->getVida() << ' '
			<< this->getPosicao().x << ' '
			<< this->getPosicao().y << ' '
			<< this->CooldownAtaque << endl;

		gravadorChefao.close();
	}
}
