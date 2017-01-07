// String�Ĵ洢�ṹ
#ifndef _CORE_STRING_STORE_
#define _CORE_STRING_STORE_

#include "gglobal.h"

#define CS_SMALL_STRING_MAX_SIZE		8

class GString;
class GSmallStringStore;
class GNormalStringStore;
class GBigStringStore;
class GReferenceStringStore;
struct GStringStore;

class GSmallStringStore
{
	friend class GString;

public:
	static const gsize MAX_SIZE = CS_SMALL_STRING_MAX_SIZE - 1;
	static const gsize NULL_POS = CS_SMALL_STRING_MAX_SIZE;

public:
	gbool Initialize();
	gbool Initialize(gchar cChar);
	gbool Initialize(const gchar *pStr, gsize size);
	gbool Initialize(const GSmallStringStore &sStr);

	gsize Size() const;

	gchar GetAt(gsize pos) const;
	gchar &GetAt(gsize pos);

	const gchar *Cursor(gsize pos) const;
	gchar *Cursor(gsize pos);

	gcstring CString() const;
	guint HashCode() const;

	gbool MakeTrim();
	gbool MakeTrimLeft();
	gbool MakeTrimRight();
	gbool MakeUpper();
	gbool MakeLower();

	gbool SwitchToNormal(GNormalStringStore &) const;

private:
	guint8 m_nSize;
	gchar m_cStr[CS_SMALL_STRING_MAX_SIZE];
};

class GNormalStringStore
{
	friend class GString;

public:
	static const gsize MAX_SIZE = G_UINT16_MAX - 1;
	static const gsize NULL_POS = G_UINT16_MAX;

public:
	gbool Initialize(gsize capacity); // ֻ�����ڴ棬Size��ȻΪ0
	gbool Initialize(const gchar *pStr, gsize size);
	gbool Initialize(const GNormalStringStore &sStr);

	// ע�⣬����Ӧ�ñ�֤sizeС��m_pStr������ڴ�
	gbool CopyString(const gchar *pStr, gsize size);
	gbool Resize(gsize size);

	gsize Size() const;
	gvoid Free();

	gchar GetAt(gsize pos) const;
	gchar &GetAt(gsize pos);

	const gchar *Cursor(gsize pos) const;
	gchar *Cursor(gsize pos);

	gcstring CString() const;
	guint HashCode() const;

	gbool MakeTrim();
	gbool MakeTrimLeft();
	gbool MakeTrimRight();
	gbool MakeUpper();
	gbool MakeLower();

	gbool CanSwithToSmall() const;
	gbool SwitchToSmall(GSmallStringStore &) const;

private:
	guint16 m_nSize;
	gchar *m_pStr;
};

// TODO
class GBigStringStore
{
	friend class GString;

public:
	static const gsize MAX_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_POS = G_LIST_NULL_POS;

private:
	gsize m_nSize;
	gpointer m_pStr;
};

// TODO
class GReferenceStringStore
{
	friend class GString;

public:
	static const gsize MAX_SIZE = G_LIST_MAX_SIZE;
	static const gsize NULL_POS = G_LIST_NULL_POS;

private:
	gsize m_nSize;
	gpointer m_pStr;
};

struct GStringStore
{
	enum TYPE
	{
		STRING_STORE_TYPE_VALUE_SMALL,
		STRING_STORE_TYPE_VALUE_NORMAL,
		STRING_STORE_TYPE_VALUE_BIG,
		STRING_STORE_TYPE_REFERENCE,
	};

	gbyte m_nType;
	union
	{
		GSmallStringStore		m_sSmallStr;	// С�ַ���
		GNormalStringStore		m_sNormalStr;	// ��ͨ�ַ���
		GBigStringStore		m_sBigStr;		// ���ַ���
		GReferenceStringStore	m_sRefStr;		// �����ַ���
	};

	static gvoid Free(GStringStore &);
};

#endif // _CORE_STRING_STORE_