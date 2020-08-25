#include "ListaDoblemeteLigada.h"

template <class T>
ListaDoblemeteLigada<T>::ListaDoblemeteLigada()
{
	m_begin = nullptr;
	m_current = m_begin;
	m_end = m_begin;
}

template<class T>
ListaDoblemeteLigada<T>::~ListaDoblemeteLigada()
{
	Clear();
	if (m_begin != nullptr) {
		delete m_begin;
		m_begin = nullptr;
	}
	if (m_current != nullptr) {
		delete m_current;
		m_current = nullptr;
	}
	if (m_end != nullptr) {
		delete m_end;
		m_end = nullptr;
	}
}

template<class T>
void ListaDoblemeteLigada<T>::SetToNext()
{
	m_current = m_current->m_next;
	/*if (m_current->m_next == m_end) {
		m_current = m_current->m_next->m_next;
	}
	else {
		m_current = m_current->m_next;
	}*/
}

template<class T>
void ListaDoblemeteLigada<T>::SetToPrev()
{
	m_current = m_current->m_prev;
	/*
	if (m_current == m_begin) {
		m_current = m_current->m_prev->m_prev;
	}
	else {
		m_current = m_current->m_prev;
	}*/
}

template<class T>
bool ListaDoblemeteLigada<T>::Insert(T* val)
{
	if (isEmpty()) {
		m_begin = new NodoDoblemeteLigado<T>();
		//m_end = new NodoDoblemeteLigado<T>();
		m_end = m_begin;

		m_begin->m_val = val;
		m_begin->m_next = m_end;
		m_begin->m_prev = m_end;
		m_end->m_next = m_begin;
		m_end->m_prev = m_begin;

		m_current = m_end->m_prev;

		return true;
	}
	else {
		NodoDoblemeteLigado<T>* temp = m_end->m_prev;
		m_end->m_prev = new NodoDoblemeteLigado<T>(val, temp, m_end);
		if (m_begin->m_next == m_end) {
			m_begin->m_next = m_end->m_prev;
		}
		else {
			m_end->m_prev->m_prev->m_next = m_end->m_prev;
		}
		m_current = m_end->m_prev;
		return true;
	}
	return false;
}


template<class T>
bool ListaDoblemeteLigada<T>::isEmpty()
{
	return m_begin == nullptr;
}

template<class T>
bool ListaDoblemeteLigada<T>::Delete(int numElem)
{
	if (!isEmpty()) {
		if (numElem <= 0) {
			std::cout << "Index out of range" << std::endl;
			return false;
		}
		if (numElem == 1) {
			NodoDoblemeteLigado<T>* tempNext = m_begin->m_next;
			if (tempNext == m_end) {
				delete m_begin;
				m_begin = nullptr;
				delete m_end;
				m_end = nullptr;
			}
			else {
				delete m_begin;
				m_begin = tempNext;
				m_end->m_next = m_begin;
				m_begin->m_prev = m_end;
			}
			return true;
		}
		int idx = 1;
		for (NodoDoblemeteLigado<T>* iterator = GetBegin(); iterator != GetEnd(); iterator = iterator->m_next) {
			if (idx == numElem) {
				NodoDoblemeteLigado<T>* tempNext = iterator->m_next;
				NodoDoblemeteLigado<T>* tempPrev = iterator->m_prev;
				delete iterator;
				tempPrev->m_next = tempNext;
				tempNext->m_prev = tempPrev;
				return true;
			}
			idx++;
		}
	}
	std::cout << "Index out of range" << std::endl;
	return false;
}

template<class T>
bool ListaDoblemeteLigada<T>::DeleteElem(T* Elem)
{
	/*
	if (!isEmpty()) {
		for (NodoDoblemeteLigado<T>* iterator = GetBegin(); iterator != GetEnd(); iterator = iterator->m_next) {
			while (iterator->m_val == Elem) {
				NodoDoblemeteLigado<T>* tempNext = iterator->m_next;
				NodoDoblemeteLigado<T>* tempPrev = iterator->m_prev;
				if (iterator == m_begin) {
					if (tempNext == m_end) {
						delete m_begin;
						m_begin = nullptr;
						delete m_end;
						m_end = nullptr;
						return true;
					}
					else {
						delete m_begin;
						m_begin = tempNext;
						tempPrev->m_next = tempNext;
						tempNext->m_prev = tempPrev;
					}
				}
				else {
					delete iterator;
					tempPrev->m_next = tempNext;
					tempNext->m_prev = tempPrev;
				}
				iterator = tempNext;
			}
		}
	}*/
	return true;
	
}

template<class T>
bool ListaDoblemeteLigada<T>::Update(int numElem, T* newVal)
{
	/*
	if (!isEmpty()) {
		if (numElem <= 0) {
			std::cout << "Index out of range" << std::endl;
			return false;
		}
		int idx = 1;
		for (NodoDoblemeteLigado<T>* iterator = GetBegin(); iterator != GetEnd(); iterator = iterator->m_next) {
			if (idx == numElem) {
				iterator->m_val = newVal;
				return true;
			}
			idx++;
		}
		std::cout << "Index out of range" << std::endl;
	}*/
	return false;
	
}

template<class T>
void ListaDoblemeteLigada<T>::Clear()
{
	if (!isEmpty()) {
		for (NodoDoblemeteLigado<T>* iterator = rbegin()->m_prev; iterator != rend(); iterator = iterator->m_prev) {
			delete iterator->m_next;
			iterator->m_next = nullptr;
		}
		delete m_begin;
		m_begin = nullptr;
	}
}

template<class T>
void ListaDoblemeteLigada<T>::Print()
{
	if (!isEmpty()) {
		int idx = 0;
		for (NodoDoblemeteLigado<T>* iterator = GetBegin(); iterator != GetEnd(); iterator = iterator->m_next) {
			std::cout << "List[" << idx++ << "] = " << iterator->m_val << std::endl;
		}
	}
}