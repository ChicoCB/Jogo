#pragma once
#include "Personagem.h"
#include "Lista.h"

class ListaPersonagens
{
private:
    Lista <Personagem> listaPersonagens;

public:
    ListaPersonagens();
    ~ListaPersonagens();

    void inclua(Personagem* personagem);
    void atualiza(float deltaTempo);
    void desenhar();
    int getTamanho();
    Personagem* indice(int i);
};

