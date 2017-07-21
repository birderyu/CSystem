#ifndef _CORE_VECTOR_INLINE_
#define _CORE_VECTOR_INLINE_

#include "gutility.h"

namespace gsystem { // gsystem

template <typename T>
GINLINE GVector<T>::GVector()
: m_tArray(0), m_nHead(NULL_POS), m_nTail(0)
{

}

template <typename T>
GINLINE GVector<T>::GVector(gsize size)
: m_tArray(size), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename T>
GINLINE GVector<T>::GVector(gsize size, const T &data)
: m_tArray(size, data), m_nHead(0), m_nTail(size)
{
	if (size <= 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename T>
GINLINE GVector<T>::GVector(const GVector<T> &datas)
: m_tArray(datas.m_tArray, datas.m_nHead, datas.Size()), m_nHead(0), m_nTail(datas.Size())
{
	if (datas.Size() == 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
}

template <typename T>
GINLINE GVector<T>::GVector(GVector<T> &&datas)
: m_tArray(GMove(datas.m_tArray))
, m_nHead(datas.m_nHead)
, m_nTail(datas.m_nTail)
{
	datas.m_nHead = NULL_POS;
	datas.m_nTail = 0;
}

template <typename T>
GINLINE GVector<T> &GVector<T>::operator=(const GVector<T> &datas)
{
	if (this == &datas)
	{
		return *this;
	}
	// TODO
	return *this;
}

template <typename T>
GINLINE GVector<T> &GVector<T>::operator=(GVector<T> &&datas)
{
	if (this == &datas)
	{
		return *this;
	}
	// TODO
	return *this;
}

template <typename T> GINLINE
gvoid GVector<T>::Reserve(gsize capacity)
{
	Reserve(capacity, 0);
}

template <typename T> GINLINE
gvoid GVector<T>::Reserve(gsize capacity, gsize start)
{
	gsize old_capacity = Capacity();
	if (capacity <= old_capacity)
	{
		if (start == 0)
		{
			// ��������
			return;
		}
	}

	gsize old_size = Size();
	if (m_nHead == NULL_POS)
	{
		m_tArray.Resize(capacity);
	}
	else
	{
		// ɾȥǰ�������Ԫ��
		m_tArray.Resize(capacity, m_nHead, old_size, start);
		m_nHead = start;
		m_nTail = old_size + start;
	}
}

template <typename T> GINLINE
gvoid GVector<T>::Resize(gsize size)
{
	if (size > Capacity())
	{
		Reserve(size);
	}
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	m_nTail = size - m_nHead;
}

template <typename T>
GINLINE gsize GVector<T>::Size() const
{
	if (!Valid())
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename T>
GINLINE gsize GVector<T>::Capacity() const
{
	gsize arr_size = m_tArray.Size();
	if (m_nHead == NULL_POS)
	{
		return arr_size;
	}
	GASSERT(arr_size > m_nHead);
	return arr_size - m_nHead;
}

template <typename T>
GINLINE gbool GVector<T>::IsEmpty() const
{
	return Size() == 0;
}

template <typename T>
GINLINE gsize GVector<T>::RealPos(gsize pos) const
{
	if (m_nHead == NULL_POS)
	{
		return NULL_POS;
	}
	return m_nHead + pos;
}

template <typename T>
GINLINE gbool GVector<T>::Valid() const
{
	return m_nHead != NULL_POS
		&& m_nTail != 0
		&& m_nTail > m_nHead
		&& m_nTail <= m_tArray.Size();
}

template <typename T>
GINLINE gvoid GVector<T>::Clear()
{
	m_tArray.Clear();
	m_nHead = NULL_POS;
	m_nTail = 0;
}

template <typename T>
gvoid GVector<T>::Destroy()
{
	m_tArray.Destroy();
	m_nHead = NULL_POS;
	m_nTail = 0;
}

template <typename T>
GINLINE T &GVector<T>::GetAt(gsize pos)
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename T>
GINLINE const T &GVector<T>::GetAt(gsize pos) const
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray.GetAt(real_pos);
}

template <typename T>
GINLINE T *GVector<T>::CursorAt(gsize pos)
{
	gsize real_pos = m_nHead + pos;
	return m_tArray.CursorAt(real_pos);
}

template <typename T>
GINLINE const T *GVector<T>::CursorAt(gsize pos) const
{
	gsize real_pos = m_nHead + pos;
	return m_tArray.CursorAt(real_pos);
}

template <typename T>
GINLINE T &GVector<T>::operator[](gsize pos)
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename T>
GINLINE const T &GVector<T>::operator[](gsize pos) const
{
	GASSERT(pos < Size());
	gsize real_pos = RealPos(pos);
	GASSERT(real_pos != NULL_POS);
	return m_tArray[real_pos];
}

template <typename T>
GINLINE gvoid GVector<T>::PushBack(const T &data)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// ��Ҫ����
		// ����ԭ�����ݵ�һ���������
		Reserve(old_size + (old_size / 2 + 1));
	}

	m_tArray[m_nTail++] = data;
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename T>
GINLINE gvoid GVector<T>::PushBack(T &&data)
{
	gsize old_size = Size();
	if (old_size >= Capacity())
	{
		// ��Ҫ����
		// ����ԭ�����ݵ�һ���������
		Reserve(old_size + (old_size / 2 + 1));
	}

	// Ϊ�˴���headָ��null_pos�����⣬����ʹ��Resize������
	m_tArray[m_nTail++] = GForward<T>(data);
	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
}

template <typename T>
GINLINE gvoid GVector<T>::PushFront(const T &data)
{
	if (m_nHead == NULL_POS)
	{
		// ����
		Reserve(G_VECTOR_DEFAULT_CAPACITY);
		m_nHead = 0;
		m_nTail = 1;
		m_tArray[0] = data;
		return;
	}
	else if (m_nHead == 0)
	{
		// ����
		gsize old_size = Size();
		// ����ԭ�����ݵ�һ���������
		Reserve(old_size + (old_size / 2 + 1), 1);
	}
	m_tArray[--m_nHead] = data;
}

template <typename T>
GINLINE gvoid GVector<T>::PushFront(T &&data)
{
	if (m_nHead == NULL_POS)
	{
		// ����
		Reserve(G_VECTOR_DEFAULT_CAPACITY);
		m_nHead = 0;
		m_nTail = 1;
		m_tArray[0] = GForward<T>(data);
		return;
	}
	else if (m_nHead == 0)
	{
		// ����
		gsize old_size = Size();
		// ����ԭ�����ݵ�һ���������
		Reserve(old_size + (old_size / 2 + 1), 1);
	}
	m_tArray[--m_nHead] = GForward<T>(data);
}

template <typename T>
GINLINE gvoid GVector<T>::PopBack(T *data)
{
	if (!Valid())
	{
		return;
	}
	
	// �α�ǰ��
	--m_nTail;

	if (data)
	{
		// ��Ԫ�����ߣ����ǿ���
		*data = GMove(m_tArray[m_nTail]);
	}
	// ����Ԫ��
	GDestruct(&m_tArray[m_nTail]);
}

template <typename T>
GINLINE gvoid GVector<T>::PopBack(gsize size)
{
	while (size > 0)
	{
		PopBack();
		size--;
		if (m_nTail == 0)
		{
			return;
		}
	}
}

template <typename T>
GINLINE gvoid GVector<T>::PopFront(T *data)
{
	if (!Valid())
	{
		return;
	}
	if (data)
	{
		// ��Ԫ�����ߣ����ǿ���
		*data = GMove(m_tArray[m_nHead]);
	}
	// ����Ԫ��
	GDestruct(&m_tArray[m_nHead]);

	// �α����
	++m_nHead;
}

template <typename T>
GINLINE gvoid GVector<T>::PopFront(gsize size)
{
	while (size > 0)
	{
		PopFront();
		size--;
		if (m_nHead == m_nTail)
		{
			return;
		}
	}
}

template <typename T>
GINLINE gvoid GVector<T>::Append(const T &data)
{
	PushBack(data);
}

template <typename T>
GINLINE gvoid GVector<T>::Append(T &&data)
{
	PushBack(GForward<T>(data));
}

template <typename T>
GINLINE gvoid GVector<T>::Append(const GVector<T> &arr)
{
	gsize add_size = arr.Size();
	if (add_size == 0)
	{
		return;
	}

	gsize old_size = Size();
	gsize new_size = old_size + add_size;
	if (new_size >= Capacity())
	{
		// ��Ҫ����
		// ����ԭ�����ݵ�һ���������
		gsize temp = old_size + (old_size / 2 + 1);
		gsize new_capacity = temp > new_size ? temp : new_size;
		Reserve(new_capacity);
	}

	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	for (gsize i = 0; i < add_size; i++)
	{
		m_tArray[m_nTail++] = arr[i];
	}
}

template <typename T>
GINLINE gvoid GVector<T>::Append(GVector<T> &&arr)
{
	gsize add_size = arr.Size();
	if (add_size == 0)
	{
		return;
	}

	gsize old_size = Size();
	gsize new_size = old_size + add_size;
	if (new_size >= Capacity())
	{
		// ��Ҫ����
		// ����ԭ�����ݵ�һ���������
		gsize temp = old_size + (old_size / 2 + 1);
		gsize new_capacity = temp > new_size ? temp : new_size;
		Reserve(new_capacity);
	}

	if (m_nHead == NULL_POS)
	{
		m_nHead = 0;
	}
	for (gsize i = 0; i < add_size; i++)
	{
		m_tArray[m_nTail++] = GMove(arr[i]);
	}

	// arr.Destroy(); // Ϊ�˽�ʡʱ�䣬����Ҫ��arr����
}

template <typename T>
GINLINE typename GVector<T>::Iterator GVector<T>::Begin()
{
	return GVector<T>::Iterator(Head());
}

template <typename T>
GINLINE typename GVector<T>::ConstIterator GVector<T>::Begin() const
{
	return GVector<T>::ConstIterator(Head());
}

template <typename T>
GINLINE typename GVector<T>::ConstIterator GVector<T>::ConstBegin() const
{
	return GVector<T>::ConstIterator(Head());
}

template <typename T>
GINLINE typename GVector<T>::Iterator GVector<T>::End()
{
	return GVector<T>::Iterator(Tail());
}

template <typename T>
GINLINE typename GVector<T>::ConstIterator GVector<T>::End() const
{
	return GVector<T>::ConstIterator(Tail());
}

template <typename T>
GINLINE typename GVector<T>::ConstIterator GVector<T>::ConstEnd() const
{
	return GVector<T>::ConstIterator(Tail());
}

template <typename T>
GINLINE T &GVector<T>::First()
{
	GASSERT(Valid());
	return *Head();
}

template <typename T>
GINLINE const T &GVector<T>::First() const
{
	GASSERT(Valid());
	return *Head();
}

template <typename T>
GINLINE T &GVector<T>::Last()
{
	GASSERT(Valid());
	return *(Tail() - 1);
}

template <typename T>
GINLINE const T &GVector<T>::Last() const
{
	GASSERT(Valid());
	return *(Tail() - 1);
}

template <typename T>
GINLINE gbool GVector<T>::StartWith(const T &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return First() == data;
}

template <typename T>
GINLINE gbool GVector<T>::EndWith(const T &data) const
{
	if (IsEmpty())
	{
		return false;
	}
	return Last() == data;
}

template <typename T> GINLINE
gvoid GVector<T>::RemoveAt(gsize pos)
{
	gsize old_size = Size();
	GASSERT(old_size > 0);
	m_tArray.RemoveAt(RealPos(pos));
	if (old_size == 1 && m_nHead == 0)
	{
		m_nHead = NULL_POS;
		m_nTail = 0;
	}
	else
	{
		--m_nTail;
	}
}

template <typename T>
GINLINE T *GVector<T>::Head()
{
	if (!Valid())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nHead);
}

template <typename T>
GINLINE const T *GVector<T>::Head() const
{
	if (!Valid())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nHead);
}

template <typename T>
GINLINE T *GVector<T>::Tail()
{
	if (m_nTail > m_tArray.Size())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nTail);
}

template <typename T>
GINLINE const T *GVector<T>::Tail() const
{
	if (!Valid())
	{
		return GNULL;
	}
	return m_tArray.CursorAt(m_nTail);
}

template <typename T> GINLINE
guint GVector<T>::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::Vector);
}

template <typename T> GINLINE
gbool GVector<T>::Serialize(GArchive &archive) const
{
	if (!archive.Input())
	{
		return false;
	}

	archive.PushCode(ClassCode());
	gsize size = Size();
	archive << size;

	for (gsize i = 0; i < size; i++)
	{
		if (!GSerialize<T>(archive, GetAt(i)))
		{
			return false;
		}
	}

	return true;
}

template <typename T> GINLINE
gbool GVector<T>::Deserialize(GArchive &archive)
{
	if (!archive.Output())
	{
		return false;
	}
	if (archive.PopCode() != ClassCode())
	{
		return false;
	}
	gsize size = 0;
	archive >> size;
	Destroy(); // �����������
	Resize(size);

	for (gsize i = 0; i < size; i++)
	{
		if (!GDeserialize<T>(archive, GetAt(i)))
		{
			return false;
		}
	}

	return true;
}

} // namespace gsystem

#endif // _CORE_VECTOR_INLINE_