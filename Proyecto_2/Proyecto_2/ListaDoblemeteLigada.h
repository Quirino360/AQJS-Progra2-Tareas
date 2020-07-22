#pragma once
#include <iostream>
#include "NodoDoblemeteLigado.h"
#include "CObjReader.h"

class ListaDoblemeteLigada
{
private:
	int size;

public:
	NodoDoblemeteLigado* First;
	NodoDoblemeteLigado* End;

public:
	ListaDoblemeteLigada();
	~ListaDoblemeteLigada();

	bool IsEmpty();
	void Insert(CObjReader* insrt);
	bool DeletePosition(int position);
	bool DeleteNumber(CObjReader* number_toDelete);
	bool Update(CObjReader* to_update, CObjReader* new_element);
	void Clear();
	void Print();
};
