#ifndef _CORE_SINGLE_LINKED_LIST_INLINE_
#define _CORE_SINGLE_LINKED_LIST_INLINE_

template<typename DataT, typename NodeT>
inline GSingleLinkedList<DataT, NodeT>::GSingleLinkedList()
: m_nSize(0), m_pFirst(NULL)
{
}

template<typename DataT, typename NodeT>
inline GSingleLinkedList<DataT, NodeT>::GSingleLinkedList(const DataT &data)
: m_nSize(0), m_pFirst(NULL)
{
	AddFirst(data);
}

template<typename DataT, typename NodeT>
inline GSingleLinkedList<DataT, NodeT>::GSingleLinkedList(const GSingleLinkedList<DataT, NodeT> &other)
: m_nSize(0), m_pFirst(NULL)
{
	if (other.m_nLength > 0)
	{
		for (gsize i = 0; i < other.m_nLength; i++)
		{
			AddLast(other.GetAt(i));
		}
	}
}

template<typename DataT, typename NodeT>
inline GSingleLinkedList<DataT, NodeT>& GSingleLinkedList<DataT, NodeT>::operator=(const GSingleLinkedList<DataT, NodeT>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_nSize > 0)
	{
		RemoveAll();
	}

	if (other.m_nLength > 0)
	{
		for (gsize i = 0; i < other.m_nLength; i++)
		{
			AddLast(other.GetAt(i));
		}
	}
	return *this;
}

template<typename DataT, typename NodeT>
inline GSingleLinkedList<DataT, NodeT>::~GSingleLinkedList()
{
	RemoveAll();
}

template<typename DataT, typename NodeT>
inline gsize GSingleLinkedList<DataT, NodeT>::Size() const
{
	return m_nSize;
}

