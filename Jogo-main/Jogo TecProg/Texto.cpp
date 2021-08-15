#include "Texto.h"

Texto::Texto()
{
}

Texto::~Texto()
{
}

void Texto::setPosicoes(float x, float y)
{
	PosicaoX = x;
	PosicaoY = y;
}

float Texto::getPosicaoX()
{
	return PosicaoX;
}

float Texto::getPosicaoY()
{
	return PosicaoY;
}

void Texto::setDimensao(float dim)
{
	Dimensao = dim;
}

float Texto::getDimensao()
{
	return Dimensao;
}

void Texto::setMensagem(string mens)
{
	Mensagem = mens;
}

string Texto::getMensagem()
{
	return Mensagem ;
}

void Texto::setCor(string cor)
{
	Cor = cor;
}

string Texto::getCor()
{
	return Cor;
}

void Texto::setFonte(string fon)
{
	Fonte = fon;
}

string Texto::getFonte()
{
	return Fonte;
}
