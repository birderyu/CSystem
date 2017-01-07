// ʹ�ö�̬����ʵ��
#ifndef _CORE_VECTOR_H_
#define _CORE_VECTOR_H_

#include "gdynamicarray.h"

#define G_VECTOR_DEFAULT_CAPACITY 16

template <typename DataT>
class GVector final
	: GListT<GVector<DataT>>
	, public GObject
{
public:
	class ConstIterator;
	class Iterator
	{
		friend class ConstIterator;
	public:
		inline Iterator() : m_pData(NULL) {}
		inline Iterator(DataT *data) : m_pData(data) {}
		inline explicit Iterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		inline DataT &operator*() const { return *m_pData; }
		inline DataT *operator->() const { return m_pData; }
		inline DataT &operator[](gsize pos) const { return *(m_pData + pos); }
		inline bool operator==(const Iterator &iter) const { return m_pData == iter.m_pData; }
		inline bool operator!=(const Iterator &iter) const { return m_pData != iter.m_pData; }
		inline bool operator<(const Iterator &iter) const { return m_pData < iter.m_pData; }
		inline bool operator<=(const Iterator &iter) const { return m_pData <= iter.m_pData; }
		inline bool operator>(const Iterator &iter) const { return m_pData > iter.m_pData; }
		inline bool operator>=(const Iterator &iter) const { return m_pData >= iter.m_pData; }
		inline Iterator &operator++() { ++m_pData; return *this; }
		inline Iterator  operator++(gint) { DataT *data = m_pData; ++m_pData; return data; }
		inline Iterator &operator--() { m_pData--; return *this; }
		inline Iterator  operator--(gint) { DataT *data = m_pData; m_pData--; return data; }
		inline Iterator &operator+=(gint i) { m_pData += i; return *this; }
		inline Iterator &operator-=(gint i) { m_pData -= i; return *this; }
		inline Iterator  operator+(gint i) const { return Iterator(m_pData + i); }
		inline Iterator  operator-(gint i) const { return Iterator(m_pData - i); }
		inline gint operator-(const Iterator &iter) const { return m_pData - iter.m_pData; }
		inline operator DataT*() const { return m_pData; }

	private:
		DataT *m_pData;
	};

	class ConstIterator
	{
		friend class Iterator;
	public:
		inline ConstIterator() : m_pData(NULL) {}
		inline ConstIterator(const DataT *data) : m_pData(data) {}
		inline explicit ConstIterator(const Iterator &iter) : m_pData(iter.m_pData) {}

		inline const DataT &operator*() const { return *m_pData; }
		inline const DataT *operator->() const { return m_pData; }
		inline const DataT &operator[](gsize pos) const { return *(m_pData + pos); }
		inline gbool operator==(const ConstIterator &citer) const { return m_pData == citer.m_pData; }
		inline gbool operator!=(const ConstIterator &citer) const { return m_pData != citer.m_pData; }
		inline gbool operator<(const ConstIterator &citer) const { return m_pData < citer.m_pData; }
		inline gbool operator<=(const ConstIterator &citer) const { return m_pData <= citer.m_pData; }
		inline gbool operator>(const ConstIterator &citer) const { return m_pData > citer.m_pData; }
		inline gbool operator>=(const ConstIterator &citer) const { return m_pData >= citer.m_pData; }
		inline ConstIterator &operator++() { ++m_pData; return *this; }
		inline ConstIterator  operator++(gint) { const DataT *n = m_pData; ++m_pData; return n; }
		inline ConstIterator &operator--() { m_pData--; return *this; }
		inline ConstIterator  operator--(gint) { const DataT *data = m_pData; m_pData--; return data; }
		inline ConstIterator &operator+=(gint i) { m_pData += i; return *this; }
		inline ConstIterator &operator-=(gint i) { m_pData -= i; return *this; }
		inline ConstIterator  operator+(gint i) const { return ConstIterator(m_pData + i); }
		inline ConstIterator  operator-(gint i) const { return ConstIterator(m_pData - i); }
		inline int operator-(const ConstIterator &citer) const { return m_pData - citer.m_pData; }
		inline operator const DataT*() const { return m_pData; }

	private:
		const DataT *m_pData;
	};

	friend class Iterator;
	friend class ConstIterator;

public:
	GVector();
	explicit GVector(gsize size);
	explicit GVector(gsize size, const DataT &data);
	GVector(const GVector<DataT> &);
	gbool Reserve(gsize);
	gbool Resize(gsize);

	gsize Size() const;
	gsize Capacity() const;
	gbool IsEmpty() const;
	gvoid Clear(); // ������飬������������
	gvoid Dispose(); // ������������
	//gvoid Collect(); // ��������

	DataT &GetAt(gsize);
	const DataT &GetAt(gsize) const;

	DataT &operator[](gsize);
	const DataT &operator[](gsize) const;

	gvoid PushBack(const DataT &data);
	gvoid PushFront(const DataT &data);
	gvoid PopBack(DataT *data = NULL);
	gvoid PopBack(gsize size); // �Ӷ�β��ȥsize��Ԫ��
	gvoid PopFront(DataT *data = NULL);
	gvoid PopFront(gsize size); // �Ӷ��׳�ȥsize��Ԫ��

	gvoid	Append(const DataT &);
	gvoid	Append(const GVector<DataT> &);

	Iterator Begin();
	ConstIterator Begin() const;
	ConstIterator ConstBegin() const;
	Iterator End();
	ConstIterator End() const;
	ConstIterator ConstEnd() const;

	DataT &First();
	const DataT &First() const;
	DataT &Last();
	const DataT &Last() const;

	gbool StartWith(const DataT &) const;
	gbool EndWith(const DataT &) const;

	//Iterator Erase(const Iterator &iter);
	//Iterator Erase(const Iterator &begin, const Iterator &end);

	//gvoid RemoveAt(gsize);
	//gvoid Remove(gsize start, gsize size);
	//gvoid Remove(const DataT &);
	//gsize FirstIndexOf(const DataT &);
	//gsize LastIndexOf(const DataT &);

	DataT *Head();
	const DataT *Head() const;
	DataT *Tail();
	const DataT *Tail() const;

	//gvoid MemCopyFrom(const GVector<DataT> &);

private:
	gsize RealPos(gsize pos) const;
	gbool Valid() const;
	gbool Reserve(gsize, gsize start);

	// ��̬����
	GDynamicArray<DataT> m_tArray;

	// ͷָ�룬ָ����Ԫ�أ���ʼֵΪNULL_POS
	gsize m_nHead;

	// βָ�룬ָ��ĩβԪ�ص���һλ����ʼֵΪ0
	gsize m_nTail;
};

#include "gvector.inl"

#undef G_VECTOR_DEFAULT_CAPACITY

#endif // _CORE_VECTOR_H_