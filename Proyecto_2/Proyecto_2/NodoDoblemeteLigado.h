#pragma once
#include "CObjReader.h"

class NodoDoblemeteLigado
{
private:
	NodoDoblemeteLigado* next;
	NodoDoblemeteLigado* prev;
	CObjReader* data;

public:
	NodoDoblemeteLigado();
	~NodoDoblemeteLigado();

	void SetData(CObjReader* d) { data = d; }
	CObjReader* getData() { return data; }

	NodoDoblemeteLigado* GetNext() { return next; }
	void SetNext(NodoDoblemeteLigado* n) { next = n; }

	NodoDoblemeteLigado* GetPrev() { return prev; }
	void SetPrev(NodoDoblemeteLigado* p) { prev = p; }
	
};

