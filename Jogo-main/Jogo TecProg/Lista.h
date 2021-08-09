#pragma once
#include "stdafx.h"

template <class TIPO>
class Lista
{
public:
    template <class TIPO>
    class Elemento
    {
    private:
        TIPO* pTipo;
        Elemento<TIPO>* pProx, * pAnte;
    public:
        Elemento() { pProx = NULL; pTipo = NULL; pAnte = NULL; }
        ~Elemento() { pTipo = NULL; pProx = NULL; }

        void setTipo(TIPO* ptipo) { pTipo = ptipo; }
        TIPO* getTipo() { return pTipo; }

        void setAnte(Elemento<TIPO>* p) { pAnte = p; }
        Elemento<TIPO>* getAnte() { return pAnte; }

        void setProx(Elemento<TIPO>* p) { pProx = p; }
        Elemento<TIPO>* getProx() { return pProx; }
    };

    Lista();
    ~Lista();

    void incluaTipo(TIPO* tipo);
    void atualiza(float deltaTempo);
    void desenhar();

    int getTamanho();
    TIPO* indice(int i);

private:
    Elemento<TIPO>* pPrimeiro;
    Elemento<TIPO>* pUltimo;
};

template<class TIPO>
Lista<TIPO>::Lista()
{
    pPrimeiro = NULL;
    pUltimo = NULL;
}

template<class TIPO>
Lista<TIPO>::~Lista()
{
    Elemento<TIPO>* pAux = NULL;

    pAux = pPrimeiro;

    while (pAux != NULL)
    {
        pPrimeiro = pPrimeiro->getProx();
        delete pAux;
        pAux = NULL;
        pAux = pPrimeiro;
    }
    pAux = NULL;
    pPrimeiro = NULL;
    pUltimo = NULL;
}

template<class TIPO>
inline void Lista<TIPO>::incluaTipo(TIPO* tipo)
{
    if (tipo != NULL)
    {
        Elemento<TIPO>* pAux = NULL;
        pAux = new Elemento<TIPO>();
        pAux->setTipo(tipo);

        if (pPrimeiro == NULL)
        {
            pPrimeiro = pAux;
            pUltimo = pAux;
        }
        else
        {
            pAux->setAnte(pUltimo);
            pUltimo->setProx(pAux);
            pUltimo = pAux;
        }
    }
    else
        cout << "Erro. Elemento nulo na lista." << endl;
}

template<class TIPO>
inline void Lista<TIPO>::atualiza(float deltaTempo)
{
    Elemento<TIPO>* pAux = NULL;

    pAux = pPrimeiro;

    while (pAux != NULL)
    {
        TIPO* pE = NULL;

        pE = pAux->getTipo();
        pE->atualiza(deltaTempo);
        pAux = pAux->getProx();
    }
}

template<class TIPO>
inline void Lista<TIPO>::desenhar()
{
    Elemento<TIPO>* pAux = NULL;

    pAux = pPrimeiro;

    while (pAux != NULL)
    {
        TIPO* pE = NULL;

        pE = pAux->getTipo();

        pE->desenhar();

        pAux = pAux->getProx();
    }
}

template<class TIPO>
inline int Lista<TIPO>::getTamanho()
{
    Elemento<TIPO>* pAux = NULL;
    int tamanho = 0;

    pAux = pPrimeiro;

    while (pAux != NULL)
    {
        tamanho++;
        pAux = pAux->getProx();
    }
    return tamanho;
}

template<class TIPO>
inline TIPO* Lista<TIPO>::indice(int i)
{
    Elemento<TIPO>* pAux = NULL;
    pAux = pPrimeiro;

    if (i < getTamanho())
    {
        for (int j = 0; j < i; j++)
            pAux = pAux->getProx();
        return pAux->getTipo();
    }
    else
    {
        cout << "Local indevido acessado" << endl;
        exit(1);
    }
}
