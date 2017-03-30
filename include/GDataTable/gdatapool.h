// ���ݳ�

#include "GCore/ghashtable.h"

namespace gsystem {
namespace data {

template<typename DataT, gsize GROW_SIZE = 1024>
class GDataPool
{
public:
	GDataPool()
	{

	}

	~GDataPool()
	{
		for (GList<GDynamicArray<DataT> *>::Iterator iter = m_tMemory.Begin();
			iter != m_tMemory.End(); iter++)
		{
			GDynamicArray<DataT> *arr = *iter;
			delete arr;
		}
	}

	DataT *Alloc(gsize size)
	{
		DataT *alloc = GNULL;
		// ���ȴӻ���վ�л����ڴ�
		GHashTable<gsize, GArrayStack<DataT *>>::Node *node = m_tRecycle.Find(size);
		if (GNULL == node)
		{
			// 
			if (GNULL == m_pCursor)
			{
				// ���·����ڴ�
				gsize real_alloc_size = GROW_SIZE > size ? GROW_SIZE : size;
				GDynamicArray<DataT> *arr = new GDynamicArray<DataT>(real_alloc_size);
				m_tMemory.PushBack(arr);
				if (real_alloc_size != size)
				{
					m_pCursor = arr;
					//m_nCursor = 
				}
				return arr->CursorAt(0);
			}
			else
			{

			}
			
		}
		else
		{
			node->m_tValue.Pop(&alloc);
			if (node->m_tValue.IsEmpty())
			{
				m_tRecycle.Delete(size);
			}
		}
		return alloc;
	}

	gvoid Free(DataT *free, gsize size)
	{
		GHashTable<gsize, GArrayStack<DataT *>>::Node *node = m_tRecycle.Find(size);
		if (GNULL == node)
		{
			GArrayStack<DataT *> list;
			list.Push(free);
			m_tRecycle.Insert(size, list);
		}
		else
		{
			node->m_tValue.Push(free);
		}
	}

private:
	// �ڴ����վ
	GHashTable<gsize, GArrayStack<DataT *>> m_tRecycle;

	// �ڴ��
	GList<GDynamicArray<DataT> *> m_tMemory;

	// ��ǰ���α�
	GDynamicArray<DataT> *m_pCursor;
	gsize m_nCursor;
};

}
}