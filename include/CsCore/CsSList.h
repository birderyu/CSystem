#ifndef _CSCORE_SINGLE_LINK_H_
#define _CSCORE_SINGLE_LINK_H_

#include <assert.h>  
#include <crtdbg.h>  

template<typename T>
class CsSList;

template<typename T>
class CsSListNode
{
	friend class CsSList<T>;
public:
	T data;
	CsSListNode<T> *next;
	CsSListNode() : data(T()), next(NULL) {}
	CsSListNode(const T &initdata) : data(initdata), next(NULL) {}
	CsSListNode(const T &initdata, CsSListNode<T> *p) : data(initdata), next(p) {}
};

template<typename T>
class CsSList
{
	typedef CsSListNode<T> Node;

public:
	CsSList();
	CsSList(const T &initdata);
	CsSList(const CsSList<T>& other);
	CsSList<T>& operator=(const CsSList<T>& other);
	~CsSList();

public:
	void    Invert();
	int     IsEmpty() const;
	int     GetCount() const;
	int     InsertBefore(const int pos, const T data);
	int     InsertAfter(const int pos, const T data);
	int     AddHead(const T data);
	int     AddTail(const T data);
	void    RemoveAt(const int pos);
	void    RemoveHead();
	void    RemoveTail();
	void    RemoveAll();
	T&      GetTail();
	T       GetTail() const;
	T&      GetHead();
	T       GetHead() const;
	T&      GetAt(const int pos);
	T       GetAt(const int pos) const;
	void    SetAt(const int pos, T data);
	int     Find(const T data) const;
	int     FindCircle() const;
	int     FindCross(CsSList& testlist);

protected:
	int m_nCount;
	Node *m_pNodeHead;
};

template<typename T>
inline CsSList<T>::CsSList() : m_nCount(0), m_pNodeHead(NULL)
{
}

template<typename T>
inline CsSList<T>::CsSList(const T &initdata) : m_nCount(0), m_pNodeHead(NULL)
{
	AddHead(initdata);
}

template<typename T>
inline CsSList<T>::CsSList(const CsSList<T>& other) : m_nCount(0), m_pNodeHead(NULL)
{
	if (other.m_nCount>0)
	{
		for (int i = 1; i <= other.m_nCount; i++)
		{
			AddTail(other.GetAt(i));
		}
	}

}

template<typename T>
inline CsSList<T>& CsSList<T>::operator=(const CsSList<T>& other)
{
	if (this == &other)
	{
		return *this;
	}

	if (m_nCount>0)
	{
		RemoveAll();
	}

	if (other.m_nCount>0)
	{
		for (int i = 1; i <= other.m_nCount; i++)
		{
			AddTail(other.GetAt(i));
		}
	}

	return *this;


}

template<typename T>
inline CsSList<T>::~CsSList()
{
	RemoveAll();
}
//reverse the list  
template<typename T>
inline void CsSList<T>::Invert()
{
	if (m_nCount <= 1) return;

	CsSListNode<T> *curNod, *preNod, *nextNod;
	curNod = m_pNodeHead;
	preNod = NULL;
	for (int i = 1; i <= m_nCount; i++)
	{
		nextNod = curNod->next;
		curNod->next = preNod;
		preNod = curNod;
		curNod = nextNod;
	}
	m_pNodeHead = preNod;
	return;
}

template<typename T>
inline int CsSList<T>::IsEmpty() const
{
	return 0 == m_nCount;
}

template<typename T>
inline int CsSList<T>::AddHead(const T data)
{
	/*Node<T> *pNewNode;

	try{
	pNewNode = new Node<T>;
	}
	catch (std::bad_alloc&)
	{
	return 0;
	}


	pNewNode->data = data;
	pNewNode->next = m_pNodeHead;

	m_pNodeHead = pNewNode;
	++m_nCount;
	return 1;*/

	return InsertBefore(1, data);
}

template<typename T>
inline int CsSList<T>::AddTail(const T data)
{
	return InsertAfter(GetCount(), data);
}

