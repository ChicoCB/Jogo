#pragma once
#include "Lista.h"
#include "Personagem.h"

class ListaPersonagens
{
private:
    Lista <Personagem> listaPersonagens;

public:
    ListaPersonagens();
    ~ListaPersonagens();

    Personagem* getAtual();
    void inclua(Personagem* ppersonagem);
    int tamanho();
    void limpar();
    void proximo();
    void inicio();
};

