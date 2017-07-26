#ifndef _CORE_LIST_QUEUE_H_
#define _CORE_LIST_QUEUE_H_

#include "gqueue.h"
#include "gdlist.h"

namespace gsystem { // gsystem

template <typename T>
class GListQueue
	: public GQueue<T>
{
public:
	GListQueue();
	GListQueue(const GListQueue<T> &queue);
	GListQueue(GListQueue<T> &&queue);
	GListQueue<T>& operator=(const GListQueue<T> &queue);
	GListQueue<T>& operator=(GListQueue<T> &&queue);

	gsize Size() const;
	gbool IsEmpty() const;

	gvoid Destroy();
	gvoid Clear();

	// ���
	gvoid EnQueue(const T &value);
	gvoid EnQueue(T &&value);

	// ����
	gbool DeQueue(T *value = GNULL);

	const T &Head() const;
	T &Head();

private:
	GDList<T> m_tList;
};

} // namespace gsystem

#include "inline/glistqueue.inl"

#endif // _CORE_LIST_QUEUE_H_