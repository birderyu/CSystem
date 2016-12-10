#ifndef _CORE_STRING_EX_H_
#define _CORE_STRING_EX_H_

#include "CsGlobal_Ex.h"
#include <sstream>

class CsSmallStr_Ex;
class CsNormalStr_Ex;
class CsBigStr_Ex;
class CsRefStr_Ex;

// ����32λ���ж�
#define CS_MIN_STRING_SIZE		8
#define CS_MAX_STRING_SIZE		20480

enum CS_STRING_EX_TYPE
{
	VALUE_STRING_SMALL = 0, // ֵ���ͣ�С�ַ�����ֱ�Ӵ洢��������
	VALUE_STRING_NORMAL,	// ֵ���ͣ���ͨ�ַ�����ʹ��һ���������ڴ�洢
	VALUE_STRING_BIG,		// ֵ���ͣ����ַ�����ʹ�÷ֶε��ڴ�洢
	REFERENCE_STRING = 99,	// �������ͣ��������ַ�����
};

// С�ַ���
class CsSmallStr_Ex
{
public:
	static cs_size_t MaxSize();

public:
	cs_bool Initialize();
	cs_bool Initialize(cs_char cChar);
	cs_bool Initialize(const cs_char *pStr, cs_size_t len);
	cs_bool Initialize(const CsSmallStr_Ex &sStr);
	cs_size_t Length() const;
	cs_char GetAt(cs_size_t id) const;
	cs_cstring CString() const;

	cs_bool MakeTrim();
	cs_bool MakeTrimLeft();
	cs_bool MakeTrimRight();
	cs_bool MakeUpper();
	cs_bool MakeLower();

	cs_bool SwitchToNormal(CsNormalStr_Ex &) const;

private:
	cs_uint8 m_nLength;
	cs_char m_cStr[CS_MIN_STRING_SIZE];
};

// ��ͨ���ַ���
class CsNormalStr_Ex
{
public:
	static cs_size_t MaxSize();

public:
	cs_bool Initialize(const cs_char *pStr, cs_size_t len);
	cs_bool Initialize(const CsNormalStr_Ex &sStr);

	// ����ȫ�ĳ�ʼ��
	// ��������������ֱ�ӽ�ָ���滻ΪpStr
	// ���������������кܴ����
	// pStr�ķ��䷽ʽ��������Free�е��ͷŷ�ʽ���Ӧ
	cs_bool Initialize_Quick(cs_char *pStr, cs_size_t len);

	cs_size_t Length() const;
	cs_void Free();
	cs_char GetAt(cs_size_t id) const;
	cs_cstring CString() const;

	cs_bool MakeTrim();
	cs_bool MakeTrimLeft();
	cs_bool MakeTrimRight();
	cs_bool MakeUpper();
	cs_bool MakeLower();

	cs_bool CanSwithToSmall() const;
	cs_bool SwitchToSmall(CsSmallStr_Ex &) const;

private:
	cs_uint16 m_nLength;
	cs_char *m_pStr;
};

// ���ַ���
class CsBigStr_Ex
{
private:
	cs_uint32 m_nLength;
	cs_pointer m_pStr;
};

// �������ַ���
class CsRefStr_Ex
{
private:
	cs_uint32 m_nLength;
	cs_pointer m_pStr;
};

/****************************************************************************
**
** CsString.h
**
** @struct: CsStringStore
** @module: CsCore
** @brief:  �ַ����洢�ṹ
**
** �ַ������͵Ĵ洢�ṹ����һ�����ϣ�union����һ����ʶ�ַ������͵ı���
** �ַ������Ͳ������µ��ڴ����
** 1.���ַ���������ʱ������ջ�ڴ棬ֱ�Ӵ洢�ڶ����У�������дЧ�ʣ��������ַ�������Ϊ��С�ַ�������
** 2.���ַ�����һ��ʱ�����������Ķ��ڴ棬����һ�������Ĵ洢�ռ䣬�������ַ�������Ϊ����ͨ�ַ�������
**   ��ʱ��һЩ���ڴ����չ��������Ƶ���������ַ����ĳ���ʱ������һ����Ч����ģ�
**   ʹ���ַ��������ࣨCsStringBuilder��ȥ����һ���ַ�����������Ч�ʣ�
** 3.���ַ����ĸ�������ʱ�����ò������Ķ��ڴ棬����һ���ڴ��������������ַ�������Ϊ�����ַ�������
**   ��ʱ���ַ������Ա�ʾ��һ��C�����ַ�����CString������ΪC�����ַ�����һ�������Ĵ洢�ռ䣻
** 4.���⣬Ϊ�˼ӿ��ַ����ķ����ٶȣ�ʹ��һ�����ýṹ��TODO��
**
****************************************************************************/
struct CsStringStore
{
	cs_byte m_nType;
	union
	{
		CsSmallStr_Ex	m_sSmallStr;	// С�ַ���
		CsNormalStr_Ex	m_sNormalStr;	// ��ͨ�ַ���
		CsBigStr_Ex		m_sBigStr;		// ���ַ���
		CsRefStr_Ex		m_sRefStr;		// �����ַ���
	};

