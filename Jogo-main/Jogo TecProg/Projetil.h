#pragma once
#include "Entidade.h"
#include "Personagem.h"

class Fase;

class Projetil : public Entidade
{
private:

	float VelocidadeX, VelocidadeY;
	string Textura;
	bool Amigavel;
	Fase* faseAtual;
	//float Tamanho;

public:
	Projetil();
	~Projetil();

	void setAmigavel(bool amigavel);
	bool getAmigavel();
	void colidir(Personagem* personagem);
	void atualiza(float deltaTempo);
	void setVelocidade(float velx, float vely);

	void setTextura(string textura);
	//void setTamanho(float lado);
	//float getTamanho

	float getVelocidadeX();
	float getVelocidadeY();

	void setFaseAtual(Fase* faseatual);
	void salvar();
};

