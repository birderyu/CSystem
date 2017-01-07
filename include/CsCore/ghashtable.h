#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "ghash.h"
#include "glist.h"
#include "gdynamicarray.h"
#include "gstructure.h"

#define G_HASH_TABLE_DEFAULT_MODULE_SIZE		0x10
#define G_HASH_TABLE_MAX_MODULE_SIZE			0x40000000
#define G_HASH_TABLE_DEFAULT_LOAD_FACTOR		0.75f

// һ��Ĭ�ϵ�hash�ڵ�
template<typename KeyT, typename ValueT>
struct GHashTableNode 
	: public GNextNodeT<GHashTableNode<KeyT, ValueT>>
	, public GPairNodeT<KeyT, ValueT>
	, public GNewT<GHashTableNode<KeyT, ValueT>>
{
	GHashTableNode(const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		GHashTableNode<KeyT, ValueT> *next = NULL);
};

/// ��ϣ��
template<typename KeyT, typename ValueT,
	typename HashT = GHashF<KeyT>,
	typename CompareT = GEqualToF<KeyT>,
	typename NodeT = GHashTableNode<KeyT, ValueT>>
class GHashTable
	: public GObject
{
public:
	// ��ϣNode��Node�ļ���
	typedef NodeT Node;
	typedef GList<NodeT *> Nodes;
	typedef GList<const NodeT *> ConstNodes;

private:
	// ��ϣ��ͻ
	struct GHashSlot 
		: public GNewT<GHashSlot>
	{
		NodeT *m_pHead;
		gsize m_nSize;
		CompareT m_fCompare;

		GHashSlot() :m_pHead(NULL), m_nSize(0) {}
		GHashSlot(const GHashSlot &slot) :m_pHead(slot.m_pHead), m_nSize(slot.m_nSize)
		~GHashSlot() { Free(); }

		GHashSlot &operator=(const GHashSlot &slot)
		{
			m_pHead = slot.m_pHead;
			m_nSize = slot.m_nSize;
			return *this;
		}

		gvoid Free()
		{
			if (!m_pHead)
			{
				return;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				m_pHead = pNode;
				pNode = pNode->m_pNext;
				delete m_pHead;
			}
			m_pHead = NULL;
			m_nSize = 0;
		}
		gsize Size()
		{
			return m_nSize;
		}
		gbool IsEmpty()
		{
			return m_pHead == NULL || m_nSize == 0;
		}
		
		gbool Search(const KeyT &key, gbool allowRepeat, Nodes &nodes)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_fCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (!allowRepeat)
					{
						// ���������ظ�Ԫ��
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
		gbool Search(const KeyT &key, gbool allowRepeat, ConstNodes &nodes) const
		{
			if (!m_pHead)
			{
				return false;
			}
			const NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_fCompare(pNode->m_tKey, key))
				{
					nodes.PushBack(pNode);
					if (!allowRepeat)
					{
						// ���������ظ�Ԫ��
						return true;
					}
				}
				pNode = pNode->m_pNext;
			}
			return !nodes.IsEmpty();
		}
				
		// ֻ������һ��
		NodeT *SearchFirst(const KeyT &key)
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_fCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return NULL;
		}
		const NodeT *SearchFirst(const KeyT &key) const
		{
			if (!m_pHead)
			{
				return false;
			}
			const NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_fCompare(pNode->m_tKey, key))
				{
					return pNode;
				}
				pNode = pNode->m_pNext;
			}
			return NULL;
		}
		gbool Contains(const KeyT &key) const
		{
			if (!m_pHead)
			{
				return false;
			}
			NodeT *pNode = m_pHead;
			while (pNode)
			{
				if (m_fCompare(pNode->m_tKey, key))
				{
					return true;
				}
			}
			return false;
		}

		NodeT *Insert(const KeyT &key, const ValueT &value, gbool allowRepeat, gbool &realInsert)
		{
			if (allowRepeat)
			{
				// allowRepeat = true���������ظ�Ԫ��
				// ֱ�Ӳ��뵽����
				NodeT *node = new NodeT(key, value);
				node->m_pNext = m_pHead;
				m_pHead = node;
				m_nSize++;
				realInsert = true;
				return node; // �����ɹ�
			}
			else
			{
				// allowRepeat = false�����������ظ�Ԫ��
				NodeT *pnode = SearchFirst(key);
				if (!pnode)
				{
					// �����ڣ����뵽����
					NodeT *node = new NodeT(key, value);
					node->m_pNext = m_pHead;
					m_pHead = node;
					m_nSize++;
					realInsert = true;
					return node;
				}
				else
				{
					// �Ѵ��ڣ�������ͬ�Ľڵ�
					pnode->m_tValue = value;
					realInsert = false;
					return pnode;
				}
			}
		}
		// ����ɾ�����ݵ����������򷵻�0
		gsize Delete(const KeyT &key, gbool allowRepeat)
		{
			if (!m_pHead)
			{
				return 0;
			}

			if (allowRepeat)
			{
				// allowRepeat = true���������ظ�Ԫ��
				gsize node_size = 0;
				NodeT *pNode = m_pHead;
				NodeT *preNode = NULL;
				while (pNode)
				{
					if (m_fCompare(pNode->m_tKey, key))
					{
						// ɾ���ڵ�
						if (DeleteAt(pNode, preNode))
						{
							node_size++;
						}
						pNode = preNode->m_pNext;
					}
					else
					{
						preNode = pNode;
						pNode = pNode->m_pNext;
					}
				}
				return node_size;
			}
			else
			{
				// allowRepeat = false�����������ظ�Ԫ��
				NodeT *pNode = m_pHead;
				NodeT *preNode = NULL;
				while (pNode)
				{
					if (m_fCompare(pNode->m_tKey, key))
					{
						// ɾ���ڵ㲢����
						if (DeleteAt(pNode, preNode))
						{
							return 1;
						}
					}
					preNode = pNode;
					pNode = pNode->m_pNext;
				}
				return 0;
			}
			return 0;
		}

		// node :��ɾ���Ľڵ�
		// preNode����ɾ���ڵ��ǰ���ڵ�
		gbool DeleteAt(NodeT *node, NodeT *preNode)
		{
			if (!node)
			{
				return false;
			}

			if (preNode)
			{
				preNode->m_pNext = node->m_pNext;
			}
			else
			{
				m_pHead = node->m_pNext;
			}
			
			delete node;
			m_nSize--;
			return true;
		}
	};

