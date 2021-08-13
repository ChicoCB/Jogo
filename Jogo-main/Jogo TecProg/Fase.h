#pragma once
#include "stdafx.h"
#include "Ente.h"
#include "Plataforma.h"
#include "GerenciadorColisoes.h"
#include "Obstaculo.h"
#include "Espinho.h"
#include "Estatico.h"
#include "ListaEntidades.h"
#include "ListaPersonagens.h"
#include "Projetil.h"

class Jogo;
class Jogador;

class Fase : public Ente
{
protected:
	Entidade Cenario;
	Jogador* pFazendeira;
	Jogador* pBruxo;
	Jogo* pJogo;
	sf::View* pView; //pGerenciadorGrafico

	GerenciadorColisoes gerenciadorColisoes;
	ListaEntidades listaEntidades;
	ListaPersonagens listaPersonagens;
	
public:
	Fase();
	virtual ~Fase();

	void setJogo(Jogo* pjogo);
	Jogo* getJogo();
	void setFazendeira(Jogador* pfazendeira);
	Jogador* getFazendeira();
	void setBruxo(Jogador* pbruxo);
	void setView(sf::View* pview);

	//Cria objetos que estão em ambas as fases
	void criaPlataforma(sf::Vector2f posicao, const string textura = "textures/Plataforma_meio.png");
	void criaPlataforma(sf::Vector2f posicao, const string textura, sf::Vector2f tamanho);
	void criaBordas();
	void criaEstatico(sf::Vector2f posicao, const string textura = "");
	void criaEspinho(sf::Vector2f posicao, const string textura = "");
	void criaTeia(sf::Vector2f posicao, const string textura = "");

	void atualizaView();
	void incluaProjetil(Projetil* projetil);
	void salvar();

	void recuperarProjeteis();
	void recuperarEstaticos();
	void recuperarEspinhos();
	void recuperarTeias();
	
	virtual void setChefaoMorreu(bool chefaomorreu);

	virtual void inicializa() = 0;
	virtual void atualiza(float deltaTempo) = 0;
	virtual void criaPlataformas() = 0;
};

