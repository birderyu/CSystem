#ifndef _CORE_B_TREE_H_
#define _CORE_B_TREE_H_

#include "CsObject.h"
#include "CsDynamicArray.h"
#include "CsReadBlackTree.h"

template<typename KeyT,
	typename CompareT = CsCompareF<KeyT >>
class CsBTreeNode :public CsObject
{
public:
	CsBTreeNode();
	virtual ~CsBTreeNode();

	KeyT &GetKeyAt(const cs_size_t id);
	cs_pointer GetChildAt(const cs_size_t id);

private:
	CsBTreeNode<KeyT> *m_pParent;		// ˫��
	CsDynamicArray<cs_pointer> m_tChildren;		// ����
	CsReadBlackTree<KeyT, CompareT> m_tKeys;	// ʹ�ú��������Ĺؼ��֣�
};

template<typename KeyT,
	cs_size_t LevelN = 3,
	typename CompareT = CsCompareF<KeyT >,
	typename NodeT = CsBTreeNode<KeyT>>
class CsBTree :public CsObject
{

};

#endif // _CORE_B_TREE_H_