#ifndef _CORE_ARRAY_STACK_INLINE_
#define _CORE_ARRAY_STACK_INLINE_

#include "gutility.h"

namespace gsystem { // gsystem

template<typename DataT>
GINLINE GArrayStack<DataT>::GArrayStack(gsize capacity)
	: m_TopCursor(NULL_POS), m_tArray(capacity)
{
	
}

template<typename DataT>
GINLINE GArrayStack<DataT>::GArrayStack(const GArrayStack<DataT> &stack)
	: m_TopCursor(stack.m_TopCursor)
	, m_tArray(stack.m_tArray)
{
	
}

template<typename DataT>
GINLINE GArrayStack<DataT>::GArrayStack(GArrayStack<DataT> &&stack)
	: m_TopCursor(stack.m_TopCursor)
	, m_tArray(GMove(stack.m_tArray))
{
	stack.m_TopCursor = NULL_POS;
}

template<typename DataT>
GINLINE GArrayStack<DataT>& GArrayStack<DataT>::operator=(const GArrayStack<DataT> &stack)
{
	if (this == &stack)
	{
		return *this;
	}
	m_tArray = stack.m_tArray;
	m_TopCursor = stack.m_TopCursor;
	return *this;
}

template<typename DataT>
GINLINE GArrayStack<DataT>& GArrayStack<DataT>::operator=(GArrayStack<DataT> &&stack)
{
	if (this == &stack)
	{
		return *this;
	}
	// ����Ҫ�ٵ������ٷ�������ΪGDynamicArray���ƶ��������Ѿ�������ԭ���ݵ�����
	m_tArray = GMove(stack.m_tArray);
	m_TopCursor = stack.m_TopCursor;
	stack.m_TopCursor = NULL_POS;
	return *this;
}

template<typename DataT>
GINLINE gsize GArrayStack<DataT>::Size() const
{
	if (m_TopCursor == NULL_POS)
	{
		return 0;
	}
	return m_TopCursor + 1;
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::IsEmpty() const
{
	return NULL_POS == m_TopCursor;
}

template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Clear()
{
	m_tArray.Clear();
	m_TopCursor = NULL_POS;
}

template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Destroy()
{
	m_tArray.Destroy();
	m_TopCursor = NULL_POS;
}

template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Push(const DataT &data)
{
	if (Fill())
	{
		// �����Ѿ������ˣ���Ҫ����
		Reserve(Capacity() + 1);
	}
	if (m_TopCursor == NULL_POS)
	{
		m_TopCursor = 0;
		m_tArray[m_TopCursor] = data;
	}
	else
	{
		m_tArray[++m_TopCursor] = data;
	}
}


template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Push(DataT &&data)
{
	if (Fill())
	{
		// �����Ѿ������ˣ���Ҫ����
		Reserve(Capacity() + 1);
	}
	if (m_TopCursor == NULL_POS)
	{
		m_TopCursor = 0;
		m_tArray[m_TopCursor] = GForward<DataT>(data);
	}
	else
	{
		m_tArray[++m_TopCursor] = GForward<DataT>(data);
	}
}

template<typename DataT>
GINLINE gvoid GArrayStack<DataT>::Pop(DataT* data = GNULL)
{
	if (IsEmpty())
	{
		return;
	}
	if (data)
	{
		// ��Ԫ�����ߣ����ǿ���
		*data = GMove(m_tArray[m_TopCursor]);
	}
	// ����Ԫ��
	GDestruct(&m_tArray[m_TopCursor]);

	// �α�ǰ��
	if (m_TopCursor == 0)
	{
		m_TopCursor = NULL_POS;
	}
	else
	{
		--m_TopCursor;
	}
}

template<typename DataT>
GINLINE const DataT &GArrayStack<DataT>::Top() const
{
	GASSERT(m_TopCursor != NULL_POS);
	return m_tArray[m_TopCursor];
}

template<typename DataT>
GINLINE DataT &GArrayStack<DataT>::Top()
{
	GASSERT(m_TopCursor != NULL_POS);
	return m_tArray[m_TopCursor];
}

template<typename DataT> GINLINE
gsize GArrayStack<DataT>::Capacity() const
{
	return m_tArray.Size();
}

template<typename DataT> GINLINE 
gbool GArrayStack<DataT>::Reserve(gsize capacity)
{
	if (IsEmpty()) 
	{
		// ջ�Ѿ�Ϊ���ˣ���������ջ
		Destroy();
	}

	gsize old_capacity = Capacity();
	old_capacity += (old_capacity / 2);
	return m_tArray.Resize(old_capacity > capacity ? old_capacity : capacity);
}

template<typename DataT>
GINLINE gbool GArrayStack<DataT>::Fill() const
{
	gsize capacity = Capacity();
	if (m_TopCursor == NULL_POS && 0 == capacity)
	{
		return true;
	}
	else if (m_TopCursor == NULL_POS)
	{
		return false;
	}
	return m_TopCursor >= capacity - 1;
}

} // namespace gsystem

#endif // _CORE_ARRAY_STACK_INLINE_