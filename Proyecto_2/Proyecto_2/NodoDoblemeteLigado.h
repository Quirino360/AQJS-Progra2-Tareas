#pragma once
#include "CObjReader.h"
#include "CVector3.h"

template <class T>
class NodoDoblemeteLigado
{
private:

	T* m_val;
	NodoDoblemeteLigado* m_prev;
	NodoDoblemeteLigado* m_next;

public:
	NodoDoblemeteLigado();
	NodoDoblemeteLigado(T* val, NodoDoblemeteLigado* prev, NodoDoblemeteLigado* next);
	~NodoDoblemeteLigado();
	NodoDoblemeteLigado<T>* getNext() { return m_next; }
	T* getValue() { return m_val; }

	template <class T> friend class ListaDoblemeteLigada;
};
