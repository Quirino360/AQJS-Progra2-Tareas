#include <iostream>
using namespace std;

int EjerUno(const char* x)
{
	int counter = 0;
	for (const char* i = x; *i != '\0'; i++)
	{
		counter++;
	}
	return counter;
}

/*
ptrSource es un puntero al array de origen.
numSrcElems es el número de elementos que tiene el array de origen.
startFromSrcIndex es el índice desde el cual se van a leer los elementos a copiar.
numElementsToCopy es el número de elementos que se quieren copiar al array de destino.
ptrDest es el puntero al array de destino
numDestElems es el numero de elementos que tiene el array de destino.
startFromDestIndex es el índice desde el cual se van a escribir los elementos en el array destino.
*/
int EjerDos(int* ptrSource, int numSrcElems, int startFromSrcIndex, int numElementsToCopy,int* ptrDest, int numDestElems, int startFromDestIndex)
{
	if ((numSrcElems - startFromSrcIndex) < numElementsToCopy)
	{
		cout << "Error" << endl;
	}
	else if ((numDestElems - startFromDestIndex) < numElementsToCopy)
	{
		cout << "No hay suficinete espacio, se pondra lo que se pueda..." << endl;

		for (int i = 0; i < (numDestElems - startFromDestIndex); i++)
		{
			*(ptrDest + startFromDestIndex + i) = *(ptrSource + startFromSrcIndex + i);
		}
	}
	else
	{
		for (int i = 0; i < numElementsToCopy; i ++)
		{
			*(ptrDest + startFromDestIndex + i) = *(ptrSource + startFromSrcIndex + i);
		}
	}
	return 0;
}


int EjerTres(const char* x)
{
	const char* counter;
	for (const char* i = x; *i != '\0'; i++)
	{
		counter++;
	}

	return counter - x;
}

int main()
{
	////////////////////////////////////////////////////////////////////////////
	const char* c = "Hola mundo";
	cout << "Ejercicio uno:" << endl;
	cout <<"Su longitu es de = "<<EjerUno(c) << endl;
	system("pause");
	system("cls;");


	//////////////////////////////////////////////////////////////////////////
	cout << "Ejercicio 2:" << endl;
	int arrayOne[10]{};
	int arrayTwo[8]{};
	for (int i = 0; i < 10; i ++)
	{
		*(arrayOne + i) = i + 1;
	}
	int copiar = EjerDos(arrayOne,10,5,5, arrayTwo, 8, 2);

	for (int i = 0; i < 8; i ++)
	{
		cout << *(arrayTwo + i) << endl;
	}
	system("pause");
	system("cls;");

	/////////////////////////////////////////////////////////////////////////////
	cout << "Ejercicio 3:" << endl;
	const char* ch = "Dogge y Moom moon";
	cout << "Ejercicio uno:" << endl;
	cout << "Su longitu es de = " << EjerTres(ch) << endl;
	system("pause");
	system("cls;");
}