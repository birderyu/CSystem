/////////////////////////////////////////////////////////////////////////////////
/// @brief ��������single linked list��
/// 
///  ��������Ķ��弰ʵ��
/// 
/// @author  birderyu
/// @version 1.0
/// @date    2016-08-07
/////////////////////////////////////////////////////////////////////////////////

#ifndef _CORE_SINGLE_LINKED_LIST_H_
#define _CORE_SINGLE_LINKED_LIST_H_

#include "glinkedlist.h"
#include "gstructure.h"

namespace gsystem { // gsystem

template<typename DataT>
struct GSingleLinkedListNode
	: public GNextNodeT<GSingleLinkedListNode<DataT>>
	, public GDataNodeT<DataT>
	, public GNewT<GSingleLinkedListNode<DataT>>
{
	GSingleLinkedListNode(const DataT &data = DataT(),
		GSingleLinkedListNode<DataT> *next = GNULL)
		: GNextNodeT<GSingleLinkedListNode<DataT>>(next)
		, GDataNodeT<DataT>(data)
	{

	}
};

template<typename DataT, typename NodeT = GSingleLinkedListNode<DataT>>
class GSingleLinkedList 
	: public GLinkedList<DataT, NodeT>
{
public:
	GSingleLinkedList();
	GSingleLinkedList(const DataT &data);
	GSingleLinkedList(DataT &&data);
	GSingleLinkedList(const GSingleLinkedList<DataT, NodeT> &list);
	GSingleLinkedList(GSingleLinkedList<DataT, NodeT> &&list);
	GSingleLinkedList<DataT, NodeT>& operator=(const GSingleLinkedList<DataT, NodeT> &list);
	GSingleLinkedList<DataT, NodeT>& operator=(GSingleLinkedList<DataT, NodeT> &&list);
	virtual ~GSingleLinkedList();

public:
	gsize Size() const;
	gbool IsEmpty() const;
	
	gvoid Invert();

	gvoid InsertBefore(gsize pos, const DataT &data);
	gvoid InsertBefore(gsize pos, DataT &&data);

	gvoid InsertBefore(NodeT *node, const DataT &data);
	gvoid InsertBefore(NodeT *node, DataT &&data);

	gvoid InsertAfter(gsize pos, const DataT &data);
	gvoid InsertAfter(gsize pos, DataT &&data);

	gvoid InsertAfter(NodeT *node, const DataT &data);
	gvoid InsertAfter(NodeT *node, DataT &&data);

	gvoid AddFirst(const DataT &data);
	gvoid AddFirst(DataT &&data);

	gvoid AddLast(const DataT &data);
	gvoid AddLast(DataT &&data);

	gvoid Remove(const NodeT *node);
	virtual gvoid RemoveAt(gsize pos, DataT *data = GNULL);
	gvoid RemoveFirst(DataT *data = GNULL);
	gvoid RemoveLast(DataT *data = GNULL);
	gvoid RemoveAll(DataT *data = GNULL);

	NodeT *GetFirstNode();
	const NodeT *GetFirstNode() const;
	NodeT *GetLastNode();
	const NodeT *GetLastNode() const;
	NodeT *GetNodeAt(gsize pos);
	const NodeT *GetNodeAt(gsize pos) const;

	DataT &GetLastData();
	const DataT &GetLastData() const;
	DataT &GetFirstData();
	const DataT &GetFirstData() const;
	DataT &GetDataAt(gsize pos);
	const DataT &GetDataAt(gsize pos) const;

	gvoid SetDataAt(gsize pos, const DataT &data);
	gvoid SetDataAt(gsize pos, DataT &&data);

	// �������򷵻�NULL_POS
	gsize IndexOf(const DataT &data) const;
	NodeT *Find(const DataT &data);
	const NodeT *Find(const DataT &data) const;

	// �������򷵻�NULL_POS�������򷵻��׽ڵ��λ��
	gsize IndexOfCircle() const;
	NodeT *FindCircle();
	const NodeT *FindCircle() const;

	// �������򷵻�NULL_POS�������򷵻��׽ڵ��λ��
	gsize IndexOfCross(const GLinkedList<DataT, NodeT> &);

	DataT &operator[](gsize pos);
	const DataT &operator[](gsize pos) const;

protected:
	gsize m_nSize;
	Node *m_pFirst;
};

} // namespace gsystem

#include "gsinglelinkedlist.inl"

#endif // _CORE_SINGLE_LINKED_LIST_H_