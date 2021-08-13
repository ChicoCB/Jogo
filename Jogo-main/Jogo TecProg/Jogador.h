#pragma once
#include "stdafx.h"
#include "Projetil.h"
#include "Personagem.h"
#include "Atirador.h"

class Fase;

class Jogador : 
	public Personagem, 
	public Atirador
{
private:
	sf::Keyboard::Key Direita, Esquerda, Pulo, Atira;
	//Fase* faseAtual;
	static int Pontuacao;

public:
	Jogador();
	~Jogador();
	
	void incrementaPontuacao();
	static int getPontuacao();
	void inicializa();
	void colidir();
	void atualiza(float deltaTempo);
	void setTeclas(sf::Keyboard::Key direita, sf::Keyboard::Key esquerda , sf::Keyboard::Key pulo, sf::Keyboard::Key atira);
	
	//void setFaseAtual(Fase* faseatual);
	
	//void atiraProjetil();
	void salvar();
	
};

