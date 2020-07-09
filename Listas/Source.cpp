#include <iostream>
#include "ListaVinculada.h"
#include "ListaNormal.h"

int main()
{
	ListaVinculada lista;
	lista.Insert(15);
	lista.Insert(15);
	lista.Insert(15);
	lista.Insert(15);
	lista.Print();

	lista.DeleteElement(1);
	lista.Print();

	lista.Update(1, 100);
	lista.Delete(15);
	lista.Print();

	/*
	ListaNormal list;
	list.Insert(1);
	list.Insert(5);
	list.Insert(42);
	list.Insert(17);
	list.Insert(0);
	list.Insert(15);

	list.Delete(2);

	list.Print();
	return 0;
	*/
}