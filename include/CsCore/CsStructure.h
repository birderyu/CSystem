#ifndef _CORE_STRUCTURE_H_
#define _CORE_STRUCTURE_H_

#include "CsGlobal.h"

/// һά��ͨ��ģʽ����
template<typename ListT>
struct CsListT
{
	static const cs_size_t MAX_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_POS = CS_LIST_NULL_POS;
};

/// ��ά��ͨ��ģʽ����
template<typename TableT>
struct CsTableT
{
	static const cs_size_t MAX_ROW_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_ROW_POS = CS_LIST_NULL_POS;
	static const cs_size_t MAX_COLUMN_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_COLUMN_POS = CS_LIST_NULL_POS;
};

/// ��������ڵ�
template<typename NodeT>
struct CsNextNodeT
{
	NodeT *m_pNext;

	CsNextNodeT(NodeT *);
};

/// ˫������ڵ�
template<typename NodeT>
struct CsPreviousNextNodeT
{
	NodeT *m_pPrevious;
	NodeT *m_pNext;

	CsPreviousNextNodeT(NodeT *previous, NodeT *next);
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

/// �����ӽڵ�
template<typename NodeT>
struct CsChildNodeT
{
	NodeT *m_pChild;

	CsChildNodeT(const NodeT *);
};

/// ��ֵ�Խڵ�
template<typename KeyT, typename ValueT>
struct CsPairNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	CsPairNodeT(const KeyT &key, const ValueT &value);
};

// �ƽڵ�
struct CsDummyNodeT
{

};

#include "CsStructure.inl"

#endif // _CORE_STRUCTURE_H_