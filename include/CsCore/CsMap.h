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

public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		Iterator(Node *node = NULL)
			:m_pNode(node)
		{

		}
		inline const KeyT &key() const { return node->m_tKey; }
		inline ValueT &value() const { return node->m_tValue; }
		inline ValueT &operator*() const { return node->m_tValue; }
		inline ValueT *operator->() const { return &node->m_tValue; }
		inline cs_bool operator==(const Iterator &o) const { return node == o.node; }
		inline cs_bool operator!=(const Iterator &o) const { return node != o.node; }

	private:
		Node *m_pNode
	};

public:
	Iterator Insert(const KeyT &key, const ValueT &value)
	{
		Node node(key, value);
		Node *p = m_tRBTree.InsertByNode(node);
		return Iterator(p);
	}

	cs_bool Contains(const KeyT &key) const
	{
		return m_tRBTree.Find(key) != NULL;
	}

	Iterator Remove(const KeyT &key)
	{
		Node *p = m_tRBTree.Delete(key);
		return Iterator(p);
	}

private:
	CsRBTree <KeyT, CompareT, CsMapNode<KeyT, ValueT>> m_tRBTree;
};

#endif // _CORE_MAP_H_