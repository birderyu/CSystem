#ifndef _CORE_STRUCTURE_H_
#define _CORE_STRUCTURE_H_

#include "gtype.h"

namespace gsystem { // gsystem

/********************************************************************************
**
** @brief һά����
** @template T {type} Ԫ�ص�����
**
********************************************************************************/
template<typename T>
struct GListT
{
	/****************************************************************************
	**
	** ��󳤶�
	**
	****************************************************************************/
	static const gsize MAX_SIZE = G_LIST_MAX_SIZE;

	/****************************************************************************
	**
	** ���±�
	**
	****************************************************************************/
	static const gsize NULL_POS = G_LIST_NULL_POS;
};

/********************************************************************************
**
** @brief ��ά��
** @template T {type} Ԫ�ص�����
**
********************************************************************************/
template<typename T>
struct GTableT
{
	/****************************************************************************
	**
	** �������
	**
	****************************************************************************/
	static const gsize MAX_ROW_SIZE = G_LIST_MAX_SIZE;

	/****************************************************************************
	**
	** ���б�
	**
	****************************************************************************/
	static const gsize NULL_ROW_POS = G_LIST_NULL_POS;

	/****************************************************************************
	**
	** �������
	**
	****************************************************************************/
	static const gsize MAX_COLUMN_SIZE = G_LIST_MAX_SIZE;

	/****************************************************************************
	**
	** ���б�
	**
	****************************************************************************/
	static const gsize NULL_COLUMN_POS = G_LIST_NULL_POS;
};

/// ��������ڵ�
template<typename T>
struct GPreviousNodeT
{
	T *m_pPrevious;

	GPreviousNodeT(T *previous) GNOEXCEPT;
};

/// ��������ڵ�
template<typename T>
struct GNextNodeT
{
	T *m_pNext;

	GNextNodeT(T *node) GNOEXCEPT;
};

/// ˫������ڵ�
template<typename T>
struct GPreviousNextNodeT
	: public GPreviousNodeT<T>, GNextNodeT<T>
{
	GPreviousNextNodeT(T *previous, T *next) GNOEXCEPT;
};

/// �������ڵ�
template<typename T>
struct GBinTreeNodeT
{
	T *m_pParent;	// ˫��
	T *m_pLeft;		// ����
	T *m_pRight;	// �Һ���

	GBinTreeNodeT(T *parent, T *left, T *right) GNOEXCEPT;

	// ���ֵ�
	const T *LeftSibling() const GNOEXCEPT;

	// ���ֵ�
	const T *RightSibling() const GNOEXCEPT;

	// ���������ǰ���ڵ�
	const T *Next() const GNOEXCEPT;
	T *Next() GNOEXCEPT;

	// ��������ĺ�̽ڵ�
	const T *Previous() const GNOEXCEPT;
	T *Previous() GNOEXCEPT;

	// ����������׽ڵ�
	const T *First() const GNOEXCEPT;
	T *First() GNOEXCEPT;

	// ���������β�ڵ�
	const T *Last() const GNOEXCEPT;
	T *Last() GNOEXCEPT;
};

/// ���ݽڵ�
template<typename T>
struct GValueNodeT
{
	T m_tData;

	GValueNodeT(const T &value) GNOEXCEPT;
	GValueNodeT(T &&value) GNOEXCEPT;
};

/// �����ӽڵ�
template<typename T>
struct GChildNodeT
{
	T *m_pChild;

	GChildNodeT(const T *node) GNOEXCEPT;
};

/// ��ֵ�Խڵ�
template<typename KeyT, typename ValueT>
struct GPairNodeT
{
	KeyT m_tKey;
	ValueT m_tValue;

	GPairNodeT(const KeyT &key, const ValueT &value) GNOEXCEPT;
	GPairNodeT(const KeyT &key, ValueT &&value) GNOEXCEPT;
};

// �ƽڵ�
struct GDummyNodeT
{

};

} // namespace gsystem

#include "inline/gstruct.inl"

#endif // _CORE_STRUCTURE_H_