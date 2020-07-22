#pragma once
#include "NodoListaLigadaInt.h"
#include <iostream>

class ListaLigadaInt
{
private:
	//NodoListaLigadaInt* NodoInicial = nullptr;
	//NodoListaLigadaInt* Temporal = nullptr; 
	//NodoListaLigadaInt* NodoFinal;

	NodoListaLigadaInt* m_pList;
	int m_numElems;


public:
	ListaLigadaInt();
	~ListaLigadaInt();

	bool Insert(int elem);
	bool IsEmpty();
	bool IsFull() const { return false; }
	bool Delete(int num_elem);
	bool DeleteElement(int num_elem);
	bool Update(int num_elem, int new_value);
	void Clear();
	int Size() const { return m_numElems; };
	void Print();
};

