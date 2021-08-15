#include "MenuJogadores.h"
#include "Jogo.h"

MenuJogadores::MenuJogadores(  int tamanho, Jogo* jg):
	Menu(  tamanho, jg),
	LimiteBaixo(2),
	LimiteCima(0)
{
	Inicializa();
	
}

MenuJogadores::~MenuJogadores()
{
}

void MenuJogadores::LoopMenu(char tecla)
{
	
		if (tecla == 'w' || tecla == 'W')
			if (Indice > LimiteCima)
				moverCima();
		if (tecla == 's' || tecla == 'S')
			if (Indice < LimiteBaixo)
				moverBaixo();
		if (tecla == 13)
		{
			switch (Indice)
			{
			case 0:
				//jogo->setEstado(2);
				Textos[0].setCor("Transparente");
				Textos[1].setCor("Transparente");
				Textos[2].setCor("Transparente");
				Textos[3].setCor("Verde");
				Textos[4].setCor("Vermelho");
				Textos[5].setCor("Verde");
				Textos[6].setCor("Verde");
				LimiteCima = 4;
				LimiteBaixo = 6;
				Indice = 4;
				break;
			case 1:
				jogo->setMultiplayer(true);
				jogo->setEstado(2);
				break;
			case 2:
			{
				jogo->setEstado(0);
				moverCima();
				moverCima();
			}
			break;
			case 4:
				jogo->setJogador1Fazendeira(true);
				jogo->setEstado(2);
				break;
			case 5:
				jogo->setJogador1Fazendeira(false);
				jogo->setEstado(2);
				break;
			case 6:
				Textos[0].setCor("Vermelho");
				Textos[1].setCor("Verde");
				Textos[2].setCor("Verde");
				Textos[3].setCor("Transparente");
				Textos[4].setCor("Transparente");
				Textos[5].setCor("Transparente");
				Textos[6].setCor("Transparente");
				LimiteCima = 0;
				LimiteBaixo = 2;
				Indice = 0;
				break;
			}
		}
}

void MenuJogadores::Inicializa() {
	Textos = new Texto[Tamanho];
	Textos[0].setCor("Vermelho");
	Textos[0].setDimensao(24);
	Textos[0].setMensagem("1 Jogador");
	Textos[0].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 250);
	Textos[0].setFonte("Arial");

	Textos[1].setCor("Verde");
	Textos[1].setDimensao(24);
	Textos[1].setMensagem("2 Jogadores");
	Textos[1].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 350);
	Textos[1].setFonte("Arial");

	Textos[2].setCor("Verde");
	Textos[2].setDimensao(24);
	Textos[2].setMensagem("Voltar");
	Textos[2].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 450);
	Textos[2].setFonte("Arial");

	Textos[3].setCor("Transparente");
	Textos[3].setDimensao(24);
	Textos[3].setMensagem("Escolha com qual jogador jogar:");
	Textos[3].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 250);
	Textos[3].setFonte("Arial");

	Textos[4].setCor("Transparente");
	Textos[4].setDimensao(24);
	Textos[4].setMensagem("Fazendeira");
	Textos[4].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 350);
	Textos[4].setFonte("Arial");

	Textos[5].setCor("Transparente");
	Textos[5].setDimensao(24);
	Textos[5].setMensagem("Bruxo");
	Textos[5].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 400);
	Textos[5].setFonte("Arial");

	Textos[6].setCor("Transparente");
	Textos[6].setDimensao(24);
	Textos[6].setMensagem("Voltar");
	Textos[6].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 500);
	Textos[6].setFonte("Arial");

}
