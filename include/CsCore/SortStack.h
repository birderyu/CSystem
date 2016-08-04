#ifndef _SORT_STACK_H_
#define _SORT_STACK_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

/// ����ջ
template <typename T>
class CSortStack
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

public:
	CSortStack();
	~CSortStack();

public:
	/// ��������
	/// ֻ����������������Ч��Χ��������Ȼ����Ч��
	bool reserve(const size_t len);

	/// ��Ч���ݵĳ���
	size_t size() const;

	/// ����
	size_t capacity() const;

	/// �Ƿ�Ϊ��
	bool empty() const;

	/// ��ռ�¼
	void clear();

	/// ����һ����¼
	bool insert(const T &t);

	/// ɾ��һ����¼
	bool remove(const T &t);

	/// �����±�ɾ��һ����¼
	bool removeAt(const size_t id);

	/// ����ĳ�����ݣ��������±꣬����-1��ʾ�����ݲ�����
	int search(const T &t) const;

	/// ȡβ��¼�ĵ�����
	inline const_iterator cfind(const T &t) const
	{
		int id = search(t);
		if (id < 0)
		{
			return NULL;
		}
		return at(id);
	}

	/// ȡ���׼�¼�����ظü�¼�ĵ�����
	inline const_iterator pop_front()
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + m_nHead++;
	}

	/// ȡ��β��¼�����ظü�¼�ĵ�����
	inline const_iterator pop_back()
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + (m_nTail--) - 1;
	}

	/// ȡ�׼�¼�ĵ�����
	inline const_iterator cbegin() const
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + m_nHead;
	}

	/// ȡβ��¼�ĵ�����
	inline const_iterator cend() const
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + m_nTail;
	}

	/// ��ȡָ��λ�õĵ�����
	inline const_iterator at(const size_t id) const
	{
		if (!valid())
		{
			return NULL;
		}
		return m_pData + real_id(id);
	}

	/// ͨ���±��ȡ���ݣ�ֻ����
	inline const T &operator[](const size_t id) const
	{
		assert(valid());
		return *(m_pData + real_id(id));
	}
	
private:
	/// ������Ч����
	/// ʹ��Ĭ�Ϲ��캯��������Ч���ݣ���Χ�ڵ����ݶ�����Ч��
	bool resize(const size_t len);

	/// �Ƿ���Ч
	bool valid() const;

	/// ��ȡ�������ݵ�λ��
	size_t insertPos(const T &t) const;

	/// ��ָ��λ�ò���һ������
	bool insertAt(const size_t id, const T &t);

	/// ���������ڴ���pData��pData��Ҫ��һ���Ѿ�����ĺϷ��ڴ�
	bool copyPartTo(const size_t start, const size_t len, T *pData) const;

	/// ʵ��ID
	size_t real_id(const size_t id) const;

private:
	// �ڴ���׵�ַ
	T *m_pData;

	// ͷָ�룬ָ����Ԫ�أ�Ĭ�������ָ��-1
	int m_nHead; 

	// βָ�룬ָ��ĩβԪ�ص���һλ��Ĭ�������ָ��-1
	int m_nTail;

	// �ڴ�ĳ���
	size_t m_nMemSize; 
};

template <typename T>
CSortStack<T>::CSortStack()
:m_pData(NULL), m_nHead(-1), m_nTail(-1), m_nMemSize(0)
{

}

template <typename T>
CSortStack<T>::~CSortStack()
{
	clear();
}

template <typename T>
bool CSortStack<T>::reserve(const size_t len)
{
	if (len <= capacity())
	{
		// ��������
		return true;
	}

	T *pData = (T*)malloc(sizeof(T)* len);
	if (!pData)
	{
		// ����ʧ��
		return false;
	}

	size_t n_size = size();
	if (m_pData && n_size > 0)
	{
		// ���ݾɵ����ݣ�ֻ������Ч���ݣ�
		if (!copyPartTo(m_nHead, n_size, pData))
		{
			return false;
		}
	}

	clear();
	m_pData = pData;
	m_nHead = 0;
	m_nTail = n_size;
	m_nMemSize = len;
	return true;
}

template <typename T>
bool CSortStack<T>::resize(const size_t len)
{
	if (len <= size())
	{
		return true;
	}
	if (len > capacity())
	{
		if (!reserve(len))
		{
			return false;
		}
	}
	for (size_t i = m_nTail; i < len - m_nHead; i++)
	{
		m_pData[i] = T();
	}
	m_nTail = len - m_nHead;
	return true;
}

template <typename T>
size_t CSortStack<T>::size() const
{
	if (m_nHead < 0 || m_nTail <= m_nHead)
	{
		return 0;
	}
	return m_nTail - m_nHead;
}

