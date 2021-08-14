#include "Jogador.h"
#include "Fase.h"
#include "Jogo.h"

int Jogador::Pontuacao = 0;

Jogador::Jogador():
	Personagem(),
	podePular(true),
	alturaPulo(150.f)
{
	Amigavel = true;
	Vida = 1000;
	CooldownAtaqueMax = 0.5f;
}

Jogador::~Jogador()
{
}

void Jogador::setPodePular(bool podepular)
{
	podePular = podepular;
}

void Jogador::setAlturaPulo(float alturapulo)
{
	alturaPulo = alturapulo;
}

void Jogador::incrementaPontuacao()
{
	Pontuacao += 10;
}

int Jogador::getPontuacao()
{
	return Pontuacao;
}

void Jogador::atualiza(float deltaTempo)
{
	if (Desalocavel)
	{
		Desalocavel = false;
		faseAtual->getJogo()->setEstado(7);
	}

	Movimento.x = 0.f;

	if (podePular)
		Velocidade = 400.f;

	char TeclaDireita, TeclaEsquerda, TeclaPulo, TeclaAtira;

	pGerenciadorGrafico->TeclaApertada(&TeclaDireita, &TeclaEsquerda, &TeclaPulo, &TeclaAtira);

	if (TeclaDireita == Direita || TeclaDireita == '>')
	{
		Movimento.x += Velocidade;
		olharDireita = true;
	}
	if (TeclaEsquerda == Esquerda || TeclaEsquerda == '<')
	{
		Movimento.x -= Velocidade;
		olharDireita = false;
	}
	if (podePular && (TeclaPulo == Pulo || TeclaPulo == 'J'))
	{
		podePular = false;
		Movimento.y = -sqrt(2 * 981.f * alturaPulo);
	}
	if ((TeclaAtira == Atira || TeclaAtira == 'S') && this->podeAtacar())
	{
		this->atiraProjetilHorizontal(this, getPosicao().y);
		CooldownAtaque = 0;
	}


	Movimento.y += 981.f * deltaTempo;
	CooldownAtaque += deltaTempo;

	this->movimenta(Movimento * deltaTempo);
}

void Jogador::setTeclas(char direita, char esquerda, char pulo, char atira)
{
	Direita = direita;
	Esquerda = esquerda;
	Pulo = pulo;
	Atira = atira;
}

void Jogador::salvar()
{
	ofstream gravadorJogador("saves/Jogadores.dat", ios::app);

	if (!gravadorJogador)
		cout << "Erro Gravar Jogadores." << endl;

	gravadorJogador << this->getVida() << ' '
		<< this->getPosicao().x << ' '
		<< this->getPosicao().y << ' '
		<< this->getMovimento().x << ' '
		<< this->getMovimento().y << ' '
		<< this->CooldownAtaque << endl;

	gravadorJogador.close();
}


