#pragma once
#include <iostream>
#include "NodoDoblemeteLigado.h"
#include "CObjReader.h"

template  <class T>
class ListaDoblemeteLigada
{
private:
	NodoDoblemeteLigado<T>* m_begin;
	NodoDoblemeteLigado<T>* m_end;
	NodoDoblemeteLigado<T>* m_current;

public:
	ListaDoblemeteLigada();
	~ListaDoblemeteLigada();

	bool Insert(T* val);
	bool isEmpty();
	bool Delete(int numElem);
	bool DeleteElem(T* Elem);
	bool Update(int numElem, T* newVal);
	void SetToNext();
	void SetToPrev();
	T* getCurrentValue() { return m_current->m_val; };
	NodoDoblemeteLigado<T>* GetBegin() { return m_begin; }
	NodoDoblemeteLigado<T>* GetEnd() { return m_end; }
	NodoDoblemeteLigado<T>* rend() { return m_begin->m_prev; }
	NodoDoblemeteLigado<T>* rbegin() { return m_end; }
	void Clear();
	void Print();

	//std::cout << "m_current file name = " << ((CObjReader*)m_current->m_val)->Get_m_sFileName() << std::endl;
};