// if success, return the position of the new node.  
// if fail, return 0.  
template<typename T>
inline int CsSList<T>::InsertBefore(const int pos, const T data)
{
	int i;
	int nRetPos;
	CsSListNode<T> *pTmpNode1;
	CsSListNode<T> *pTmpNode2;
	CsSListNode<T> *pNewNode;

	try{
		pNewNode = new CsSListNode<T>;
	}
	catch (std::bad_alloc&)
	{
		nRetPos = 0;
		return nRetPos;
	}

	pNewNode->data = data;

	// if the list is empty, replace the head node with the new node.  
	if (NULL == m_pNodeHead)
	{
		pNewNode->next = NULL;
		m_pNodeHead = pNewNode;
		nRetPos = 1;
		++m_nCount;
		return nRetPos;
	}

	// is pos range valid?  
	ASSERT(1 <= pos && pos <= m_nCount);

	// insert before head node?  
	if (1 == pos)
	{
		pNewNode->next = m_pNodeHead;
		m_pNodeHead = pNewNode;
		nRetPos = 1;
		++m_nCount;
		return nRetPos;
	}

	// if the list is not empty and is not inserted before head node,  
	// seek to the pos of the list and insert the new node before it.  
	pTmpNode1 = m_pNodeHead;
	for (i = 1; i < pos; ++i)
	{
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->next;
	}
	pNewNode->next = pTmpNode1;
	pTmpNode2->next = pNewNode;

	nRetPos = pos;
	++m_nCount;
	return nRetPos;
}

// if success, return the position of the new node.  
// if fail, return 0.  
template<typename T>
inline int CsSList<T>::InsertAfter(const int pos, const T data)
{
	int i;
	int nRetPos;
	CsSListNode<T> *pTmpNode;
	CsSListNode<T> *pNewNode;

	try{
		pNewNode = new CsSListNode<T>;
	}
	catch (std::bad_alloc&)
	{
		nRetPos = 0;
		return nRetPos;
	}

	pNewNode->data = data;

	// if the list is empty, replace the head node with the new node.  
	if (NULL == m_pNodeHead)
	{
		pNewNode->next = NULL;
		m_pNodeHead = pNewNode;
		nRetPos = 1;
		++m_nCount;
		return nRetPos;
	}

	// is pos range valid?  
	ASSERT(1 <= pos && pos <= m_nCount);

	// if the list is not empty,  
	// seek to the pos of the list and insert the new node after it.  
	pTmpNode = m_pNodeHead;
	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}
	pNewNode->next = pTmpNode->next;
	pTmpNode->next = pNewNode;

	nRetPos = pos + 1;
	++m_nCount;
	return nRetPos;
}

template<typename T>
inline int CsSList<T>::GetCount() const
{
	return m_nCount;
}

template<typename T>
inline void CsSList<T>::RemoveAt(const int pos)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsSListNode<T> *pTmpNode1;
	CsSListNode<T> *pTmpNode2;

	pTmpNode1 = m_pNodeHead;

	// head node?  
	if (1 == pos)
	{
		m_pNodeHead = m_pNodeHead->next;
		delete pTmpNode1;
		--m_nCount;
		return;
	}

	for (i = 1; i < pos; ++i)
	{
		// we will get the previous node of the target node after  
		// the for loop finished, and it would be stored into pTmpNode2  
		pTmpNode2 = pTmpNode1;
		pTmpNode1 = pTmpNode1->next;
	}
	pTmpNode2->next = pTmpNode1->next;
	delete pTmpNode1;
	--m_nCount;
}

template<typename T>
inline void CsSList<T>::RemoveHead()
{
	ASSERT(0 != m_nCount);
	RemoveAt(1);
}

template<typename T>
inline void CsSList<T>::RemoveTail()
{
	ASSERT(0 != m_nCount);
	RemoveAt(m_nCount);
}

