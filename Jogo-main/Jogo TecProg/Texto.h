#pragma once
#include "stdafx.h"

class Texto
{
private:
	string Mensagem, Cor, Fonte;
	float PosicaoX, PosicaoY, Dimensao;


public:
	Texto();
	~Texto();

	void setPosicoes(float x, float y);
	float getPosicaoX();
	float getPosicaoY();

	void setDimensao(float dim);
	float getDimensao();

	void setMensagem(string mens);
	string getMensagem();

	void setCor(string cor);
	string getCor();

	void setFonte(string fon);
	string getFonte();
};