public:
	GHashTable(gsize module = G_HASH_TABLE_DEFAULT_MODULE_SIZE, 
		gfloat factor = G_HASH_TABLE_DEFAULT_LOAD_FACTOR,
		gbool allowRepeat = false);
	~GHashTable();

	NodeT *FirstNode();
	const NodeT *FirstNode() const;
	NodeT *NextNode(NodeT *node);
	const NodeT *NextNode(NodeT *node) const;

	NodeT *Find(const KeyT &key);
	const NodeT *Find(const KeyT &key) const;
	gbool Find(const KeyT &key, Nodes &nodes);
	gbool Find(const KeyT &key, ConstNodes &nodes) const;

	virtual NodeT *Insert(const KeyT &key, const ValueT &value);
	virtual gvoid Delete(const KeyT &key);

protected:
	virtual gsize IndexOf(const KeyT &key) const;

private:
	gsize m_nModule;
	gsize m_nSize; // ʵ��Ԫ�صĸ���
	gfloat m_nFactor;	// ��������
	GDynamicArray<GHashSlot*> m_tBuckets;
	HashT m_fHash;
	gbool m_bAllowRepeat; // �Ƿ������ظ�
};

#include "ghashtable.inl"

#undef G_HASH_TABLE_DEFAULT_LOAD_FACTOR
#undef G_HASH_TABLE_MAX_MODULE_SIZE
#undef G_HASH_TABLE_DEFAULT_MODULE_SIZE

#endif // _CORE_HASH_TABLE_H_