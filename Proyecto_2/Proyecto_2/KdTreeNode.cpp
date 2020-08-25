#include "KdTreeNode.h"

KdTreeNode::KdTreeNode(CObjReader* data, int profundidad):
	m_Data(data), m_left(nullptr), m_right(nullptr), profundidad(0)
{
}

KdTreeNode::~KdTreeNode()
{
	clear();
}

void KdTreeNode::clear()
{
	if (m_left != nullptr)
	{
		delete m_left;
		m_left = nullptr;
	}
	if (m_right != nullptr)
	{
		delete m_right;
		m_right = nullptr;
	}
}

void KdTreeNode::inOrder()
{
	if (m_left != nullptr)
	{
		m_left->inOrder();
	}
	//std::cout << m_data->getX() << " " << m_data->getY() << std::endl;

	if (m_right != nullptr)
	{
		m_right->inOrder();
	}
}

void KdTreeNode::preOrder()
{
	//std::cout << *m_data << std::endl;
	if (m_left != nullptr)
	{
		m_left->preOrder();
	}
	if (m_right != nullptr)
	{
		m_right->preOrder();
	}
}

void KdTreeNode::postOrder()
{
	if (m_left != nullptr)
	{
		m_left->postOrder();
	}
	if (m_right != nullptr)
	{
		m_right->postOrder();
	}
	//std::cout << *m_data << std::endl;

}

bool KdTreeNode::insertElementObj(CObjReader* data)
{
	A = profundidad % K;
	
	if ((A == 0 && data->Get_m_objectPosition()->getX() < m_Data->Get_m_objectPosition()->getX()) || (A == 1 && data->Get_m_objectPosition()->getY() < m_Data->Get_m_objectPosition()->getY())) {
		if (m_left == nullptr) {

			m_left = new KdTreeNode(data, + 1);
		}
		else {
			m_left->insertElementObj(data);
		}

		return true;
	}
	else {
		if (m_right == nullptr) {

			m_right = new KdTreeNode(data, +1);

		}
		else {
			m_right->insertElementObj(data);
		}

		return true;
	}
	return false;

}

bool KdTreeNode::insertElementToElimi(KdTreeNode* subArbol)
{
	return false;
}


