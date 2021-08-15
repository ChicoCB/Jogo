#include "MenuPause.h"
#include "Jogo.h"

MenuPause::MenuPause( int tamanho, Jogo* jg):
	Menu( tamanho, jg)
{
	Inicializa();
}

MenuPause::~MenuPause()
{
}

void MenuPause::setEstadoAtual(int estadoatual)
{
	EstadoAtual = estadoatual;
}

int MenuPause::getEstadoAtual()
{
	return EstadoAtual;
}

void MenuPause::LoopMenu(char tecla)
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
				jogo->setEstado(EstadoAtual);
				break;
			case 1:
				jogo->Salvar();
				break;
			case 2:
				jogo->getMenuColocacao().setEstadoAnterior(6);
				jogo->getMenuColocacao().setEditavel(true);
				jogo->setEstado(3);
				break;
			case 3:
				jogo->setEstado(0);
				break;
			case 4:
				pGerenciadorGrafico->fechar();
				break;
			}
		}
	
}

void MenuPause::Inicializa()
{
	Textos = new Texto[Tamanho];
	Textos[0].setCor("Vermelho");
	Textos[0].setDimensao(24);
	Textos[0].setMensagem("Retomar");
	Textos[0].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 150);
	Textos[0].setFonte("Arial");

	Textos[1].setCor("Verde");
	Textos[1].setDimensao(24);
	Textos[1 ].setMensagem("Salvar jogo");
	Textos[1].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 250);
	Textos[1].setFonte("Arial");

	Textos[2].setCor("Verde");
	Textos[2].setDimensao(24);
	Textos[2].setMensagem("Salvar pontuação");
	Textos[2].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 350);
	Textos[2].setFonte("Arial");

	Textos[3].setCor("Verde");
	Textos[3].setDimensao(24);
	Textos[3].setMensagem("Voltar ao Menu Principal");
	Textos[3].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 450);
	Textos[3].setFonte("Arial");

	Textos[4].setCor("Verde");
	Textos[4].setDimensao(24);
	Textos[4].setMensagem("Sair do jogo");
	Textos[4].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 550);
	Textos[4].setFonte("Arial");
	

}
