#ifndef _CORE_HASH_TABLE_H_
#define _CORE_HASH_TABLE_H_

#include "CsObject.h"
#include "CsHash.h"
#include "CsDynamicArray.h"
#include "CsStructure.h"

#define CS_HASH_DEFAULT_MODULE_SIZE		0x10
#define CS_HASH_MAX_MODULE_SIZE			0x40000000
#define CS_HASH_DEFAULT_LOAD_FACTOR		0.75f

template<typename KeyT, typename ValueT>
struct CsHashTableNode 
	: public CsSingleLinkedListNodeT<CsHashTableNode<KeyT, ValueT>>
	, public CsKeyValueNodeT<KeyT, ValueT>
	, public CsNewT<CsHashTableNode<KeyT, ValueT>>
{
	CsHashTableNode(const KeyT &key = KeyT(),
		const ValueT &value = ValueT(),
		CsHashTableNode<KeyT, ValueT> *next = NULL);
};

/// ��ϣ��
template<typename KeyT, typename ValueT,
	typename HashT = CsHashF<KeyT>,
	typename CompareT = CsEqualToF<KeyT>,
	typename NodeT = CsHashTableNode<KeyT, ValueT>>
class CsHashTable
	: public CsObject
{
public:
	// ��ϣNode�ļ���
	template<typename NodeT>
	class CsHashNodes
	{
	public:
		CsHashNodes(cs_size_t capacity = 0)
			:m_nLength(0)
		{
			if (capacity > 0)
			{
				m_tNodes.Resize(capacity, NULL);
			}
		}
		cs_void Add(NodeT *node)
		{
			if (m_nLength == m_tNodes.Size())
			{
				m_tNodes.Resize(m_nLength + m_nLength / 2 + 1);
			}
			m_tNodes[m_nLength++] = node;
		}
		cs_bool IsEmpty() const
		{
			return m_nLength == 0;
		}
		cs_size_t Size() const
		{
			return m_nLength;
		}
		NodeT *operator[](cs_size_t i)
		{
			return m_tNodes[i];
		}
		const NodeT *operator[](cs_size_t) const
		{
			return m_tNodes[i];
		}

	private:
		CsDynamicArray<NodeT*> m_tNodes;
		cs_size_t m_nLength;
	};
	
	typedef NodeT Node;
	typedef CsHashNodes<NodeT> Nodes;

private:
	// ��ϣ��ͻ
	template<typename KeyT, typename ValueT , typename CompareT, typename NodeT>
	struct CsHashSlot 
		: public CsNewT<CsHashSlot<KeyT, ValueT, CompareT, NodeT>>
	{
		NodeT *m_pHead;
		cs_size_t m_nLength;
		CompareT m_fCompare;

		CsHashSlot()
			:m_pHead(NULL), m_nLength(0)
		{

		}
		CsHashSlot(const CsHashSlot<KeyT, ValueT, CompareT, NodeT> &slot)
			:m_pHead(slot.m_pHead), m_nLength(slot.m_nLength)
		{

		}
		~CsHashSlot()
		{
			Free();
		}

		CsHashSlot<KeyT, ValueT, CompareT, NodeT> &operator=(const CsHashSlot<KeyT, ValueT, CompareT, NodeT> &slot)
		{
			m_pHead = slot.m_pHead;
			m_nLength = slot.m_nLength;
			return *this;
		}

		cs_void Free()
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
			m_nLength = 0;
		}
		
		// ��һ��nodeΪͷ��㣬����ǰ��nodeΪNULL
		cs_bool Search(const KeyT &key, cs_bool allowRepeat,
			CsHashNodes<NodeT> &nodes) const
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
					nodes.Add(pNode);
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
		NodeT *Search(const KeyT &key) const
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
		cs_bool Contains(const KeyT &key) const
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

		NodeT *Insert(const KeyT &key, const ValueT &value, cs_bool allowRepeat, cs_bool &realInsert)
		{
			if (allowRepeat)
			{
				// allowRepeat = true���������ظ�Ԫ��
				// ֱ�Ӳ��뵽����
				NodeT *node = new NodeT(key, value);
				node->m_pNext = m_pHead;
				m_pHead = node;
				m_nLength++;
				realInsert = true;
				return node; // �����ɹ�
			}
			else
			{
				// allowRepeat = false�����������ظ�Ԫ��
				NodeT *pnode = Search(key);
				if (!pnode)
				{
					// �����ڣ����뵽����
					NodeT *node = new NodeT(key, value);
					node->m_pNext = m_pHead;
					m_pHead = node;
					m_nLength++;
					realInsert = true;
					return node;
				}
				else
				{
					// �Ѵ��ڣ�������ͬ�Ľڵ�
					realInsert = false;
					return pnode;
				}
			}
		}
	};

public:
	CsHashTable(cs_size_t module = CS_HASH_DEFAULT_MODULE_SIZE, 
		cs_float factor = CS_HASH_DEFAULT_LOAD_FACTOR,
		cs_bool allowRepeat = false);
	~CsHashTable();

	NodeT *FirstNode() const;
	NodeT *NextNode(NodeT *node) const;

	virtual NodeT *Insert(const KeyT &key, const ValueT &value);

	NodeT *Find(const KeyT &key) const;
	cs_bool Find(const KeyT &key, Nodes &nodes) const;

protected:
	virtual cs_size_t IndexOf(const KeyT &key) const;

private:
	cs_size_t m_nModule;
	cs_size_t m_nLength; // ʵ��Ԫ�صĸ���
	cs_float m_nFactor;	// ��������
	CsDynamicArray<CsHashSlot<KeyT, ValueT, CompareT, NodeT>*> m_tBuckets;
	HashT m_fHash;
	cs_bool m_bAllowRepeat; // �����ظ�
};

#include "CsHashTable.inl"

#endif // _CORE_HASH_TABLE_H_