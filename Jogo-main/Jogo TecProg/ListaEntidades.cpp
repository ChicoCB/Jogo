#include "ListaEntidades.h"

ListaEntidades::ListaEntidades()
{
    
}

ListaEntidades::~ListaEntidades()
{
    listaEntidades.limpar();
}

Entidade* ListaEntidades::getAtual()
{
    return listaEntidades.getAtual();
}

void ListaEntidades::inclua(Entidade* pentidade)
{
    listaEntidades.incluaTipo(pentidade);
}

void ListaEntidades::atualiza(float deltaTempo)
{
   listaEntidades.inicio();

    while (listaEntidades.getAtual() != NULL)
    {
        Entidade* pE = NULL;

        pE = listaEntidades.getAtual();

        pE->atualiza(deltaTempo);

        listaEntidades.proximo();
    }
}

void ListaEntidades::limpar()
{
    listaEntidades.inicio();

    while (listaEntidades.getAtual() != NULL)
    {
        Entidade* pE = NULL;

        pE = listaEntidades.getAtual();
        listaEntidades.proximo();
        if (pE->getDesalocavel())
            listaEntidades.remove(pE);

        
    }
}

void ListaEntidades::desenhar()
{
    listaEntidades.inicio();

    while (listaEntidades.getAtual() != NULL)
    {
        Entidade* pE = NULL;

        pE = listaEntidades.getAtual();
    
        pE->desenhar();

        listaEntidades.proximo();
    }
}

void ListaEntidades::salvar()
{
    listaEntidades.inicio();

    while (listaEntidades.getAtual() != NULL)
    {
        Entidade* pE = NULL;

        pE = listaEntidades.getAtual();

        pE->salvar();

        listaEntidades.proximo();
    }
}

int ListaEntidades::tamanho()
{
    return listaEntidades.tamanho();
}

void ListaEntidades::proximo()
{
    listaEntidades.proximo();
}

void ListaEntidades::inicio()
{
    listaEntidades.inicio();
}

void ListaEntidades::remove(Entidade* pentidade)
{
    listaEntidades.remove(pentidade);
}
