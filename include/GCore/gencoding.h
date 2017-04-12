#ifndef _CORE_ENCODING_H_
#define _CORE_ENCODING_H_

#include "gunordermap.h"

namespace gsystem { // gsystem

class GAPI GEncoding
{
public:
	static GEncoding &Instance();

	// ��ȡUTF-8����ʵ�ʵ��ַ��������ܶ���ַ���Ԫ��ʾһ���ַ���
	static gsize GetLengthOfUtf8String(gcstring8 utf8);
	static gsize GetLengthOfUtf8String(gcstring8 utf8, gsize size);
	static gsize GetLengthOfGbkString(gcstring8 gbk);
	static gsize GetLengthOfGbkString(gcstring8 gbk, gsize size);

	/// �鿴һ��UTF-8�ַ�ռ�˶����ֽ�
	/// utf8��ʾһ��UTF-8�ַ����׵�ַ
	/// ����ֵ����Ϊ0��1��2��3��4������0����Ƿ���1��2��3��4����ռ�ݵ��ֽ�����
	static guint8 GetUnitSizeOfUtf8Character(const gchar8 *utf8);

	static gsize GetUnitSizeOfUtf8CharacterFromUnicode();

	// ��һ��UTF-8�ַ�תΪ��Ӧ��Unicode����
	static guint32 Utf8CharacterToUnicode(const gchar8 *utf8);

	// ��һ��Unicode����ת��Ϊ��Ӧ��UTF-8�ַ��������ַ�ռ�ݵ�Ԫ�ص�λ�ĸ���
	static guint8 UnicodeToUtf8Character(guint32 unicode, gchar8 *utf8);

	// ��һ��Unicode����ת��Ϊ��Ӧ��UTF-16�ַ��������ַ�ռ�ݵ�Ԫ�ص�λ�ĸ���
	static guint8 UnicodeToUtf16Character(guint32 unicode, gchar16 *utf16);

	// ��һ��Unicode����ת��Ϊ��Ӧ��UTF-32�ַ��������ַ�ռ�ݵ�Ԫ�ص�λ�ĸ���
	static guint8 UnicodeToUtf32Character(guint32 unicode, gchar32 *utf32);

public:
	// ��һ������Ϊsize��GBK�ַ���ת��Ϊ��ʾ��ͬ���ݵ�UTF-8�ַ���������UTF-8�ַ����ĳ���
	gsize GbkStringToUtf8String(gcstring8 gbk, gsize size, gstring8 utf8);
	gsize GbkStringToUtf16String(gcstring8 gbk, gsize size, gstring16 utf16);
	gsize GbkStringToUtf32String(gcstring8 gbk, gsize size, gstring32 utf32);

	// ��һ������Ϊsize��UTF-8�ַ���ת��Ϊ��ʾ��ͬ���ݵ�GBK�ַ���������GBK�ַ����ĳ���
	gsize Utf8StringToGbkString(gcstring8 utf8, gsize size, gstring8 gbk);
	gsize Utf8StringToUtf16String(gcstring8 utf8, gsize size, gstring16 utf16);
	gsize Utf8StringToUtf32String(gcstring8 utf8, gsize size, gstring32 utf32);

	gsize Utf16StringToGbkString(gcstring16 utf16, gsize size, gstring8 gbk);

private:
	GEncoding();
	~GEncoding();
	GEncoding(const GEncoding &) = delete;
	GEncoding &operator=(const GEncoding &) = delete;

	gvoid Initialize();
	gvoid Release();

	gbool HasGBK(guint32 unicode) const;

	// Unicode��GBK�Ķ�Ӧ���������֣�
	guint16 *unicode_gbk_basic;

	// Unicode��GBK�Ķ�Ӧ�����ţ�
	GUnorderMap<guint16, guint16> unicode_gbk_symbol;

	// GBK��Unicode�Ķ�Ӧ��
	GUnorderMap<guint16, guint16> gbk_unicode;

private:
	static GEncoding *m_pEncoding;
};

} // namespace gsystem

#endif // _CORE_ENCODING_H_