template<typename T>
inline void CsSList<T>::RemoveAll()
{
	int i;
	int nCount;
	CsSListNode<T> *pTmpNode;

	nCount = m_nCount;
	if (nCount == 0)
	{
		return;
	}
	for (i = 0; i < nCount; ++i)
	{
		pTmpNode = m_pNodeHead->next;
		delete m_pNodeHead;
		m_pNodeHead = pTmpNode;
	}

	m_pNodeHead = NULL;
	m_nCount = 0;
}

template<typename T>
inline T& CsSList<T>::GetTail()
{
	ASSERT(0 != m_nCount);

	int i;
	int nCount;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	nCount = m_nCount;
	for (i = 1; i < nCount; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	return pTmpNode->data;
}

template<typename T>
inline T CsSList<T>::GetTail() const
{
	ASSERT(0 != m_nCount);

	int i;
	int nCount;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	nCount = m_nCount;
	for (i = 1; i < nCount; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	return pTmpNode->data;
}

template<typename T>
inline T& CsSList<T>::GetHead()
{
	ASSERT(0 != m_nCount);
	return m_pNodeHead->data;
}

template<typename T>
inline T CsSList<T>::GetHead() const
{
	ASSERT(0 != m_nCount);
	return m_pNodeHead->data;
}

template<typename T>
inline T& CsSList<T>::GetAt(const int pos)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	return pTmpNode->data;
}

template<typename T>
inline T CsSList<T>::GetAt(const int pos) const
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}

	return pTmpNode->data;
}

template<typename T>
inline void CsSList<T>::SetAt(const int pos, T data)
{
	ASSERT(1 <= pos && pos <= m_nCount);

	int i;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	for (i = 1; i < pos; ++i)
	{
		pTmpNode = pTmpNode->next;
	}
	pTmpNode->data = data;
}

template<typename T>
inline int CsSList<T>::Find(const T data) const
{
	int i;
	int nCount;
	CsSListNode<T> *pTmpNode = m_pNodeHead;

	nCount = m_nCount;
	for (i = 0; i < nCount; ++i)
	{
		if (data == pTmpNode->data)
			return i + 1;
		pTmpNode = pTmpNode->next;
	}

	return 0;
}

/*判断链表是否有环，如果有环则返回环的首结点位置，否则返回0*/
template<typename T>
inline int CsSList<T>::FindCircle() const
{
	if (0 == m_nCount)
	{
		return 0;
	}

	CsSListNode<T>* p1 = m_pNodeHead;
	CsSListNode<T>* p2 = m_pNodeHead;

	/*判断链表是否有环，当p1=p2时说明链表有环，程序跳出循环。如果p2一直走到链表尽头则说明没有环。*/
	do{
		if (p1 != NULL&&p2 != NULL&&p2->next != NULL)
		{
			p1 = p1->next;
			p2 = p2->next->next;
		}
		else
			return 0;
	} while (p1 != p2);

	/*求出环的起点节点，并将其返回*/
	p2 = m_pNodeHead;
	while (p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}

	int i;
	p2 = m_pNodeHead;
	for (i = 1; i <= m_nCount; i++)
	{
		if (p1 == p2) break;
		p2 = p2->next;
	}
	return i;

}

/*判断两个链表是否交叉，如果交叉返回首个交叉节点位置（在本链表中的位置，而不是testlist中的位置），否则返回0。
假定：这两个链表本身均无环*/
template<typename T>
inline int CsSList<T>::FindCross(CsSList& testlist)
{
	if (0 == m_nCount || 0 == testlist.m_nCount)
	{
		return 0;
	}

	if (FindCircle() || testlist.FindCircle())
	{
		return 0;
	}

	/*将第二个链表接在第一个链表后面*/
	CsSListNode<T>* pTail = m_pNodeHead;
	for (int i = 1; i<m_nCount; i++)
	{
		pTail = pTail->next;
	}

	pTail = testlist.m_pNodeHead;
	m_nCount += testlist.m_nCount;

	int i = FindCircle();

	pTail = NULL;
	m_nCount -= testlist.m_nCount;
	return i;
}

#endif // _CSCORE_SINGLE_LINK_H_