#include <iostream>

using namespace std;

void ReserveMemory(int** ptrInt, int numElems)
{
    *ptrInt = new int[numElems];

    if (*ptrInt != nullptr)
    {
        memset(*ptrInt, 0, numElems * sizeof(int)); //el punetro que vas a usar, el valor que le vas a poner a cada espacio de memoria, cantidad de bytes que se va modificar 

        for (int i = 0; i < numElems; i++)
        {
            *(*ptrInt + i) = i;
        }

        cout << "En reserveMemory()" << endl;
        for (int i = 0; i < numElems; i++)
        {
            cout << "(ptrInt + " << i << "):  " << *(*ptrInt + i) << endl;
        }
    }
}

int main()
{
    int* ptrInt{ nullptr };

    ReserveMemory(&ptrInt, 10);

    if (ptrInt != nullptr) {
        std::cout << "Despues reserveMemory()" << std::endl;
        for (int i = 0; i < 10; i++) {
            std::cout << "(ptrInt + " << i << ") = " << *(ptrInt + i) << std::endl;
        }
    }

    system("pause");
}