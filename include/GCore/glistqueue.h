#ifndef _CORE_LIST_QUEUE_H_
#define _CORE_LIST_QUEUE_H_

#include "gqueue.h"
#include "gdlist.h"

namespace gsystem { // gsystem

template <typename DataT>
class GListQueue
	: public GQueue<DataT>
{
public:
	GListQueue();
	GListQueue(const GListQueue<DataT> &queue);
	GListQueue(GListQueue<DataT> &&queue);
	GListQueue<DataT>& operator=(const GListQueue<DataT> &queue);
	GListQueue<DataT>& operator=(GListQueue<DataT> &&queue);

	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Destroy();
	gvoid Clear();

	// ���
	gvoid EnQueue(const DataT &data);
	gvoid EnQueue(DataT &&data);

	// ����
	gvoid DeQueue(DataT *data = GNULL);

	const DataT &Head() const;
	DataT &Head();

private:
	GDList<DataT> m_tList;
};

} // namespace gsystem

#include "inline/glistqueue.inl"

#endif // _CORE_LIST_QUEUE_H_