template<typename DataT, typename NodeT>
inline gbool GSingleLinkedList<DataT, NodeT>::IsEmpty() const
{
	return 0 == m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::Invert()
{
	if (m_nSize <= 1) return;

	NodeT *cur_node = m_pFirst, *pre_node = NULL, *next_node = m_pFirst;
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
inline gbool GSingleLinkedList<DataT, NodeT>::AddFirst(const DataT &data)
{
	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = m_pFirst;
	m_pFirst = pNewNode;
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GSingleLinkedList<DataT, NodeT>::AddLast(const DataT &data)
{
	return InsertAfter(m_nSize - 1, data);
}

template<typename DataT, typename NodeT>
inline gbool GSingleLinkedList<DataT, NodeT>::InsertBefore(gsize pos, const DataT &data)
{
	if (pos == NULL_POS)
	{
		return false;
	}

	if (NULL == m_pFirst || 0 == pos)
	{
		return AddFirst(data);
	}

	GASSERT(pos < m_nSize);
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = pTmpNode1;
	pTmpNode2->m_pNext = pNewNode;

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GSingleLinkedList<DataT, NodeT>::InsertBefore(NodeT *node, const DataT &data)
{	
	if (!node)
	{
		return false;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	if (pTmpNode1 == NULL)
	{
		// ���Ҳ����������κβ���
		return false;
	}
	
	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
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
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GSingleLinkedList<DataT, NodeT>::InsertAfter(gsize pos, const DataT &data)
{
	if (NULL == m_pFirst)
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
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = pTmpNode->m_pNext;
	pTmpNode->m_pNext = pNewNode;

	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gbool GSingleLinkedList<DataT, NodeT>::InsertAfter(NodeT *node, const DataT &data)
{
	if (NULL == node)
	{
		return false;
	}

	NodeT *pNewNode = new NodeT(data);
	if (!pNewNode)
	{
		return false;
	}
	pNewNode->m_pNext = node->m_pNext;
	node->m_pNext = pNewNode;
	++m_nSize;
	return true;
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::Remove(NodeT *node)
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
	NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		if (pTmpNode1 == node)
		{
			break;
		}
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}

	if (NULL == pTmpNode1)
	{
		return;
	}

	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::RemoveAt(gsize pos)
{
	GASSERT(pos < m_nSize);

	if (0 == pos)
	{
		RemoveFirst();
		return;
	}

	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	for (gsize i = 0; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	pTmpNode2->m_pNext = pTmpNode1->m_pNext;
	delete pTmpNode1;
	pTmpNode1 = NULL;
	--m_nSize;
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::RemoveFirst()
{
	if (!m_pFirst)
	{
		return;
	}

	NodeT *pTmpNode = m_pFirst;
	m_pFirst = m_pFirst->m_pNext;

	delete pTmpNode;
	--m_nSize;
	return;
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::RemoveLast()
{
	GASSERT(0 != m_nSize);
	RemoveAt(m_nSize - 1);
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::RemoveAll()
{
	if (m_nSize <= 0)
	{
		return;
	}

	NodeT *pTmpNode = NULL;
	for (gsize i = 0; i < m_nSize; ++i)
	{
		pTmpNode = m_pFirst->m_pNext;
		delete m_pFirst;
		m_pFirst = pTmpNode;
	}

	m_pFirst = NULL;
	m_nSize = 0;
}

template<typename DataT, typename NodeT>
inline NodeT *GSingleLinkedList<DataT, NodeT>::GetFirstNode()
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
inline const NodeT *GSingleLinkedList<DataT, NodeT>::GetFirstNode() const
{
	return m_pFirst;
}

template<typename DataT, typename NodeT>
inline NodeT *GSingleLinkedList<DataT, NodeT>::GetLastNode()
{
	NodeT *pTmpNode1 = m_pFirst;
	NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
inline const NodeT *GSingleLinkedList<DataT, NodeT>::GetLastNode() const
{
	const NodeT *pTmpNode1 = m_pFirst;
	const NodeT *pTmpNode2 = NULL;
	while (pTmpNode1)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->m_pNext;
	}
	return pTmpNode2;
}

template<typename DataT, typename NodeT>
inline NodeT *GSingleLinkedList<DataT, NodeT>::GetNodeAt(gsize pos)
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
inline const NodeT *GSingleLinkedList<DataT, NodeT>::GetNodeAt(gsize pos) const
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
inline DataT &GSingleLinkedList<DataT, NodeT>::GetFirstData()
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &GSingleLinkedList<DataT, NodeT>::GetFirstData() const
{
	GASSERT(m_pFirst);
	return m_pFirst->m_tData;
}

template<typename DataT, typename NodeT>
inline DataT &GSingleLinkedList<DataT, NodeT>::GetLastData()
{
	NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &GSingleLinkedList<DataT, NodeT>::GetLastData() const
{
	const NodeT *pTail = GetLastNode();
	GASSERT(pTail);
	return pTail->m_tData;
}

template<typename DataT, typename NodeT>
inline DataT &GSingleLinkedList<DataT, NodeT>::GetDataAt(gsize pos)
{
	NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
inline const DataT &GSingleLinkedList<DataT, NodeT>::GetDataAt(gsize pos) const
{
	const NodeT *node = GetNodeAt(pos);
	GASSERT(node);
	return node->m_tData;
}

template<typename DataT, typename NodeT>
inline gvoid GSingleLinkedList<DataT, NodeT>::SetDataAt(gsize pos, const DataT &data)
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
inline gsize GSingleLinkedList<DataT, NodeT>::IndexOf(const DataT &data) const
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
inline NodeT *GSingleLinkedList<DataT, NodeT>::Find(const DataT &data)
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
inline const NodeT *GSingleLinkedList<DataT, NodeT>::Find(const DataT &data) const
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
inline gsize GSingleLinkedList<DataT, NodeT>::IndexOfCircle() const
{
	if (0 == m_nSize)
	{
		return NULL_POS;
	}

	NodeT* p1 = m_pFirst; // p1������Ϊ1
	NodeT* p2 = m_pFirst; // p2������Ϊ2

	/*�ж������Ƿ��л�����p1=p2ʱ˵�������л�����������ѭ�������p2һֱ�ߵ�����ͷ��˵��û�л���*/
	do
	{
		if (p1 != NULL && p2 != NULL && p2->m_pNext != NULL)
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
inline NodeT *GSingleLinkedList<DataT, NodeT>::FindCircle()
{
	if (0 == m_nSize)
	{
		return NULL;
	}

	NodeT* p1 = m_pFirst; // p1������Ϊ1
	NodeT* p2 = m_pFirst; // p2������Ϊ2

	/*�ж������Ƿ��л�����p1=p2ʱ˵�������л�����������ѭ�������p2һֱ�ߵ�����ͷ��˵��û�л���*/
	do
	{
		if (p1 != NULL && p2 != NULL && p2->m_pNext != NULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return NULL;
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
inline const NodeT *GSingleLinkedList<DataT, NodeT>::FindCircle() const
{
	if (0 == m_nSize)
	{
		return NULL;
	}

	const NodeT* p1 = m_pFirst; // p1������Ϊ1
	const NodeT* p2 = m_pFirst; // p2������Ϊ2

	/*�ж������Ƿ��л�����p1=p2ʱ˵�������л�����������ѭ�������p2һֱ�ߵ�����ͷ��˵��û�л���*/
	do
	{
		if (p1 != NULL && p2 != NULL && p2->m_pNext != NULL)
		{
			p1 = p1->m_pNext;
			p2 = p2->m_pNext->m_pNext;
		}
		else
		{
			return NULL;
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
inline gsize GSingleLinkedList<DataT, NodeT>::IndexOfCross(const GLinkedList<DataT, NodeT> &list)
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

	/*���ڶ���������ڵ�һ���������*/
	NodeT* pTail = m_pFirst;
	for (gsize i = 1; i < m_nSize; i++)
	{
		pTail = pTail->m_pNext;
	}

	pTail->m_pNext = const_cast<NodeT *>(list.GetFirstNode());
	m_nSize += list.Size();
	gsize i = IndexOfCircle();

	pTail->m_pNext = NULL;
	m_nSize -= list.Size();
	return i;
}

template<typename DataT, typename NodeT>
DataT &GSingleLinkedList<DataT, NodeT>::operator[](gsize pos)
{
	return GetDataAt(pos);
}

template<typename DataT, typename NodeT>
const DataT &GSingleLinkedList<DataT, NodeT>::operator[](gsize pos) const
{
	return GetDataAt(pos);
}

#endif // _CORE_SINGLE_LINKED_LIST_INLINE_