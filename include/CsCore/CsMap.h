// ʹ�ú����ʵ��

#ifndef _CORE_MAP_H_
#define _CORE_MAP_H_

#include "CsRBTree.h"

/// �ڵ�
template <typename KeyT, typename ValueT>
struct CsMapNode :CsObject
{
	enum COLOR
	{
		COLOR_RED = 0,
		COLOR_BLACK = 1
	};
	KeyT m_tKey;						// ���ݣ���Ҫ���ⲿȥ�����������������ڴ�й¶
	ValueT m_tValue;					// ���ݣ���Ҫ���ⲿȥ�����������������ڴ�й¶
	CsMapNode<KeyT, ValueT> *m_pParent;	// ˫��
	CsMapNode<KeyT, ValueT> *m_pLeft;	// ����
	CsMapNode<KeyT, ValueT> *m_pRight;	// �Һ���
	cs_uint8 m_nColor;

	CsMapNode(
		const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsMapNode<KeyT, ValueT> *parent = NULL,
		CsMapNode<KeyT, ValueT> *left = NULL,
		CsMapNode<KeyT, ValueT> *right = NULL,
		COLOR color = COLOR_BLACK);
	~CsMapNode();
	CsMapNode<KeyT, ValueT> *Copy() const;
};

template<typename KeyT,
	typename ValueT,
	typename CompareT = CsCompareF<KeyT >>
class CsMap :public CsObject
{
	typedef CsMapNode<KeyT, ValueT> Node;
	typedef CsRBTree <KeyT, CompareT, Node> Tree;

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator(Node *node = NULL, Tree *tree = NULL)
			:m_pNode(node), m_pTree(tree)
		{

		}
		inline const KeyT &key() const { return node->m_tKey; }
		inline ValueT &value() const { return node->m_tValue; }
		inline ValueT &operator*() const { return node->m_tValue; }
		inline ValueT *operator->() const { return &node->m_tValue; }
		inline cs_bool operator==(const Iterator &o) const { return node == o.node; }
		inline cs_bool operator!=(const Iterator &o) const { return node != o.node; }
		inline Iterator &operator++() 
		{
			if (m_pTree)
			{
				node = m_pTree->NextNode(node);
			}
			return *this;
		}
		inline Iterator &operator--()
		{
			if (m_pTree)
			{
				node = m_pTree->PreviousNode(node);
			}
			return *this;
		}

	private:
		Node *m_pNode;
		Tree *m_pTree;
	};

public:
	Iterator Insert(const KeyT &key, const ValueT &value)
	{
		Node node(key, value);
		Node *p = m_tTree.InsertByNode(node);
		return Iterator(p, &m_tTree);
	}

	cs_bool Contains(const KeyT &key) const
	{
		return m_tTree.Find(key) != NULL;
	}

	Iterator Remove(const KeyT &key)
	{
		Node *p = m_tTree.Delete(key);
		return Iterator(p);
	}

private:
	Tree m_tTree;
};

#endif // _CORE_MAP_H_