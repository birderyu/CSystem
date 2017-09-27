#ifndef _CORE_STRING_8_BIT_H_
#define _CORE_STRING_8_BIT_H_

#include "gseries.h"
#include "gserializable.h"
#include "gstringlist.h"

namespace gsystem { // gsystem
	class GVariety;
} // namespace gsystem

namespace gsystem { // gsystem

/****************************************************************************
**
** @brief	��8���ֽ�Ϊ1���ַ����ַ�������
**
** ���ַ����е��ַ�������8���ֽ�Ϊ��λ�ģ���������Ա�ʾUTF-8��GBK������ַ�����Ĭ��ΪUTF-8
**
****************************************************************************/
class GAPI GString8 final 
	: public GSerializable
{
	friend class GVariety;
	friend GAPI GString8 operator+(const GString8 &s1, const GString8 &s2);
	friend GAPI gbool operator==(const GString8 &s1, const GString8 &s2);
	friend GAPI gbool operator!=(const GString8 &s1, const GString8 &s2);
	friend GAPI gbool operator>(const GString8 &s1, const GString8 &s2);
	friend GAPI gbool operator>=(const GString8 &s1, const GString8 &s2);
	friend GAPI gbool operator<(const GString8 &s1, const GString8 &s2);
	friend GAPI gbool operator<=(const GString8 &s1, const GString8 &s2);

public: // ��̬����
	static GString8 Number(gsmall num, gint base = 10);
	static GString8 Number(gusmall num, gint base = 10);
	static GString8 Number(gshort num, gint base = 10);
	static GString8 Number(gushort num, gint base = 10);
	static GString8 Number(gint num, gint base = 10);
	static GString8 Number(guint num, gint base = 10);
	static GString8 Number(glong num, gint base = 10);
	static GString8 Number(gulong num, gint base = 10);
	static GString8 Number(glonglong num, gint base = 10);
	static GString8 Number(gulonglong num, gint base = 10);
	static GString8 Number(gfloat num, gint base = 10);
	static GString8 Number(gdouble num, gint base = 10);
	static GString8 Number(gdecimal num, gint base = 10);

	static GString8 ReferenceOf(gcstring8 str);
	static GString8 ReferenceOf(const GString8 &str);
	static GString8 Format(gcstring8 format, ...);

public: // ���췽��
	GString8();
	GString8(gchar8 c);
	GString8(gcstring8 str);
	GString8(const GString8 &str);
	GString8(GString8 &&str);

public:
	gsize Size() const;
	gsize Length() const; // �ַ��ĳ���
	gbool IsEmpty() const;
	gchar8 &GetAt(gsize pos);
	const gchar8 &GetAt(gsize pos) const;
	gchar8 *CursorAt(gsize);
	const gchar8 *CursorAt(gsize) const;
	gvoid Resize(gsize size);
	gvoid Reserve(gsize size);
	gbool StartWith(gchar8 c) const;
	gbool EndWith(gchar8 c) const;
	gvoid Append(const GString8 &str);
	gvoid Append(GString8 &&str);

public: // �ַ�����Ϊ
	gbool Equals(const GString8 &str, gbool bIsSensitive = true) const;
	GString8 Trim() const;
	GString8 TrimLeft() const;
	GString8 TrimRight() const;
	GString8 ToUpper() const;
	GString8 ToLower() const;
	gcstring8 CString() const;
	GString8 &Replace(const GString8 &from, const GString8 &to, gbool bIsSensitive = true);
	// ignoreEmpty���Ƿ���Կո�; isSensitive����Сд�Ƿ�����
	GStringListT<GString8> Split(const GString8 &sep, gbool ignoreEmpty = false, gbool isSensitive = true) const;
	gsize Find(gchar8 c, gsize start = 0, gbool bIsSensitive = true) const;
	gsize Find(const GString8 &str, gsize start = 0, gbool bIsSensitive = true) const;
	GString8 SubString(gsize start, gsize length) const;

public: // ����ת��
	gsmall ToSmall(gbool *bIsOk = GNULL) const;
	gusmall ToUSmall(gbool *bIsOk = GNULL) const;
	gshort ToShort(gbool *bIsOk = GNULL) const;
	gushort ToUShort(gbool *bIsOk = GNULL) const;
	gint ToInt(gbool *bIsOk = GNULL) const;
	guint ToUInt(gbool *bIsOk = GNULL) const;
	glong ToLong(gbool *bIsOk = GNULL) const;
	gulong ToULong(gbool *bIsOk = GNULL) const;
	glonglong ToLongLong(gbool *bIsOk = GNULL) const;
	gulonglong ToULongLong(gbool *bIsOk = GNULL) const;
	gfloat ToFloat(gbool *bIsOk = GNULL) const;
	gdouble ToDouble(gbool *bIsOk = GNULL) const;
	glongdouble ToLongDouble(gbool *bIsOk = GNULL) const;

public: // Object
	//const GObject *Boxing() const;
	//GString ToString() const;

public: // Serializable
	guint ClassCode() const GNOEXCEPT;
	GString8 ClassName() const GNOEXCEPT;
	gbool Serialize(GArchive &archive) const;
	gbool Deserialize(GArchive &archive);

public: // ���������
	GString8 &operator=(const GString8 &str);
	GString8 &operator=(GString8 &&sStr);
	GString8 &operator+=(const GString8 &sStr);
	const gchar8 &operator[](gsize) const;
	gchar8 &operator[](gsize);

private: // ˽�з���
	GString8(gcstring8 str, gsize size);
	GString8(const GString8Data &str);
	GString8(GString8Data &&str);

private: // ˽�г�Ա
	//GString8Data m_tString;
	GSeries<gchar8, 8, true, 0> m_tString;
};

/// �����
GAPI GString8 operator+(const GString8 &s1, const GString8 &s2);
GAPI gbool operator==(const GString8 &s1, const GString8 &s2);
GAPI gbool operator!=(const GString8 &s1, const GString8 &s2);
GAPI gbool operator>(const GString8 &s1, const GString8 &s2);
GAPI gbool operator>=(const GString8 &s1, const GString8 &s2);
GAPI gbool operator<(const GString8 &s1, const GString8 &s2);
GAPI gbool operator<=(const GString8 &s1, const GString8 &s2);

} // namespace gsystem

#endif // _CORE_STRING_8_BIT_H_
