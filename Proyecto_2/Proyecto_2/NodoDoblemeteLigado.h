#pragma once
#include "CObjReader.h"

template <class T>
class NodoDoblemeteLigado
{
private:
	NodoDoblemeteLigado<T>* next;
	NodoDoblemeteLigado<T>* prev;
	T* data;

public:
	NodoDoblemeteLigado();
	~NodoDoblemeteLigado();

	void SetData(T* d) { data = d; }
	T* getData() { return data; }

	NodoDoblemeteLigado<T>* GetNext() { return next; }
	void SetNext(NodoDoblemeteLigado<T>* n) { next = n; }

	NodoDoblemeteLigado<T>* GetPrev() { return prev; }
	void SetPrev(NodoDoblemeteLigado<T>* p) { prev = p; }
	
};

