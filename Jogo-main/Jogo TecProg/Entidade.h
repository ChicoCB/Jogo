#pragma once
#include "stdafx.h"
#include "Ente.h"

class Personagem;
class GerenciadorGrafico;

class Entidade : public Ente
{
protected:

	float MovimentoX, MovimentoY;
	bool Desalocavel;

	int IdCorpo;
	static int IdCorpoAtual;
	
public:
	Entidade();
	virtual ~Entidade();

	void setDimensoes(float x, float y);
	float getDimensoesX();
	float getDimensoesY();
		
	void setPosicao(float x, float y);
	float getPosicaoX();
	float getPosicaoY();

	void setMovimento(float x, float y);
	float getMovimentoX();
	float getMovimentoY();

	void setDesalocavel(bool desalocavel);
	bool getDesalocavel();

	void incrementaIdCorpoAtual();
	void setId(int id);
	int getIdCorpoAtual();
	int getId();

	void movimenta(float movimentox, float movimentoy);
	void desenhar();

	virtual void colidir(Personagem* personagem);
	virtual void atualiza(float deltaTempo);
	virtual void salvar();
};

