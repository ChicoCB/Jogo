#include "MenuFases.h"
#include "Jogo.h"

MenuFases::MenuFases(  int tamanho, Jogo* jg):
	Menu( tamanho, jg)
{
	Textos = new Texto[Tamanho];
	Textos[0].setCor("Vermelho");
	Textos[0].setDimensao(24);
	Textos[0].setMensagem("Fase 1");
	Textos[0].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 250);
	Textos[0].setFonte("Arial");

	Textos[1].setCor("Verde");
	Textos[1].setDimensao(24);
	Textos[1].setMensagem("Fase 2");
	Textos[1].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 350);
	Textos[1].setFonte("Arial");

	Textos[2].setCor("Verde");
	Textos[2].setDimensao(24);
	Textos[2].setMensagem("Voltar");
	Textos[2].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 450);
	Textos[2].setFonte("Arial");
}

MenuFases::~MenuFases()
{
}

void MenuFases::LoopMenu(char tecla)
{

		if (tecla == 'w' || tecla == 'W')
			moverCima();
		if (tecla == 's' || tecla == 'S')
			moverBaixo();
		if (tecla == 13)
		{
			switch (Indice)
			{
			case 0:
				jogo->InicializaJogadores();
				jogo->InicializaFases();
				jogo->getJogador1()->setFaseAtual(&jogo->getQuintal());
				if (jogo->getMultiplayer())
					jogo->getJogador2()->setFaseAtual(&jogo->getQuintal());
				jogo->setEstado(4);
				break;
			case 1:
				jogo->InicializaJogadores();

				if (jogo->getMultiplayer())
					jogo->getJogador2()->setFaseAtual(&jogo->getQuarto());
				jogo->getJogador1()->setFaseAtual(&jogo->getQuarto());
				jogo->InicializaQuarto();
				jogo->setEstado(5);
				break;
			case 2:
			{
				jogo->setEstado(1);
				moverCima();
				moverCima();
			}
				break;
			}
		}
	
}
