#pragma once
#include "CVector3.h"
#include "CObjReader.h"
#include "KdTreeNode.h"

class KdTree
{
public:
    KdTreeNode* m_root;
    KdTree();
    ~KdTree();

    bool insertElementObj(CObjReader* position);
    bool deleteElementObj(CObjReader* position);

    bool isEmpty() { return (m_root == nullptr); }
    void preorder() { if (!isEmpty()) { m_root->preOrder(); } }
    void inOrder() { if (!isEmpty()) { m_root->inOrder(); } }
    void postOrder() { if (!isEmpty()) { m_root->postOrder(); } }
};
