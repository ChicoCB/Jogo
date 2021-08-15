#include "MenuPrincipal.h"
#include "Jogo.h"

MenuPrincipal::MenuPrincipal( int tamanho, Jogo* jg):
Menu(  tamanho, jg)
{
	Textos = new Texto[Tamanho];
	Textos[0].setCor("Vermelho");
	Textos[0].setDimensao(24);
	Textos[0].setMensagem("Novo Jogo");
	Textos[0].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 250);
	Textos[0].setFonte("Arial");

	Textos[1].setCor("Verde");
	Textos[1].setDimensao(24);
	Textos[1].setMensagem("Recuperar Jogo Salvo");
	Textos[1].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 350);
	Textos[1].setFonte("Arial");

	Textos[2].setCor("Verde");
	Textos[2 ].setDimensao(24);
	Textos[2].setMensagem("Verificar Pontuação");
	Textos[2].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 450);
	Textos[2].setFonte("Arial");

	Textos[3].setCor("Verde");
	Textos[3].setDimensao(24);
	Textos[3].setMensagem("Sair");
	Textos[3].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 550);
	Textos[3].setFonte("Arial");

}

MenuPrincipal::~MenuPrincipal()
{
}

void MenuPrincipal::LoopMenu(char tecla)
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
				jogo->setEstado(1);
				jogo->getQuintal().limparTudo();
				jogo->getQuarto().limparTudo();
				break;
			case 1:
				jogo->getQuintal().limparTudo();
				jogo->getQuarto().limparTudo();
				jogo->Recuperar();
				break;
			case 2:
				jogo->getMenuColocacao().setEstadoAnterior(jogo->getEstado());
				jogo->getMenuColocacao().setEditavel(false);
				jogo->setEstado(3);
				break;
			case 3:
				pGerenciadorGrafico->fechar();
				break;
			}
		}
	
}

