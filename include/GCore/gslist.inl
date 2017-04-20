#ifndef _CORE_SINGLE_LINKED_LIST_INLINE_
#define _CORE_SINGLE_LINKED_LIST_INLINE_

namespace gsystem { // gsystem

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>::GSList()
: m_nSize(0), m_pFirst(GNULL)
{
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>::GSList(const DataT &data)
: m_nSize(0), m_pFirst(GNULL)
{
	AddFirst(data);
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>::GSList(DataT &&data)
: m_nSize(0), m_pFirst(GNULL)
{
	AddFirst(GForward<DataT>(data));
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>::GSList(const GSList<DataT, NodeT> &list)
: m_nSize(0), m_pFirst(GNULL)
{
	NodeT *node = list.m_pFirst;
	if (GNULL == node)
	{
		return;
	}

	NodeT *new_node = new NodeT(node->m_tData);
	m_pFirst = new_node;
	m_nSize = 1;
	node = node->m_pNext;
	while (node)
	{
		new_node->m_pNext = new NodeT(node->m_tData);
		new_node = new_node->m_pNext;
		node = node->m_pNext;

		m_nSize++;
	}
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>::GSList(GSList<DataT, NodeT> &&list)
: m_nSize(list.m_nSize), m_pFirst(list.m_pFirst)
{
	list.m_nSize = 0;
	list.m_pFirst = GNULL;
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>& GSList<DataT, NodeT>::operator=(const GSList<DataT, NodeT> &list)
{
	if (this == &list)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	NodeT *node = list.m_pFirst;
	if (GNULL == node)
	{
		return *this;
	}

	NodeT *new_node = new NodeT(node->m_tData);
	m_pFirst = new_node;
	m_nSize = 1;
	node = node->m_pNext;
	while (node)
	{
		new_node->m_pNext = new NodeT(node->m_tData);
		new_node = new_node->m_pNext;
		node = node->m_pNext;

		m_nSize++;
	}
	return *this;
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>& GSList<DataT, NodeT>::operator=(GSList<DataT, NodeT> &&list)
{
	if (this == &list)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	m_nSize = list.m_nSize;
	m_pFirst = list.m_pFirst;
	list.m_nSize = 0;
	list.m_pFirst = GNULL;
	return *this;
}

template<typename DataT, typename NodeT>
GINLINE GSList<DataT, NodeT>::~GSList()
{
	RemoveAll();
}

template<typename DataT, typename NodeT>
GINLINE gsize GSList<DataT, NodeT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gbool GSList<DataT, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::Invert()
{
	if (m_nSize <= 1) return;

	NodeT *cur_node = m_pFirst, *pre_node = GNULL, *next_node = m_pFirst;
	for (gsize i = 1; i <= m_nSize; i++)
	{
		next_node = cur_node->m_pNext;
		cur_node->m_pNext = pre_node;
		pre_node = cur_node;
		cur_node = next_node;
	}
	m_pFirst = pre_node;
	return;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertBefore(gsize pos, const DataT &data)
{
	GASSERT(pos != NULL_POS);
	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(data);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertBefore(gsize pos, DataT &&data)
{
	GASSERT(pos != NULL_POS);
	if (GNULL == m_pFirst || 0 == pos)
	{
		return AddFirst(GForward<DataT>(data));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertBefore(NodeT *node, const DataT &data)
{	
	GASSERT(node);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	if (pTmpNode1 == GNULL)
	{
		// ���Ҳ����������κβ���
		return;
	}
	
	NodeT *pNewNode = new NodeT(data);
	pNewNode->m_pNext = node;
	if (pTmpNode2)
	{
		pTmpNode2->m_pNext = pNewNode;
	}
	if (m_pFirst == node)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertBefore(NodeT *node, DataT &&data)
{
	GASSERT(node);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	if (pTmpNode1 == GNULL)
	{
		// ���Ҳ����������κβ���
		return;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	pNewNode->m_pNext = node;
	if (pTmpNode2)
	{
		pTmpNode2->m_pNext = pNewNode;
	}
	if (m_pFirst == node)
	{
		m_pFirst = pNewNode;
	}
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertAfter(gsize pos, const DataT &data)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(data);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(data);
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertAfter(gsize pos, DataT &&data)
{
	if (GNULL == m_pFirst)
	{
		return AddFirst(GForward<DataT>(data));
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}

	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertAfter(NodeT *node, const DataT &data)
{
	GASSERT(node);
	NodeT *pNewNode = new NodeT(data);
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::InsertAfter(NodeT *node, DataT &&data)
{
	GASSERT(node);
	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::AddFirst(const DataT &data)
{
	NodeT *pNewNode = new NodeT(data);
	pNewNode->m_pNext = m_pFirst;
	m_pFirst = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::AddFirst(DataT &&data)
{
	NodeT *pNewNode = new NodeT(GForward<DataT>(data));
	pNewNode->m_pNext = m_pFirst;
	m_pFirst = pNewNode;
	++m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::AddLast(const DataT &data)
{
	InsertAfter(m_nSize - 1, data);
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::AddLast(DataT &&data)
{
	InsertAfter(m_nSize - 1, GForward<DataT>(data));
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::Remove(const NodeT *node)
{
	if (!node || m_nSize <= 0)
	{
		return;
	}

	if (node == m_pFirst)
	{
		RemoveFirst();
		return;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	if (GNULL == pTmpNode1)
	{
		return;
	}

	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::RemoveAt(gsize pos, DataT *data)
{
	GASSERT(pos < m_nSize);

	if (0 == pos)
	{
		RemoveFirst(data);
		return;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	if (data)
	{
		// ��Ԫ�����ߣ����ǿ���
		*data = GMove(pTmpNode1->m_tData);
	}
	delete pTmpNode1;
	pTmpNode1 = GNULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::RemoveFirst(DataT *data)
{
	if (!m_pFirst)
	{
		return;
	}

	NodeT *pTmpNode = m_pFirst;
	m_pFirst = m_pFirst->m_pNext;
	if (data)
	{
		// ��Ԫ�����ߣ����ǿ���
		*data = GMove(pTmpNode->m_tData);
	}
	delete pTmpNode;
	--m_nSize;
	return;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::RemoveLast(DataT *data)
{
	GASSERT(0 != m_nSize);
	RemoveAt(m_nSize - 1, data);
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::RemoveAll()
{
	if (m_nSize <= 0)
	{
		return;
	}

	NodeT *pTmpNode = GNULL;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		pTmpNode = m_pFirst->m_pNext;
		delete m_pFirst;
		m_pFirst = pTmpNode;
	}

	m_pFirst = GNULL;
	m_nSize = 0;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSList<DataT, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSList<DataT, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSList<DataT, NodeT>::GetLastNode()
{
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSList<DataT, NodeT>::GetLastNode() const
{
	const NodeT *pTmpNode1 = m_pFirst;
	const NodeT *pTmpNode2 = GNULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSList<DataT, NodeT>::GetNodeAt(gsize pos)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSList<DataT, NodeT>::GetNodeAt(gsize pos) const
{
	GASSERT(pos < m_nSize);
	const NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE DataT &GSList<DataT, NodeT>::GetFirstData()
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE const DataT &GSList<DataT, NodeT>::GetFirstData() const
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE DataT &GSList<DataT, NodeT>::GetLastData()
{
	NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE const DataT &GSList<DataT, NodeT>::GetLastData() const
{
	const NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE DataT &GSList<DataT, NodeT>::GetDataAt(gsize pos)
{
	NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE const DataT &GSList<DataT, NodeT>::GetDataAt(gsize pos) const
{
	const NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::SetDataAt(gsize pos, const DataT &data)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = data;
}

template<typename DataT, typename NodeT>
GINLINE gvoid GSList<DataT, NodeT>::SetDataAt(gsize pos, DataT &&data)
{
	GASSERT(pos < m_nSize);
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode = pTmpNode->m_pNext;
	}
	pTmpNode->m_tData = GForward<DataT>(data);
}

template<typename DataT, typename NodeT>
GINLINE gsize GSList<DataT, NodeT>::IndexOf(const DataT &data) const
{
	NodeT *pTmpNode = m_pFirst;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		if (data == pTmpNode->m_tData)
			return i;
		pTmpNode = pTmpNode->m_pNext;
	}
	return NULL_POS;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSList<DataT, NodeT>::Find(const DataT &data)
{
	NodeT *pTmpNode = m_pFirst;
	while (pTmpNode)
	{
		if (data == pTmpNode->m_tData)
			return pTmpNode;
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSList<DataT, NodeT>::Find(const DataT &data) const
{
	const NodeT *pTmpNode = m_pFirst;
	while (pTmpNode)
	{
		if (data == pTmpNode->m_tData)
			return pTmpNode;
		pTmpNode = pTmpNode->m_pNext;
	}
	return pTmpNode;
}

template<typename DataT, typename NodeT>
GINLINE gsize GSList<DataT, NodeT>::IndexOfCircle() const
{
	if (0 == m_nSize)
	{
		return NULL_POS;
	}

	NodeT* p1 = m_pFirst; // p1������Ϊ1
	NodeT* p2 = m_pFirst; // p2������Ϊ2

	/*�ж������Ƿ��л�����p1=p2ʱ˵�������л�����������ѭ�������p2һֱ�ߵ�������ͷ��˵��û�л���*/
	do
	{
		if (p1 != GNULL && p2 != GNULL && p2->m_pNext != GNULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return NULL_POS;
		}
	} while (p1 != p2);

	/*����������ڵ㣬�����䷵��*/
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}

	p2 = m_pFirst;
	gsize i = 0;
	for (i = 0; i < m_nSize; i++)
	{
		if (p1 == p2) break;
		p2 = p2->m_pNext;
	}
	return i;
}

template<typename DataT, typename NodeT>
GINLINE NodeT *GSList<DataT, NodeT>::FindCircle()
{
	if (0 == m_nSize)
	{
		return GNULL;
	}

	NodeT* p1 = m_pFirst; // p1������Ϊ1
	NodeT* p2 = m_pFirst; // p2������Ϊ2

	/*�ж������Ƿ��л�����p1=p2ʱ˵�������л�����������ѭ�������p2һֱ�ߵ�������ͷ��˵��û�л���*/
	do
	{
		if (p1 != GNULL && p2 != GNULL && p2->m_pNext != GNULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return GNULL;
		}
	} while (p1 != p2);

	/*����������ڵ㣬�����䷵��*/
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename DataT, typename NodeT>
GINLINE const NodeT *GSList<DataT, NodeT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return GNULL;
	}

	const NodeT* p1 = m_pFirst; // p1������Ϊ1
	const NodeT* p2 = m_pFirst; // p2������Ϊ2

	/*�ж������Ƿ��л�����p1=p2ʱ˵�������л�����������ѭ�������p2һֱ�ߵ�������ͷ��˵��û�л���*/
	do
	{
		if (p1 != GNULL && p2 != GNULL && p2->m_pNext != GNULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return GNULL;
		}
	} while (p1 != p2);

	/*����������ڵ㣬�����䷵��*/
	p2 = m_pFirst;
	while (p1 != p2)
	{
		p1 = p1->m_pNext;
		p2 = p2->m_pNext;
	}
	return p1;
}

template<typename DataT, typename NodeT>
GINLINE gsize GSList<DataT, NodeT>::IndexOfCross(const GLinkedList<DataT, NodeT> &list)
{
	if (0 == m_nSize || 0 == list.Size())
	{
		return NULL_POS;
	}

	if (IndexOfCircle() != NULL_POS
		|| list.IndexOfCircle() != NULL_POS)
	{
		return NULL_POS;
	}

	/*���ڶ����������ڵ�һ����������*/
	NodeT* pTail = m_pFirst;
	for (gsize i = 1; i < m_nSize; i++)
	{
		pTail = pTail->m_pNext;
	}

	pTail->m_pNext = const_cast<NodeT *>(list.GetFirstNode());
	m_nSize += list.Size();
	gsize i = IndexOfCircle();

	pTail->m_pNext = GNULL;
	m_nSize -= list.Size();
	return i;
}

template<typename DataT, typename NodeT>
DataT &GSList<DataT, NodeT>::operator[](gsize pos)
{
	return GetDataAt(pos);
}

template<typename DataT, typename NodeT>
const DataT &GSList<DataT, NodeT>::operator[](gsize pos) const
{
	return GetDataAt(pos);
}

} // namespace gsystem

#endif // _CORE_SINGLE_LINKED_LIST_INLINE_