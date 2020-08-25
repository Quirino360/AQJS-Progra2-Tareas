#pragma once
#include "CObjReader.h"
#include <iostream>
class KdTreeNode
{
private:
    int A = 0;
    const int K = 2;
    CObjReader* m_Data;
    KdTreeNode* m_left;
    KdTreeNode* m_right;
    int profundidad = 0;

public:
    KdTreeNode(CObjReader* data, int profundidad);
    ~KdTreeNode();

    CObjReader* get_m_Data() { return m_Data; }
    KdTreeNode* getLeft() { return m_left; }
    KdTreeNode* getRigth() { return m_right; }

    void clear();
    void inOrder();
    void preOrder();
    void postOrder();

    bool insertElementObj(CObjReader* data);
    bool insertElementToElimi(KdTreeNode* subArbol);
};



