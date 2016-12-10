#ifndef _CORE_BINARY_SORT_TREE_INLINE_
#define _CORE_BINARY_SORT_TREE_INLINE_

template<typename KeyT, typename ValueT>
inline CsBinarySortTreeNode<KeyT, ValueT>::CsBinarySortTreeNode(
	const KeyT &key,
	const ValueT &value,
	CsBinarySortTreeNode<KeyT, ValueT> *parent,
	CsBinarySortTreeNode<KeyT, ValueT> *left,
	CsBinarySortTreeNode<KeyT, ValueT> *right)
	: CsBinaryTreeNodeT<CsBinarySortTreeNode<KeyT, ValueT>>(parent, left, right)
	, CsKeyValueNodeT<KeyT, ValueT>(key, value)
{

}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::~CsBinarySortTree()
{

}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT* CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find(const KeyT &key) const
{
	NodeT *root = m_pRoot;
	CS_ASSERT(root);

	// �ݹ�ʵ��
	//return Find_Recursive(key, root);

	// �ǵݹ�ʵ��
	return Find(key, root);
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT* CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::FirstNode() const
{
	NodeT *root = m_pRoot;
	CS_ASSERT(root);
	return root->First();
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT* CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::LastNode() const
{
	NodeT *root = m_pRoot;
	CS_ASSERT(root);
	return root->Last();
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT* CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert(const KeyT &key, const ValueT &value)
{
	NodeT *node = NULL;
	// �ݹ�ʵ��
	//Insert_Recursive(key, value, m_pRoot, node);
	// �ǵݹ�ʵ��
	Insert(key, value, m_pRoot, node);
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline cs_void CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete(const KeyT &key)
{
	// �ݹ�ʵ��
	//Delete_Recursive(key, m_pRoot);

	// �ǵݹ�ʵ��
	Delete(key, m_pRoot);
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT* CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find(const KeyT &key, NodeT *node) const
{
	while (node)
	{
		cs_int ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			break;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline cs_void CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins)
{
	NodeT* insert_point = NULL; // ����λ�õ�˫�׽ڵ�
	while (node)
	{
		insert_point = node;
		cs_int ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node = node->m_pLeft;
		}
		else if (ret > 0)
		{
			node = node->m_pRight;
		}
		else
		{
			node_ins = insert_point;
			return;
		}
	}

	// ��������ڵ�
	NodeT* insert_node = new NodeT(key, value);
	if (!insert_point)
	{
		//�������һ�ſ���
		m_pRoot = insert_node;
	}
	else
	{
		// �ҵ�����Ĳ���λ��
		cs_int ret = m_fCompare(key, insert_point->m_tKey);
		if (ret < 0)
		{
			insert_point->m_pLeft = insert_node;
		}
		else if (ret > 0)
		{
			insert_point->m_pRight = insert_node;
		}
		else
		{
			// ����������ͬ�����
		}
		insert_node->m_pParent = insert_point;
	}
	node_ins = insert_node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline cs_void CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete(const KeyT &key, NodeT *node)
{
	NodeT* delete_point = Find(key, node);
	if (!delete_point)
	{
		return;
	}
	if (delete_point->m_pLeft && delete_point->m_pRight)
	{
		// �ҵ��ڵ㣬�Ҹýڵ���������������
		NodeT *successor = delete_point->m_pRight->First();
		SwitchNode(delete_point, successor);
	}

	NodeT *delete_point_child = NULL;
	if (!delete_point->m_pLeft)
	{
		delete_point_child = delete_point->m_pRight;
	}
	else if (!delete_point->m_pRight)
	{
		delete_point_child = delete_point->m_pLeft;
	}

	NodeT *delete_point_parent = delete_point->m_pParent;
	if (delete_point_child)
	{
		delete_point_child->m_pParent = delete_point_parent;
	}

	if (!delete_point_parent)
	{
		m_pRoot = delete_point_child;
	}
	else
	{
		if (delete_point == delete_point_parent->m_pLeft)
		{
			delete_point_parent->m_pLeft = delete_point_child;
		}
		else
		{
			delete_point_parent->m_pRight = delete_point_child;
		}
	}
	delete delete_point;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT *CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Find_Recursive(const KeyT &key, NodeT *node) const
{
	if (!node)
	{
		return NULL;
	}
	cs_int ret = m_fCompare(key, node->m_tKey);
	if (ret < 0)
	{
		return Find(key, node->m_pLeft);
	}
	else if (ret > 0)
	{
		return Find(key, node->m_pRight);
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT *CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Insert_Recursive(const KeyT &key, const ValueT &value, NodeT *node, NodeT *&node_ins)
{
	if (NULL == node)
	{
		try
		{
			node = new NodeT(key, value);
		}
		catch (std::bad_alloc&)
		{
			return NULL;
		}

		node_ins = node;
		if (IsEmpty())
		{
			m_pRoot = node;
		}
	}
	else
	{
		cs_int ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			NodeT *_node = Insert_Recursive(key, value, node->m_pLeft, node_ins);
			if (_node && !node->m_pLeft)
			{
				node->m_pLeft = _node;
				_node->m_pParent = node;
			}
		}
		else if (ret > 0)
		{
			NodeT *_node = Insert_Recursive(key, value, node->m_pRight, node_ins);
			if (_node && !node->m_pRight)
			{
				node->m_pRight = _node;
				_node->m_pParent = node;
			}
		}
		else
		{
			// ��ȣ������κβ���
			node_ins = node;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline NodeT *CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::Delete_Recursive(const KeyT &key, NodeT *node)
{
	if (NULL == node)
	{
		// δ�ܲ��ҵ�Ԫ��
	}
	else
	{
		cs_int ret = m_fCompare(key, node->m_tKey);
		if (ret < 0)
		{
			node->m_pLeft = Delete_Recursive(key, node->m_pLeft);
		}
		else if (ret > 0)
		{
			node->m_pRight = Delete_Recursive(key, node->m_pRight);
		}
		else if (node->m_pLeft && node->m_pRight)
		{
			// �ҵ��ڵ㣬�Ҹýڵ���������������
			NodeT *temp = node->m_pRight->First();
			SwitchNode(node, temp);
			node->m_pRight = Delete_Recursive(key, temp->m_pRight);
		}
		else
		{
			// �ҵ��ڵ㣬�Ҹýڵ�ֻ��һ�����ӻ�û�к���
			NodeT *temp = node;
			if (!node->m_pLeft)
			{
				node = node->m_pRight;
			}
			else if (!node->m_pRight)
			{
				node = node->m_pLeft;
			}

			NodeT *pnode = temp->m_pParent;
			if (node)
			{
				node->m_pParent = pnode;
			}

			if (!pnode)
			{
				m_pRoot = node;
			}
			else
			{
				if (temp == pnode->m_pLeft)
				{
					pnode->m_pLeft = node;
				}
				else
				{
					pnode->m_pRight = node;
				}
			}
			delete temp;
		}
	}
	return node;
}

template<typename KeyT, typename ValueT, typename CompareT, typename NodeT>
inline cs_bool CsBinarySortTree<KeyT, ValueT, CompareT, NodeT>::SwitchNode(NodeT *node1, NodeT *node2)
{
	if (!node1 || !node2)
	{
		return false;
	}
	if (node1 == node2)
	{
		return true;
	}
	NodeT *pnode1 = node1->m_pParent;
	NodeT *pnode2 = node2->m_pParent;

	if (pnode1)
	{
		if (pnode1->m_pLeft == node1)
		{
			pnode1->m_pLeft = node2;
		}
		else
		{
			pnode1->m_pRight = node2;
		}
	}

	if (pnode2)
	{
		if (pnode2->m_pLeft == node2)
		{
			pnode2->m_pLeft = node1;
		}
		else
		{
			pnode2->m_pRight = node1;
		}
	}

	// ����node1��node2��˫��
	node1->m_pParent = pnode2;
	node2->m_pParent = pnode1;

	// ����node1��node2���ӵ�˫��
	if (node1->m_pLeft)
	{
		node1->m_pLeft->m_pParent = node2;
	}
	if (node1->m_pRight)
	{
		node1->m_pRight->m_pParent = node2;
	}

	if (node2->m_pLeft)
	{
		node2->m_pLeft->m_pParent = node1;
	}
	if (node2->m_pRight)
	{
		node2->m_pRight->m_pParent = node1;
	}

	// ����node1��node2�ĺ���
	NodeT *tmp = node1->m_pLeft;
	node1->m_pLeft = node2->m_pLeft;
	node2->m_pLeft = tmp;

	tmp = node1->m_pRight;
	node1->m_pRight = node2->m_pRight;
	node2->m_pRight = tmp;

	if (node1->m_pParent == NULL)
	{
		m_pRoot = node1;
	}
	if (node2->m_pParent == NULL)
	{
		m_pRoot = node2;
	}

	return true;
}

#endif // _CORE_BINARY_SORT_TREE_INLINE_