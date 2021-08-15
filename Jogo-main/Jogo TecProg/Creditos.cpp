#include "Creditos.h"
#include "Jogo.h"

Creditos::Creditos(  int tamanho, Jogo* jg) :
	Menu( tamanho, jg)
{
	Textos = new Texto[Tamanho];
	Textos[0].setCor("Vermelho");
	Textos[0].setDimensao(24);
	Textos[0].setMensagem("Salvar Pontuação");
	Textos[0].setPosicoes(COMPRIMENTO_RESOLUCAO * 3 / 4, 500);
	Textos[0].setFonte("Arial");

	Textos[1].setCor("Verde");
	Textos[1].setDimensao(24);
	Textos[1 ].setMensagem("Voltar ao Menu Principal");
	Textos[1].setPosicoes(COMPRIMENTO_RESOLUCAO * 3 / 4, 550);
	Textos[1].setFonte("Arial");

}

Creditos::~Creditos()
{
}


void Creditos::LoopMenu(char tecla)
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
				jogo->getMenuColocacao().setEstadoAnterior(jogo->getEstado());
				jogo->getMenuColocacao().setEditavel(true);
				jogo->setEstado(3);
				break;
			case 1:
				jogo->setEstado(0);
				break;
			}
		}
	

}
