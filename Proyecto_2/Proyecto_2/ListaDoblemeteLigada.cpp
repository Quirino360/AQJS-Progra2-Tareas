#include "ListaDoblemeteLigada.h"

template <class T>
ListaDoblemeteLigada<T>::ListaDoblemeteLigada()
{
    First = nullptr;
    End = nullptr;
    size = 0;
}
template <class T>
ListaDoblemeteLigada<T>::~ListaDoblemeteLigada()
{
    //Clear();
}

template <class T>
bool ListaDoblemeteLigada<T>::IsEmpty()
{
    if (End == nullptr)
    {
        return true;   
    }
    return false;
}

template <class T>
void ListaDoblemeteLigada<T>::Insert(T* insrt)
{
    if (IsEmpty())//primera vez que entra
    {


        End = new NodoDoblemeteLigado();
        End->SetData(insrt);
        End->SetNext(First);
        End->SetPrev(End);

        First = End;
        size += 1;
    }
    else 
    {
        NodoDoblemeteLigado* aux = new NodoDoblemeteLigado();
        aux = End;

        End = new NodoDoblemeteLigado();
        End->SetData(insrt);
        End->SetNext(First);
        End->SetPrev(aux);
        
        aux->SetNext(End);
        First->SetPrev(End);
        size += 1;
    }

}

template <class T>
bool ListaDoblemeteLigada<T>::DeletePosition(int position)
{
    NodoDoblemeteLigado* aux = End;
    if (!IsEmpty())
    {
        for (int i = 0; i < position; i++)
        {
            aux = aux->GetNext();
        }

        aux->GetPrev()->SetNext(aux->GetNext());
        aux->GetNext()->SetPrev(aux->GetPrev());

        delete aux;
        size -= 1;

        return true;
    }
    return false;
}

template <class T>
bool ListaDoblemeteLigada<T>::DeleteNumber(T* number_toDelete)
{
    NodoDoblemeteLigado* aux = End;
    if (!IsEmpty())
    {
        for (int i = 0; i < size ; i++)
        {
            aux = aux->GetNext();
            if (aux->getData() == number_toDelete)
            {
                aux->GetPrev()->SetNext(aux->GetNext());
                aux->GetNext()->SetPrev(aux->GetPrev());

                delete aux;
                size -= 1;
                aux = End;
            }
        }
        return true;
    }
    return false;
}

template <class T>
bool ListaDoblemeteLigada<T>::Update(T* to_update, T* new_element)
{
    return false;
}

template <class T>
void ListaDoblemeteLigada<T>::Clear()
{
    NodoDoblemeteLigado* aux = new NodoDoblemeteLigado();
    if (IsEmpty())
    {
        std::cout << "This list is empty u cant delete this" << std::endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            aux = First->GetNext();
            delete First;
            First = aux;
        }
        First = nullptr;
        End = nullptr;
        size = 0;
    }

}

template <class T>
void ListaDoblemeteLigada<T>::Print()
{
    NodoDoblemeteLigado* aux = new NodoDoblemeteLigado();
    if (IsEmpty())
    {
        std::cout << "U cant print an empty list" << std::endl;
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            aux = this->End->GetNext();
            this->End = this->End->GetNext();
            std::cout << "[" << i + 1 << "] " << aux->getData() << std::endl;

        }
    }

}
