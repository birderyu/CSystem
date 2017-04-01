#ifndef _CORE_B_TREE_H_
#define _CORE_B_TREE_H_

#include "gnew.h"

namespace gsystem { // gsystem

template<typename KeyT, typename ValueT, gsize KEY_MAX, gsize CHILD_MAX>
struct GBTreeNode
	: public GNewT<GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
{
	gbool m_bIsLeaf;					// �Ƿ���Ҷ�ӽڵ�  
	gsize m_nKeyNum;					// �ڵ�����Ĺؼ�������  
	KeyT m_tKeys[KEY_MAX];				// �ؼ�������
	ValueT m_tValues[KEY_MAX];			// ֵ����
	GBTreeNode *m_pChild[CHILD_MAX];	// ����ָ������  

	GBTreeNode(gbool b = true, gsize n = 0)
		:m_bIsLeaf(b), m_nKeyNum(n) {}
};

template<typename KeyT,
	typename ValueT,
	gsize M = 3, 
	gsize KEY_MAX = 2 * M - 1, 
	gsize KEY_MIN = M - 1,
	gsize CHILD_MAX = KEY_MAX + 1, 
	gsize CHILD_MIN = KEY_MIN + 1,
	typename NodeT = GBTreeNode<KeyT, ValueT, KEY_MAX, CHILD_MAX>>
class GBTree
{
public:
	GBTree();
	~GBTree();

	// ��B���в����½��key 
	gbool Insert(const KeyT &key, const ValueT &value);

	// ��B����ɾ�����key 
	gbool Delete(const KeyT &key);

	//����key�Ƿ������B����
	gbool Contains(const KeyT &key) const;

	//���B��
	gvoid Clear();

#ifdef GDEBUG
	// ��ӡ���Ĺؼ��� 
	gvoid Display() const;
#endif // GDEBUG

private:
	// �ݹ�ɾ����  
	gvoid Recursive_clear(NodeT *pNode);

	// ɾ���ڵ�  
	gvoid DeleteNode(NodeT *&pNode);

	// ���ҹؼ���  
	gbool Search(NodeT *pNode, const KeyT &key) const;

	// �����ӽڵ�  
	gvoid SplitChild(NodeT *pParent, gint nChildIndex, NodeT *pChild);

	// �ڷ����ڵ��в���ؼ���  
	gvoid InsertNonFull(NodeT *pNode, const KeyT &key, const ValueT &value);

	// �ϲ������ӽڵ�  
	gvoid MergeChild(NodeT *pParent, gsize index);

	// �ݹ��ɾ���ؼ���  
	gvoid Recursive_remove(NodeT *pNode, const KeyT &key);

	// �ҵ�ǰ���ؼ���  
	KeyT &GetPredecessor(NodeT *pNode);
	const KeyT &GetPredecessor(const NodeT *pNode) const;

	// �ҵ���̹ؼ���  
	KeyT &GetSuccessor(NodeT *pNode);
	const KeyT &GetSuccessor(const NodeT *pNode) const;

#ifdef GDEBUG
	// �����Ŵ�ӡ��  
	gvoid DisplayInConcavo(NodeT *pNode, gint count) const;
#endif // GDEBUG

private:
	NodeT * m_pRoot;  //B���ĸ��ڵ�  
};

} // namespace gsystem

#include "gbtree.inl"

#endif // _CORE_B_TREE_H_