template <typename T>
size_t CSortStack<T>::capacity() const
{
	if (m_nHead < 0 || m_nMemSize <= m_nHead)
	{
		return 0;
	}
	return m_nMemSize - m_nHead;
}

template <typename T>
bool CSortStack<T>::empty() const
{
	return m_pData == NULL || size() == 0;
}

template <typename T>
void CSortStack<T>::clear()
{
	if (m_pData)
	{
		free(m_pData);
		m_pData = NULL;
	}
	m_nHead = m_nTail = -1;
	m_nMemSize = 0;
}

template <typename T>
bool CSortStack<T>::insert(const T &t)
{
	return insertAt(insertPos(t), t);
}

template <typename T>
bool CSortStack<T>::remove(const T &t)
{
	int id = search(t);
	if (id < 0)
	{
		return false;
	}
	return removeAt(id);
}

template <typename T>
bool CSortStack<T>::removeAt(const size_t id)
{
	size_t n_real_id = real_id(id);
	if (n_real_id < m_nHead || n_real_id >= m_nTail)
	{
		// ��Ч���ݣ�����ɾ��
		return true;
	}

	// ��βֱ���ƶ�ָ��
	if (n_real_id == m_nHead)
	{
		return pop_front() != NULL;
	}
	if (n_real_id == m_nTail - 1)
	{
		return pop_back() != NULL;
	}

	// ����λ�ã������ݺ���
	T bakup(m_pData[n_real_id]);
	if (!copyPartTo(n_real_id + 1, m_nTail - n_real_id - 1, m_pData + n_real_id))
	{
		return false;
	}
	m_nTail--;
	memcpy(m_pData + m_nTail, &bakup, sizeof(T));
	return true;
}

template <typename T>
int CSortStack<T>::search(const T &t) const
{
	if (!valid()
		|| t < m_pData[m_nHead]
		|| t > m_pData[m_nTail - 1])
	{
		return -1;
	}

	size_t start = m_nHead;
	size_t end = m_nTail - 1;
	while (start <= end)
	{
		size_t middle = start + ((end - start) >> 1);
		if (t == m_pData[middle])
		{
			return middle - m_nHead;
		}
		else if (t > m_pData[middle])
		{
			start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return -1;
}

template <typename T>
bool CSortStack<T>::valid() const
{
	return m_pData != NULL && m_nHead >= 0 && m_nTail > m_nHead && m_nTail <= m_nMemSize;
}

template <typename T>
size_t CSortStack<T>::insertPos(const T &t) const
{
	if (!valid()
		|| t < m_pData[m_nHead])
	{
		return 0;
	}
	if (t > m_pData[m_nTail - 1])
	{
		return m_nTail;
	}

	size_t start = m_nHead;
	size_t end = m_nTail - 1;

	while (start <= end)
	{
		size_t middle = start + ((end - start) >> 1);
		if (t == m_pData[middle] ||
			(middle - 1 >= m_nHead && t > m_pData[middle - 1] && t < m_pData[middle]))
		{
			return middle;
		}
		else if (t > m_pData[middle])
		{
			start = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return 0;
}

template <typename T>
bool CSortStack<T>::insertAt(const size_t id, const T &t)
{
	if (id >= capacity())
	{
		reserve(capacity() + 1);
	}
	size_t n_real_id = real_id(id); // ʵ���±꣨m_nHead + id��
	if (m_nTail < m_nMemSize)
	{
		// ����Ҫ�����µ��ڴ棬ֱ�Ӻ���
		if (copyPartTo(n_real_id, m_nTail - n_real_id, m_pData + n_real_id + 1))
		{
			m_pData[n_real_id] = t;
			m_nTail++;
		}
	}
	else
	{
		// �����µ��ڴ�
		size_t len = size() + 1; // ���ڴ�ĳ��ȣ�m_nTail - m_nHead + 1��
		T *pData = (T*)malloc(sizeof(T)* len);
		if (!pData)
		{
			// ���ڴ����ʧ��
			return false;
		}
		if (copyPartTo(m_nHead, id, pData))
		{
			if (copyPartTo(m_nHead + id, m_nTail - m_nHead - id, pData + id + 1))
			{
				clear();
				m_pData = pData;
				m_nHead = 0;
				m_nTail = len;
				m_nMemSize = len;
				m_pData[id] = t;
				return true;
			}
		}
	}
	return false;
}

template <typename T>
bool CSortStack<T>::copyPartTo(const size_t start, const size_t len, T *pData) const
{
	if (!pData || !m_pData || start >= m_nMemSize || len + start > m_nMemSize)
	{
		return false;
	}
	memcpy(pData, m_pData + start, sizeof(T)* len);
	return true;
}

template <typename T>
size_t CSortStack<T>::real_id(const size_t id) const
{
	return m_nHead + id;
}

#endif // _SORT_STACK_H_