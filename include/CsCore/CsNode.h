#ifndef _CORE_NODE_H_
#define _CORE_NODE_H_

#include "CsType.h"

/// ��������ڵ�
template<typename NodeT>
struct CsSingleLinkedListNodeT
{
	NodeT *m_pNext;

	CsSingleLinkedListNodeT(NodeT *);
};

/// ˫������ڵ�
template<typename NodeT>
struct CsDoubleLinkedListNodeT
{
	NodeT *m_pPrevious;
	NodeT *m_pNext;

	CsDoubleLinkedListNodeT(NodeT *previous, NodeT *next);
};

/// �������ڵ�
template<typename NodeT>
struct CsBinaryTreeNodeT
{
	NodeT *m_pParent;	// ˫��
	NodeT *m_pLeft;		// ����
	NodeT *m_pRight;	// �Һ���

	CsBinaryTreeNodeT(NodeT *parent, NodeT *left, NodeT *right);

	// ���ֵ�
	const NodeT *LeftSibling() const;

	// ���ֵ�
	const NodeT *RightSibling() const;

	// ���������ǰ���ڵ�
	const NodeT *Next() const;

	// ��������ĺ�̽ڵ�
	const NodeT *Previous() const;

	// ����������׽ڵ�
	const NodeT *First() const;
	NodeT *First();

	// ���������β�ڵ�
	const NodeT *Last() const;
	NodeT *Last();
};

/// ���ݽڵ�
template<typename DataT>
struct CsDataNodeT
{
	DataT m_tData;

	CsDataNodeT(const DataT &);
};

/// ��ֵ�Խڵ�
template<typename KeyT, typename ValueT>
struct CsKeyValueNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	CsKeyValueNodeT(const KeyT &key, const ValueT &value);
};

#include "CsNode.inl"

#endif // _CORE_NODE_H_