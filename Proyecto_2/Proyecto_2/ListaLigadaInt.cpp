#include "ListaLigadaInt.h"

ListaLigadaInt::ListaLigadaInt() : m_numElems{ 0 }
{
	m_pList = new NodoListaLigadaInt(100);
}

ListaLigadaInt::~ListaLigadaInt()
{
	Clear();
}

bool ListaLigadaInt::Insert(int elem)
{
	NodoListaLigadaInt* m_NuevoNodo = new NodoListaLigadaInt(elem);
	NodoListaLigadaInt* aux1 = m_pList->getNext();

	m_pList->setNext(m_NuevoNodo);
	m_NuevoNodo->setNext(aux1);

	return true;
}

bool ListaLigadaInt::IsEmpty()
{
	return (m_pList != nullptr ? ((m_pList->getNext() == nullptr)) : false);
}

bool ListaLigadaInt::Delete(int num_elem)
{
	NodoListaLigadaInt* aux = m_pList;

	for (int i = 0; i > num_elem || aux->getNext() != nullptr; i++)
	{
		if (aux->getNext() == nullptr) {

			std::cout << "No existe este dato" << std::endl;
			return false;

		}
		if (num_elem == aux->get_iDato()) {
			DeleteElement(i);
			i = 0;
			aux = m_pList;
		}
		aux = aux->getNext();
	}

	return true;
}

bool ListaLigadaInt::DeleteElement(int num_elem)
{
	NodoListaLigadaInt* current = m_pList;
	NodoListaLigadaInt* previous = current;
	for (int i = 0; i <= num_elem || current->getNext() != nullptr; i++)
	{
		if (current->getNext() == nullptr) {

			std::cout << "Aun no existe este dato" << std::endl;
			return false;

		}
		if (num_elem == i) {
			previous->setNext(current->getNext());
			current->~NodoListaLigadaInt();

		}
		previous = current;
		current = current->getNext();

	}
	return true;
}

bool ListaLigadaInt::Update(int num_elem, int new_value)
{
	NodoListaLigadaInt* aux = m_pList;

	for (int i = 0; i <= num_elem || aux->getNext() != nullptr; i++)
	{
		if (aux->getNext() == nullptr) {

			std::cout << "No existe este dato" << std::endl;
			return false;

		}
		if (num_elem == i) {

			aux->set_iDato(new_value);
		}
		aux = aux->getNext();
	}

	return true;
}

void ListaLigadaInt::Clear()
{
	if (m_pList != nullptr) {
		NodoListaLigadaInt* aux = nullptr;

		while (m_pList != nullptr) {
			aux = m_pList->getNext();
			delete m_pList;
			m_pList = aux;
		}
	}

	m_numElems = 0;
}

void ListaLigadaInt::Print()
{
	NodoListaLigadaInt* aux = m_pList;
	std::cout << "Lista Ligada" << std::endl;
	while (aux->getNext() != nullptr)
	{
		std::cout << aux->m_iDato << std::endl;
		aux = aux->getNext();
	}
}
	