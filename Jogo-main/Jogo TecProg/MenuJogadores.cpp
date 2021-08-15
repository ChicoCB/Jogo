#include "MenuJogadores.h"
#include "Jogo.h"

MenuJogadores::MenuJogadores(  int tamanho, Jogo* jg):
	Menu(  tamanho, jg)
{
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
	
}

MenuJogadores::~MenuJogadores()
{
}

void MenuJogadores::LoopMenu(char tecla)
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
				jogo->setEstado(2);
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
			}
		}
	
}
