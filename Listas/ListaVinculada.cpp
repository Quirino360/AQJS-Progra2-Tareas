#include "ListaVinculada.h"

ListaVinculada::ListaVinculada() :
	m_numElems{ 0 }
{
	m_pList = new NodoListLigada(0);

}

ListaVinculada::~ListaVinculada()
{
	Clear();
}

bool ListaVinculada::Insert(int elem)
{
	NodoListLigada* m_NuevoNodo;
	m_NuevoNodo = new NodoListLigada(elem);
	NodoListLigada* aux1 = m_pList->getNext();
	m_pList->setNext(m_NuevoNodo);
	m_NuevoNodo->setNext(aux1);
	return true;
}

bool ListaVinculada::isEmpty()
{
	return (m_pList != nullptr ? ((m_pList->getNext() == nullptr)) : false);
}

bool ListaVinculada::Delete(int num_elem)
{
	NodoListLigada* aux = m_pList;

	for (int i = 0; i > num_elem || aux->getNext() != nullptr; i++)
	{
		if (aux->getNext() == nullptr) {

			std::cout << "ERROR TE PASATE DE LARGO. NO EXISTE  AUN ESE DATO" << std::endl;
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

bool ListaVinculada::Update(int num_elem, int new_value)
{
	NodoListLigada* aux = m_pList;

	for (int i = 0; i <= num_elem || aux->getNext() != nullptr; i++)
	{
		if (aux->getNext() == nullptr) {

			std::cout << "ERROR TE PASATE DE LARGO. NO EXISTE  AUN ESE DATO" << std::endl;
			return false;

		}
		if (num_elem == i) {

			aux->set_IDato(new_value);
		}
		aux = aux->getNext();
	}
	return true;
}

void ListaVinculada::Clear()
{
	if (m_pList != nullptr) {
		NodoListLigada* aux = nullptr;

		while (m_pList != nullptr) {
			aux = m_pList->getNext();
			delete m_pList;
			m_pList = aux;
		}
	}

	m_numElems = 0;
}

bool ListaVinculada::DeleteElement(int num_elem)
{
	NodoListLigada* current = m_pList;
	NodoListLigada* previus = current;
	for (int i = 0; i <= num_elem || current->getNext() != nullptr; i++)
	{
		if (current->getNext() == nullptr) {

			std::cout << "ERROR TE PASATE DE LARGO. NO EXISTE  AUN ESE DATO" << std::endl;
			return false;

		}
		if (num_elem == i) {
			previus->setNext(current->getNext());
			current->~NodoListLigada();

		}
		previus = current;
		current = current->getNext();

	}
	return true;
}

void ListaVinculada::Print()
{
	NodoListLigada* aux = m_pList;
	std::cout << "Lista Ligada" << std::endl;
	while (aux->getNext() != nullptr)
	{
		std::cout << aux->m_iDato << std::endl;
		aux = aux->getNext();
	}
}
