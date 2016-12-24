// String的存储结构
#ifndef _CORE_STRING_STORE_
#define _CORE_STRING_STORE_

#include "CsGlobal.h"

#define CS_SMALL_STRING_MAX_SIZE		8

class CsString;
class CsSmallStringStore;
class CsNormalStringStore;
class CsBigStringStore;
class CsReferenceStringStore;
struct CsStringStore;

class CsSmallStringStore
{
	friend class CsString;

public:
	static const cs_size_t MAX_SIZE = CS_SMALL_STRING_MAX_SIZE - 1;
	static const cs_size_t NULL_POS = CS_SMALL_STRING_MAX_SIZE;

public:
	cs_bool Initialize();
	cs_bool Initialize(cs_char cChar);
	cs_bool Initialize(const cs_char *pStr, cs_size_t size);
	cs_bool Initialize(const CsSmallStringStore &sStr);

	cs_size_t Size() const;

	cs_char GetAt(cs_size_t pos) const;
	cs_char &GetAt(cs_size_t pos);

	const cs_char *Cursor(cs_size_t pos) const;
	cs_char *Cursor(cs_size_t pos);

	cs_cstring CString() const;
	cs_uint HashCode() const;

	cs_bool MakeTrim();
	cs_bool MakeTrimLeft();
	cs_bool MakeTrimRight();
	cs_bool MakeUpper();
	cs_bool MakeLower();

	cs_bool SwitchToNormal(CsNormalStringStore &) const;

private:
	cs_uint8 m_nSize;
	cs_char m_cStr[CS_SMALL_STRING_MAX_SIZE];
};

class CsNormalStringStore
{
	friend class CsString;

public:
	static const cs_size_t MAX_SIZE = CS_UINT16_MAX - 1;
	static const cs_size_t NULL_POS = CS_UINT16_MAX;

public:
	cs_bool Initialize(cs_size_t capacity); // 只分配内存，Size仍然为0
	cs_bool Initialize(const cs_char *pStr, cs_size_t size);
	cs_bool Initialize(const CsNormalStringStore &sStr);

	// 注意，这里应该保证size小于m_pStr分配的内存
	cs_bool CopyString(const cs_char *pStr, cs_size_t size);
	cs_bool Resize(cs_size_t size);

	cs_size_t Size() const;
	cs_void Free();

	cs_char GetAt(cs_size_t pos) const;
	cs_char &GetAt(cs_size_t pos);

	const cs_char *Cursor(cs_size_t pos) const;
	cs_char *Cursor(cs_size_t pos);

	cs_cstring CString() const;
	cs_uint HashCode() const;

	cs_bool MakeTrim();
	cs_bool MakeTrimLeft();
	cs_bool MakeTrimRight();
	cs_bool MakeUpper();
	cs_bool MakeLower();

	cs_bool CanSwithToSmall() const;
	cs_bool SwitchToSmall(CsSmallStringStore &) const;

private:
	cs_uint16 m_nSize;
	cs_char *m_pStr;
};

// TODO
class CsBigStringStore
{
	friend class CsString;

public:
	static const cs_size_t MAX_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_POS = CS_LIST_NULL_POS;

private:
	cs_size_t m_nSize;
	cs_pointer m_pStr;
};

// TODO
class CsReferenceStringStore
{
	friend class CsString;

public:
	static const cs_size_t MAX_SIZE = CS_LIST_MAX_SIZE;
	static const cs_size_t NULL_POS = CS_LIST_NULL_POS;

private:
	cs_size_t m_nSize;
	cs_pointer m_pStr;
};

struct CsStringStore
{
	enum TYPE
	{
		STRING_STORE_TYPE_VALUE_SMALL,
		STRING_STORE_TYPE_VALUE_NORMAL,
		STRING_STORE_TYPE_VALUE_BIG,
		STRING_STORE_TYPE_REFERENCE,
	};

	cs_byte m_nType;
	union
	{
		CsSmallStringStore		m_sSmallStr;	// 小字符串
		CsNormalStringStore		m_sNormalStr;	// 普通字符串
		CsBigStringStore		m_sBigStr;		// 大字符串
		CsReferenceStringStore	m_sRefStr;		// 引用字符串
	};

	static cs_void Free(CsStringStore &);
};

#endif // _CORE_STRING_STORE_