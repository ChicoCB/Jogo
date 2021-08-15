#include "MenuColocacao.h"
#include "Jogo.h"

MenuColocacao::MenuColocacao(  int tamanho, Jogo* jg):
	Menu( tamanho, jg),
	EstadoAnterior(0)
{	
	Inicializa();
}

MenuColocacao::~MenuColocacao()
{
}

void MenuColocacao::LoopMenu(char tecla)
{
	cout << "Indice: " << Indice << endl;
	Textos[Indice].setCor("Vermelho");

	if (Digitando)
	{
			if (tecla == 13)
			{
				Textos[Indice].setCor("Verde");
				Textos[5].setCor("Vermelho");
				Indice = 5;
				Digitando = false;
				Nome.clear();
			}
			else
			{
				string saux;
				stringstream ss;

				if (tecla == '\b') {
					if (Nome.size() != 0)
						Nome.erase(Nome.size() - 1);
				}
				else if (tecla > 31 && tecla < 128) {
					Nome = Nome + tecla;
					//Nome.insert(Nome.size(), tecla);
				}

				ss << jogo->getJogador1()->getPontuacao();

				saux = ss.str() + " - " + Nome;
				cout << ss.str() << endl;
				Textos[Indice].setMensagem(saux);
			}
	}
	 
	else {
		cout << "Digitando = " << Digitando << endl;
		if (tecla == 'w' || tecla == 'W')
			if (Indice != Limite)
				moverCima();
		if (tecla == 's' || tecla == 'S')
			moverBaixo();
		if (tecla == 13)
		{
			if (Indice < 5) {
				Digitando = true;
				Textos[Indice].setMensagem("0 - ");
			}
			else
				switch (Indice)
				{
				case 5:
				{
					ofstream deletarColocacao("saves/Colocacao.dat", ios::out);
					deletarColocacao.close();

					ofstream gravadorColocacao("saves/Colocacao.dat", ios::app);
					if (!gravadorColocacao)
						cout << "Erro Gravar Colocacao." << endl;

					for (int i = 1; i <= 4; i++) {
						string saux = Textos[i].getMensagem();
						while (saux.back() == ' ')
							saux.pop_back();

						gravadorColocacao << saux << '\n';
					}


					gravadorColocacao.close();
				}
				break;
				case 6:
					for (int i = 1; i <= 4; i++)
						Textos[i].setMensagem("0 - Vazio");
					break;
				case 7:
					Textos[Indice].setCor("Verde");
					jogo->setEstado(EstadoAnterior);
					break;
				}

		}
	}
}

void MenuColocacao::Recupera() 
{
	ifstream recuperadorColocacao("saves/Colocacao.dat", ios::in);

	if (!recuperadorColocacao)
		cout << "Erro Recuperar Colocacao." << endl;

	int i = 1;
	string aux, string = "";

	while (!recuperadorColocacao.eof()) {
		recuperadorColocacao >> aux;
		string += aux + " ";
		aux = "";
		if (recuperadorColocacao.get() == '\n') {
			Textos[i].setMensagem(string);
			i++;
			string = "";
		}
	}

	recuperadorColocacao.close();

}

void MenuColocacao::Inicializa() 
{
	
	Digitando = false;

	Textos = new Texto[Tamanho];
	Textos[0].setCor("Verde");
	Textos[0].setDimensao(24);
	Textos[0].setMensagem("Pontuacao:");
	Textos[0].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 150);
	Textos[0].setFonte("Arial");

	Textos[1].setCor("Verde");
	Textos[1].setDimensao(24);
	Textos[1].setMensagem("0 - Vazio");
	Textos[1].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 200);
	Textos[1].setFonte("Arial");

	Textos[2].setCor("Verde");
	Textos[2].setDimensao(24);
	Textos[2].setMensagem("0 - Vazio");
	Textos[2].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 250);
	Textos[2].setFonte("Arial");

	Textos[3].setCor("Verde");
	Textos[3].setDimensao(24);
	Textos[3].setMensagem("0 - Vazio");
	Textos[3].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 300);
	Textos[3].setFonte("Arial");

	Textos[4].setCor("Verde");
	Textos[4].setDimensao(24);
	Textos[4].setMensagem("0 - Vazio");
	Textos[4].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 350);
	Textos[4].setFonte("Arial");

	Textos[5].setCor("Verde");
	Textos[5].setDimensao(24);
	Textos[5].setMensagem("Vermelho");
	Textos[5].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 500);
	Textos[5].setFonte("Arial");

	Textos[6].setCor("Verde");
	Textos[6 ].setDimensao(24);
	Textos[6].setMensagem("Apagar Tudo");
	Textos[6].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 550);
	Textos[6].setFonte("Arial");

	Textos[7].setCor("Verde");
	Textos[7 ].setDimensao(24);
	Textos[7].setMensagem("Voltar");
	Textos[7].setPosicoes(COMPRIMENTO_RESOLUCAO / 4, 600);
	Textos[7].setFonte("Arial");


}

void MenuColocacao::setEditavel(bool Editavel)
{
	if (Editavel) {
		Indice = 1;
		Limite = 1;
	}
	else {
		Indice = 5;
		Limite = 5;
	}

}

void MenuColocacao::setEstadoAnterior(int estadoanterior)
{
	EstadoAnterior = estadoanterior;
}
