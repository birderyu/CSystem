#ifndef _CORE_BYTES_PRIVATE_H_
#define _CORE_BYTES_PRIVATE_H_

#include "CsEndian.h"
#include "CsBlock.h"
#include <string>

class CsString;

class CsBytes_Ex
{
public:
	CsBytes_Ex(cs_size_t nCapacity);
	CsBytes_Ex(const CsBytes_Ex &tBytes);
	~CsBytes_Ex();

	cs_void Clear();
	cs_bool IsEmpty() const;
	cs_byte *GetHead() const;
	cs_size_t Length() const;
	cs_size_t Capacity() const;
	cs_bool ReadFrom(const cs_byte *pBuf, cs_size_t len);
	cs_bool ReadFrom(cs_cstring str);
	cs_bool WriteTo(cs_size_t len, cs_byte *&pBuf);
	cs_bool WriteToStr(cs_char *str, cs_size_t maxsize);

	// ���յ��Ѿ��������õ��ڴ�
	cs_bool Collect();

	/// д��������ֽ���
	template<typename T>
	cs_bool operator<<(T val);

	/// �Ӷ������ֽ�����д��
	template<typename T>
	cs_bool operator>>(T &val);

private:
	cs_bool Valid() const;
	cs_byte *GetTail() const; // �ҵ���ǰ����λ��
	cs_bool Reserve(cs_size_t size);

	// ͷָ�룬ָ����Ԫ�أ�Ĭ�������ָ��-1
	int m_nHeadCursor;

	// βָ�룬ָ��ĩβԪ�ص���һλ��Ĭ�������ָ��-1
	int m_nTailCursor;

	// �ڴ��
	CsBlock m_tBlock;
};

template<typename T>
cs_bool CsBytes_Ex::operator << (T val)
{
#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN

	cs_size_t nSize = sizeof(T);
	cs_size_t nNewLen = Length() + nSize;
	if (nNewLen > Capacity())
	{
		if (!Reserve(nNewLen))
		{
			return false;
		}
	}
	memcpy(GetTail(), &val, nSize);
	m_nTailCursor += nSize;
	return true;
}

template<typename T>
cs_bool CsBytes_Ex::operator >> (T &val)
{
	cs_size_t nSize = sizeof(T);
	cs_int nNewLen = Length() - nSize;
	if (nNewLen < 0)
	{
		return false;
	}
	memcpy(&val, GetHead(), nSize);
	m_nHeadCursor += nSize;

#ifdef CS_LITTLE_ENDIAN
	val = CsEndian::Swap(val);
#endif // CS_LITTLE_ENDIAN
	return true;
}

#endif // _CORE_BYTES_PRIVATE_H_