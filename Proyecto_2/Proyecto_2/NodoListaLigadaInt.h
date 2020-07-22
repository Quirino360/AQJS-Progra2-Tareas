#pragma once
class NodoListaLigadaInt
{
private:
	
	NodoListaLigadaInt* m_pNext;

public:
	NodoListaLigadaInt(int dato);
	~NodoListaLigadaInt();
	
	int m_iDato;
	int get_iDato() { return m_iDato; }
	void set_iDato(int new_dato) { m_iDato = new_dato; }
	NodoListaLigadaInt* getNext() { return m_pNext; }
	void setNext(NodoListaLigadaInt* n) { m_pNext = n; }
};