	static cs_void Free(CsStringStore &);
};

class CS_API CsString_Ex :public CsNewT<CsString_Ex>
{
public:
	// 
	template <typename T>
	static cs_bool FromNum(T nNum, cs_int nBase, CsString_Ex &sStr);

public:
	CsString_Ex();
	CsString_Ex(cs_char cChar);
	CsString_Ex(const cs_char *pStr);
	CsString_Ex(const CsString_Ex &sStr);
	~CsString_Ex();

	cs_bool Initialize();
	cs_bool Initialize(cs_char cChar);
	cs_bool Initialize(const cs_char *pStr);
	cs_bool Initialize(const CsString_Ex &sStr);

	// �������ַ�����������д����ʱ����ת��Ϊ�������͵��ַ���
	cs_bool IsReference() const;

	// С�ַ���������ֱ�ӿ������ڴ濪��С
	cs_bool IsSmall() const;

	// ���ַ�������ʹ�������ڴ�洢���ַ���
	cs_bool IsLarge() const;

	// ʹ�������ڴ�洢���ַ���
	cs_bool IsSerial() const;

	// ����������ת����ֵ����
	CsString_Ex &ToValue();

	cs_char GetAt(cs_size_t id) const;
	cs_cstring CString() const;

	cs_size_t Length() const;
	cs_bool IsEmpty() const;

	CsString_Ex &MakeTrim();
	CsString_Ex &MakeTrimLeft();
	CsString_Ex &MakeTrimRight();

	CsString_Ex &MakeUpper();
	CsString_Ex &MakeLower();

	CsString_Ex &Replace(const cs_char *from, cs_size_t from_len, 
		const cs_char *to, cs_size_t to_len, 
		cs_bool bIsSensitive);
	CsString_Ex &Replace(cs_size_t start, cs_size_t length, 
		const cs_char *to, cs_size_t to_len, 
		cs_bool bIsSensitive);

	cs_uint64 HashCode() const;

	cs_bool operator==(const CsString_Ex &sStr) const
	{
		return false;
	}
	CsString_Ex &operator=(const CsString_Ex &sStr)
	{
		return *this;
	}
	CsString_Ex &operator+=(const CsString_Ex &sStr)
	{
		return *this;
	}
	
	//CsStringList Split(const CsString_Ex &sSep, cs_bool bIgnoreEmpty, cs_bool bIsSensitive) const;
	cs_int Find(cs_char c, cs_size_t start, cs_bool bIsSensitive) const;
	cs_int Find(const CsString_Ex &str, cs_size_t start, cs_bool bIsSensitive) const;
	CsString_Ex SubString(cs_size_t start, cs_size_t length);

	CsString_Ex &Switch(CS_STRING_EX_TYPE emType, cs_bool *pIsOk = NULL);

	// ���ݳ��ȼ����ַ���������
	CS_STRING_EX_TYPE GetTypeByLength(cs_size_t) const;

	// �����ڴ�
	CsString_Ex &Collect(cs_bool *pIsOk = NULL);
	
	template <typename T>
	T ToNum(cs_bool *isok = NULL) const;

private:
	cs_void Free();

	CsStringStore m_tStrMem;
};

template <typename T>
cs_bool CsString_Ex::FromNum(T nNum, cs_int nBase, CsString_Ex &sStr)
{
	std::ostringstream oss;
	if (nBase == 2)
	{

	}
	else if (nBase == 8)
	{
		oss << std::oct;
	}
	else if (nBase == 10)
	{
		oss << std::dec;
	}
	else if (nBase == 16)
	{
		oss << std::hex;
	}
	else
	{
		oss << std::dec;
	}
	oss << nNum;
	return sStr.Initialize(oss.str().c_str());
}

template <typename T>
T CsString_Ex::ToNum(cs_bool *isok) const
{
	std::istringstream iss(CString());
	T nNum;
	if (isok)
	{
		*isok = false;
	}
	if (iss >> nNum)
	{
		if (isok)
		{
			*isok = true;
		}
	}
	return nNum;
}

#endif // _CORE_STRING_EX_H_
