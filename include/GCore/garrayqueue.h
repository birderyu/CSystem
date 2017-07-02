// ʹ������ʵ�ֵĶ���
#ifndef _CORE_ARRAY_QUEUE_H_
#define _CORE_ARRAY_QUEUE_H_

#include "gqueue.h"
#include "gdynamicarray.h"

namespace gsystem { // gsystem

template <typename DataT>
class GArrayQueue
	: public GQueue<DataT>
{
public:
	GArrayQueue(gsize capacity = 0);
	GArrayQueue(const GArrayQueue<DataT> &queue);
	GArrayQueue(GArrayQueue<DataT> &&queue);
	GArrayQueue<DataT>& operator=(const GArrayQueue<DataT> &queue);
	GArrayQueue<DataT>& operator=(GArrayQueue<DataT> &&queue);

	gbool IsEmpty() const;
	gsize Size() const;

	gvoid Clear();
	gvoid Destroy();

	gvoid EnQueue(const DataT &data);
	gvoid EnQueue(DataT &&data);

	gvoid DeQueue(DataT *data = GNULL);

	const DataT &Head() const;
	DataT &Head();
	
private:
	gsize Capacity() const;
	gvoid Reserve(gsize capacity);

private:
	gsize m_nHead; // ����
	gsize m_nTail; // ��β����һλ
	GDynamicArray<DataT> m_tArray;
};

} // namespace gsystem

#include "inline/garrayqueue.inl"

#endif // _CORE_ARRAY_QUEUE_H_
