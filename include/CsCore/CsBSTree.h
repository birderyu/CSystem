/////////////////////////////////////////////////////////////////////////////////
/// @brief ������������binary sort tree��
/// 
///  �����������Ķ��弰ʵ��
/// 
/// @author  Birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CSCORE_BINARY_SORT_TREE_H_
#define _CSCORE_BINARY_SORT_TREE_H_

#include "CsBTree.h"

template<typename T>
class CsBSTree : public CsBTree<T>
{//����Ҫ���ж��幹�캯����copying�������������ϳɵİ汾�������ã����ǻ���û���͸������ݳ�Ա����Ӧ�Ĺ��캯����copying����  

public://public interfaces for core operations  
	Node *Find(const T &data) const;
	Node *FindMin() const;
	Node *FindMax() const;
	virtual Node *Insert(const T &data);
	virtual Node *Delete(const T &data);

private://real functions implementing core operations  
	Node *Find(const T &data, Node *p) const;
	Node *FindMin(Node *p) const;
	Node *FindMax(Node *p) const;
	virtual Node *Insert(const T &data, Node *p);//insert data in the proper place which is always a child of a leafnode.  
	virtual Node *Delete(const T &data, Node *p);
};

/*--------------------------------------------------------------------------------------------
*public interfaces for core operations
----------------------------------------------------------------------------------------------*/

template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::Find(const T &data) const
{
	return Find(data, m_pNodeRoot);
}

template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::FindMin() const
{
	return FindMin(m_pNodeRoot);
}

template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::FindMax() const
{
	return FindMax(m_pNodeRoot);
}

template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::Insert(const T &data)
{
	return Insert(data, m_pNodeRoot);
}

template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::Delete(const T &data)
{
	return Delete(data, m_pNodeRoot);
}


/*-------------------------------------------------------------------------------------------------
*real functions implementing core operations
--------------------------------------------------------------------------------------------------*/

template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::Find(const T &data, CsBTreeNode<T> *p) const
{
	if (NULL == p)
	{
		return NULL;
	}
	if (data < p->data)
	{
		return Find(data, p->m_pLeft);
	}
	else if (data > p->data)
	{
		return Find(data, p->m_pRight);
	}
	else
	{
		return p;
	}
}



template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::FindMin(CsBTreeNode<T> *p) const
{
	if (NULL == p)
		return NULL;
	else if (NULL == p->left)
		return p;
	else
		return FindMin(p->left);
}



template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::FindMax(CsBTreeNode<T> *p) const
{
	if (NULL == p)
		return NULL;
	else if (NULL == p->right)
		return p;
	else
		return FindMax(p->right);
}


//����ֵ�����pΪNULL���򷵻�ֵΪ�·����ڴ��ָ�룻���p����NULL���򷵻�ֵ��Ϊp.  
template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::Insert(const T &data, CsBTreeNode<T> *p)
{
	if (NULL == p)//��ֹ������ֻ�ܲ���ҳ�ڵ���ӽڵ�λ���ϡ�  
	{
		try
		{
			p = new CsBTreeNode<T>;
		}
		catch (std::bad_alloc&)
		{
			return NULL;
		}

		p->data = data;
		p->left = NULL;
		p->right = NULL;
		if (NULL == m_pNodeRoot)
		{
			m_pNodeRoot = p;
			m_pNodeRoot->parent = NULL;
		}

	}
	else if (data < p->data)
	{
		p->left = Insert(data, p->left);
		if (p->left)
			p->left->parent = p;
	}
	else if (data > p->data)
	{
		p->right = Insert(data, p->right);
		if (p->right)
			p->right->parent = p;
	}
	// else data is in the tree already, we'll do nothing!  

	return p;
}

//����ֵ������ڵ�p��������data���ȣ��򷵻�ֵ��Ϊp;�����ȣ����������ӽڵ㣬����ֵҲΪp����һ���ӽڵ㣬����ֵΪ���ӽڵ�ָ�룬  
//����޽ڵ㣬����ֵNULL��  
template<typename T>
inline CsBTreeNode<T>* CsBSTree<T>::Delete(const T &data, CsBTreeNode<T> *p)
{
	if (NULL == p)
	{
		// Error! data not found!  
	}
	else if (data < p->data)
	{
		p->left = Delete(data, p->left);
	}
	else if (data > p->data)
	{
		p->right = Delete(data, p->right);
	}
	else if (p->left && p->right)   // found it, and it has two children  
	{
		CsBTreeNode<T> *pTmp = FindMin(p->right);
		p->data = pTmp->data;
		p->right = Delete(p->data, p->right);
	}
	else    // found it, and it has one or zero children  
	{
		CsBTreeNode<T> *pTmp = p;
		if (NULL == p->left)
			p = p->right;
		else if (NULL == p->right)
			p = p->left;

		if (p)
			p->parent = pTmp->parent;

		if (m_pNodeRoot == pTmp)
			m_pNodeRoot = p;

		delete pTmp;
	}

	return p;
}

#endif // _CSCORE_BINARY_SEARCH_TREE_H_