#pragma once
class ListaNormal
{
	int m_iNumElemts;
	int m_Elements[100]; //100 = Max Elements in List
public:
	ListaNormal();
	~ListaNormal();

	bool Insert(int element);
	bool IsEmpty() const { return m_iNumElemts == 0; }
	bool IsFull() const { return m_iNumElemts >= 100; }
	bool Delete(int num_elemet);
	bool Update(int num_elemt, int new_value);
	void Clear();
	int Size() const { return m_iNumElemts; }
	void Print();
};

