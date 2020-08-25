#include "KdTree.h"

KdTree::KdTree() : m_root(nullptr)
{
}

KdTree::~KdTree()
{
    if (m_root != nullptr)
    {
        delete m_root;
        m_root = nullptr;
    }
}

bool KdTree::insertElementObj(CObjReader* objread)
{
    if (m_root == nullptr) {
        m_root = new KdTreeNode(objread, 0);
    }
    else {
        m_root->insertElementObj(objread);
    }


    return true;
}

bool KdTree::deleteElementObj(CObjReader* position)
{
    return false;
}