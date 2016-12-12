/// �������ֽ���

#ifndef _CORE_BYTES_H_
#define _CORE_BYTES_H_

#include "CsObject.h"
#include "CsStructure.h"
#include "CsBlock.h"

#define CS_BYTES_DEFAULT_BUF_SIZE 4096
#define CS_BYTES_DEFAULT_ADD_SIZE 512

class CS_API CsBytes 
	: public CsObject
	, public CsListT<CsBytes>
{
public:
	CsBytes(cs_size_t nCapacity = CS_BYTES_DEFAULT_BUF_SIZE,
		cs_size_t nAddSize = CS_BYTES_DEFAULT_ADD_SIZE);
	CsBytes(const CsBytes &tBytes);
	~CsBytes();

	cs_bool Reserve(cs_size_t);
	cs_void Clear();

	cs_bool Valid() const;
	cs_bool IsEmpty() const;
	cs_size_t Size() const;
	cs_size_t Capacity() const;

	cs_bool ReadFrom(const cs_byte *pBuf, cs_size_t len);
	cs_bool WriteTo(cs_size_t len, cs_byte *&pBuf);

	/// д��������ֽ���
	CsBytes &operator<<(cs_bool);
	CsBytes &operator<<(cs_char);
	CsBytes &operator<<(cs_schar);
	CsBytes &operator<<(cs_uchar);
	CsBytes &operator<<(cs_wchar);
	CsBytes &operator<<(cs_short);
	CsBytes &operator<<(cs_ushort);
	CsBytes &operator<<(cs_int);
	CsBytes &operator<<(cs_uint);
	CsBytes &operator<<(cs_long);
	CsBytes &operator<<(cs_ulong);
	CsBytes &operator<<(cs_longlong);
	CsBytes &operator<<(cs_ulonglong);
	CsBytes &operator<<(cs_float);
	CsBytes &operator<<(cs_double);
	CsBytes &operator<<(cs_decimal);
	CsBytes &operator<<(const CsString &);

	/// �Ӷ������ֽ�����д��
	CsBytes &operator>>(cs_bool &);
	CsBytes &operator>>(cs_char &);
	CsBytes &operator>>(cs_schar &);
	CsBytes &operator>>(cs_uchar &);
	CsBytes &operator>>(cs_wchar &);
	CsBytes &operator>>(cs_short &);
	CsBytes &operator>>(cs_ushort &);
	CsBytes &operator>>(cs_int &);
	CsBytes &operator>>(cs_uint &);
	CsBytes &operator>>(cs_long &);
	CsBytes &operator>>(cs_ulong &);
	CsBytes &operator>>(cs_longlong &);
	CsBytes &operator>>(cs_ulonglong &);
	CsBytes &operator>>(cs_float &);
	CsBytes &operator>>(cs_double &);
	CsBytes &operator>>(cs_decimal &);
	CsBytes &operator>>(CsString &);

private:
	cs_byte *Head() const;
	cs_byte *Tail() const;

private:
	// ͷָ�룬ָ����Ԫ�أ���ʼֵΪNULL
	cs_size_t m_nHeadCursor;
	//cs_pointer m_nHeadCursor;

	// βָ�룬ָ��ĩβԪ�ص���һλ����ʼֵΪNULL_POS
	cs_size_t m_nTailCursor;
	//cs_pointer m_nTailCursor;

	// ÿ������ʱ�Ĳ�����Ԫ
	cs_size_t m_nAddSize;

	// �ڴ��
	CsBlock m_tBlock;
};

#undef CS_BYTES_DEFAULT_ADD_SIZE
#undef CS_BYTES_DEFAULT_BUF_SIZE

#endif // _CORE_BYTES_H_