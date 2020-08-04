#pragma once
#include <iostream>
#include "NodoDoblemeteLigado.h"
#include "CObjReader.h"

template <class T>
class ListaDoblemeteLigada
{
private:
	int size;

public:
	NodoDoblemeteLigado<T>* First;
	NodoDoblemeteLigado<T>* End;

public:
	ListaDoblemeteLigada();
	~ListaDoblemeteLigada();

	bool IsEmpty();
	void Insert(T* insrt);
	bool DeletePosition(int position);
	bool DeleteNumber(T* number_toDelete);
	bool Update(T* to_update, T* new_element);
	void Clear();
	void Print();
};
