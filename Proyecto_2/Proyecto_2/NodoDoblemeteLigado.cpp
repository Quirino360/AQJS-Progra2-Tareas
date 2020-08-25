#include "NodoDoblemeteLigado.h"

template<class T>
NodoDoblemeteLigado<T>::NodoDoblemeteLigado()
{
	m_next = nullptr;
	m_prev = nullptr;
}

template<class T>
NodoDoblemeteLigado<T>::NodoDoblemeteLigado(T* val, NodoDoblemeteLigado* prev, NodoDoblemeteLigado* next)
{
	m_val = val;
	m_prev = prev;
	m_next = next;
}


template<class T>
NodoDoblemeteLigado<T>::~NodoDoblemeteLigado()
{
}