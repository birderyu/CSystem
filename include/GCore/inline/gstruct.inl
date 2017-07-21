#ifndef _CORE_STRUCTURE_INLINE_
#define _CORE_STRUCTURE_INLINE_

namespace gsystem { // gsystem

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
GINLINE GNextNodeT<NodeT>::GNextNodeT(NodeT *next)
: m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
GINLINE GPreviousNextNodeT<NodeT>::GPreviousNextNodeT(NodeT *previous, NodeT *next)
: m_pPrevious(previous), m_pNext(next)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
GINLINE GBinTreeNodeT<NodeT>::GBinTreeNodeT(NodeT *parent, NodeT *left, NodeT *right)
: m_pParent(parent), m_pLeft(left), m_pRight(left)
{

}

template<typename NodeT>
GINLINE const NodeT *GBinTreeNodeT<NodeT>::LeftSibling() const
{
	if (m_pParent)
	{
		return m_pParent->m_pLeft;
	}
	return GNULL;
}

template<typename NodeT>
GINLINE const NodeT *GBinTreeNodeT<NodeT>::RightSibling() const
{
	if (m_pParent)
	{
		return m_pParent->m_pRight;
	}
	return GNULL;
}

template<typename NodeT>
GINLINE const NodeT *GBinTreeNodeT<NodeT>::Next() const
{
	const NodeT *node = GNULL;
	if (m_pRight)
	{
		node = m_pRight;
		while (node->m_pLeft)
		{
			node = node->m_pLeft;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (const NodeT *)this;
		const NodeT *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pRight)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename NodeT>
GINLINE NodeT *GBinTreeNodeT<NodeT>::Next()
{
	NodeT *node = GNULL;
	if (m_pRight)
	{
		node = m_pRight;
		while (node->m_pLeft)
		{
			node = node->m_pLeft;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (NodeT *)this;
		NodeT *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pRight)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename NodeT>
GINLINE const NodeT *GBinTreeNodeT<NodeT>::Previous() const
{
	const NodeT *node = GNULL;
	if (m_pLeft)
	{
		node = m_pLeft;
		while (node->m_pRight)
		{
			node = node->m_pRight;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (const NodeT *)this;
		const NodeT *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pLeft)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename NodeT>
GINLINE NodeT *GBinTreeNodeT<NodeT>::Previous()
{
	NodeT *node = GNULL;
	if (m_pLeft)
	{
		node = m_pLeft;
		while (node->m_pRight)
		{
			node = node->m_pRight;
		}
	}
	else
	{
		if (!m_pParent)
		{
			return GNULL;
		}
		node = (NodeT *)this;
		NodeT *pnode = node->m_pParent;
		while (pnode && node == pnode->m_pLeft)
		{
			node = pnode;
			pnode = node->m_pParent;
		}
		node = pnode;
	}
	return node;
}

template<typename NodeT>
GINLINE const NodeT *GBinTreeNodeT<NodeT>::First() const
{
	if (!m_pLeft)
	{
		return (const NodeT *)this;
	}
	const NodeT *node = (const NodeT *)this;
	while (node->m_pLeft)
	{
		node = node->m_pLeft;
	}
	return node;
}

template<typename NodeT>
GINLINE NodeT *GBinTreeNodeT<NodeT>::First()
{
	if (!m_pLeft)
	{
		return (NodeT *)this;
	}
	NodeT *node = (NodeT *)this;
	while (node->m_pLeft)
	{
		node = node->m_pLeft;
	}
	return node;
}

template<typename NodeT>
GINLINE const NodeT *GBinTreeNodeT<NodeT>::Last() const
{
	if (!m_pRight)
	{
		return (const NodeT *)this;
	}
	const NodeT *node = (const NodeT *)this;
	while (node->m_pRight)
	{
		node = node->m_pRight;
	}
	return node;
}

template<typename NodeT>
GINLINE NodeT *GBinTreeNodeT<NodeT>::Last()
{
	if (!m_pRight)
	{
		return (NodeT *)this;
	}
	NodeT *node = (NodeT *)this;
	while (node->m_pRight)
	{
		node = node->m_pRight;
	}
	return node;
}

//////////////////////////////////////////////////////////////////////////
template<typename T>
GINLINE GValueNodeT<T>::GValueNodeT(const T &value)
	: m_tData(value)
{

}

template<typename T>
GINLINE GValueNodeT<T>::GValueNodeT(T &&value)
	: m_tData(GForward<T>(value))
{

}

//////////////////////////////////////////////////////////////////////////
template<typename NodeT>
GINLINE GChildNodeT<NodeT>::GChildNodeT(const NodeT *child)
: m_pChild(child)
{

}

//////////////////////////////////////////////////////////////////////////
template<typename KeyT, typename ValueT>
GINLINE GPairNodeT<KeyT, ValueT>::GPairNodeT(const KeyT &key, const ValueT &value)
	: m_tKey(key)
	, m_tValue(value)
{

}

template<typename KeyT, typename ValueT>
GINLINE GPairNodeT<KeyT, ValueT>::GPairNodeT(const KeyT &key, ValueT &&value)
	: m_tKey(key)
	, m_tValue(GForward<ValueT>(value))
{

}

} // namespace gsystem

#endif // _CORE_STRUCTURE_INLINE_