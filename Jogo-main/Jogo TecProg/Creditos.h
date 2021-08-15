#pragma once
#include "Menu.h"

class Jogo;

class Creditos:
    public Menu
{
private:

public:
    Creditos( int tamanho, Jogo* jg);
    ~Creditos();

    void LoopMenu(char tecla);

};

