#pragma once
#include "stdafx.h"
#include "GerenciadorGrafico.h" 
#include "MenuPrincipal.h"
#include "MenuFases.h"
#include "MenuJogadores.h"
#include "MenuPause.h"
#include "MenuColocacao.h"
#include "Creditos.h"
#include "Quintal.h"
#include "Quarto.h"
#include "Jogador.h"
 
class Jogo
{
private:
	GerenciadorGrafico gerenciadorGrafico;
	Quintal Fase_Quintal;
	Quarto Fase_Quarto;
	Jogador* Jogador1;
	Jogador* Jogador2;
 	int Estado;
	bool Multiplayer;
	MenuPrincipal menuPrincipal;
	MenuJogadores menuJogadores;
	MenuFases menuFases;
	MenuPause menuPause;
	MenuColocacao menuColocacao;
	Creditos creditos;

	bool Jogador1Fazendeira; //se for falso, é bruxo, se for verdadeiro é fazendeira

public:
	Jogo();
	~Jogo();

	void setEstado(int estado);
	int getEstado();
	Quarto& getQuarto();
	Quintal& getQuintal();
	void setMultiplayer(bool multiplayer);
	bool getMultiplayer();
	GerenciadorGrafico& getGerenciadorGrafico();

	MenuColocacao& getMenuColocacao();
	
	Jogador* getJogador2();
	Jogador* getJogador1();

	void Atualiza(float deltaTempo);
	void Inicializa();
	void InicializaFases();
	void InicializaQuintal();
	void InicializaQuarto();
	void InicializaJogadores();
	void Executar();
	void LoopJogo();
	void Salvar();
	void Recuperar();
	void LimparArquivos();

	void setJogador1Fazendeira(bool fazendeira);
	bool getJogador1Fazendeira();

	void setEstadoAtual(int estado);

	void MenusJogo(int estado, char tecla);

	void RecuperarJogadores();
};

