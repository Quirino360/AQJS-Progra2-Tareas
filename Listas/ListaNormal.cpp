#include "ListaNormal.h"
#include "ListaVinculada.h"

ListaNormal::ListaNormal()
{
    Clear();
}

ListaNormal::~ListaNormal()
{
    Clear();
}

bool ListaNormal::Insert(int element)
{
    if (!IsFull())
    {
        m_Elements[m_iNumElemts++] = element;
        return true;
    }
    else
    {
        std::cout << "Lista llena" << std::endl;
    }
    return false;
}

bool ListaNormal::Delete(int num_elemet)
{
    int indx = num_elemet - 1;
    if (IsEmpty())
    {
        return false;
    }

    if (indx < 0 || indx > m_iNumElemts)
    {
        std::cout << "Indice invalido" << std::endl;
        return false;
    }

    for (int i = indx; i < m_iNumElemts; i++)
    {
        m_Elements[i] = m_Elements[i + 1];
    }

    m_Elements[m_iNumElemts--] = 0;
    return true;
}

bool ListaNormal::Update(int num_elemt, int new_value)
{
    int indx = num_elemt - 1;
    if (indx >= 0 && indx <= m_iNumElemts)
    {
        m_Elements[indx] = new_value;
        return true;
    }
    else
    {
        std::cout << "Your list is Empty" << std::endl;
    }
    return false;
}

void ListaNormal::Clear()
{
    m_iNumElemts = 0;
    memset(&m_Elements[0], 0, 100 * sizeof(int));
}

void ListaNormal::Print()
{
    if (!IsEmpty())
    {
        for (int i = 0; i < m_iNumElemts; ++i)
        {
            std::cout << "m_Elems[" << i << "]: " << m_Elements[i] << std::endl;
        }
    }
    else
    {
        std::cout << "Your list is Empty" << std::endl;
    }
}
