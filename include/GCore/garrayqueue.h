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
	//���캯��
	GArrayQueue(gsize capacity)
		: m_nFront(0)
		, m_nRear(0)
		, m_tArray(capacity)
	{
		
	}
	//��������
	~GArrayQueue()
	{
		
	}

	gbool IsEmpty() const;
	int Size();         //���еĴ�С

	gvoid Clear();
	gvoid Dispose();

	DataT front();          //����Ԫ��
	bool pop();         //����
	bool push(T t);     //���
	

private:
	gsize m_nFront; // ����
	gsize m_nRear;	// ��β
	GDynamicArray<DataT> m_tArray;
};

} // namespace gsystem

#include "garrayqueue.inl"

#endif // _CORE_ARRAY_QUEUE_H_
