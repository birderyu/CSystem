#ifndef _CORE_LIST_QUEUE_H_
#define _CORE_LIST_QUEUE_H_

#include "gqueue.h"
#include "gdoublelinkedlist.h"

namespace gsystem { // gsystem

/*��������Ķ��е�ADT*/
template <typename DataT>
class GListQueue
	: public GQueue<DataT>
{
public:
	GListQueue() : phead(GNULL), pend(GNULL), count(0){
		phead = new Node<T>();
		pend = phead;
		count = 0;
	}

	T front();          //����Ԫ��
	bool pop();         //����
	bool push(T t);     //���
	bool isEmpty();     //�п�
	int size();         //���еĴ�С
private:
	Node<T>* phead;
	Node<T>* pend;
	int count;    //����Ԫ�ص�����
};

template <typename T>
T GListQueue<T>::front()
{
	if (count != 0)
		return phead->next->value;
};

template <typename T>
bool GListQueue<T>::pop()
{
	if (count == 0)
		return false;
	Node<T>* pdel = phead->next;
	phead->next = pdel->next;
	delete pdel;
	count--;
	return true;
};

template <typename T>
bool GListQueue<T>::push(T t)
{
	Node<T>* pnode = new Node<T>(t);
	pend->next = pnode;
	pend = pnode;
	count++;
	return true;
};

template <typename T>
bool GListQueue<T>::isEmpty()
{
	if (count == 0)
		return true;
	else
		return false;
};

template <typename T>
int GListQueue<T>::size()
{
	return count;
};

} // namespace gsystem

#endif // _CORE_LIST_QUEUE_H_