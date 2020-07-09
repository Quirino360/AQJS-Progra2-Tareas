#pragma once
#include "NodoListLigada.h"
#include <iostream>

class ListaVinculada
{
private:

    NodoListLigada* m_pList;
    int m_numElems;

public:

    ListaVinculada();
    ~ListaVinculada();

    bool Insert(int elem);
    bool isEmpty();
    bool isFull() const { return false; }
    //deletea todos los elementos que tenga el mismo numero que se indique
    bool Delete(int num_elem);
    bool Update(int num_elem, int new_value);
    void Clear();
    //deletea solo un elemento
    bool DeleteElement(int num_elem);
    int Size() const { return m_numElems; };
    void Print();
};

