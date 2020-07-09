#pragma once
class NodoListLigada
{
private:
	NodoListLigada* m_pNext;
public:
	NodoListLigada(int dato);
	~NodoListLigada();

    int m_iDato;
    int get_iDato() { return m_iDato; }
    void set_IDato(int new_dato) { m_iDato = new_dato; }
    NodoListLigada* getNext() { return m_pNext; }
    void setNext(NodoListLigada* n) { m_pNext = n; }
};

