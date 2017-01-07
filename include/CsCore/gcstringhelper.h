#ifndef _CORE_C_STRING_HELPER_H_
#define _CORE_C_STRING_HELPER_H_

#include "gglobal.h"

#define G_USE_MSVC_STRCMP

#ifdef G_COMPILER_MSVC
#	ifdef G_USE_MSVC_STRCMP
#	define strcasecmp	_stricmp
#	define strncasecmp	_strnicmp 
#	else // !G_USE_MSVC_STRCMP
GAPI gint strcasecmp(const gchar *s1, gchar *s2);
GAPI gint strncasecmp(const gchar *s1, gchar *s2, /*register*/ gint n);
#	endif // G_USE_MSVC_STRCMP
#endif // G_COMPILER_MSVC

// δ���пղ���
class GAPI GCStringHelper
{
public:
	// ������'\0'�ĳ���
	static gsize Size(const gchar *c_str);

	// size = strlen(src) + 1��ĩβ��'\0'��
	static gbool Copy(const gchar *src, gsize size, gchar *dest);

	static gbool Trim(const gchar *c_str, gsize size,
		gchar *c_str_out, gsize &len_out);
	static gbool TrimLeft(const gchar *c_str, gsize size,
		gchar *c_str_out, gsize &len_out);
	static gbool TrimRight(const gchar *c_str, gsize size,
		gchar *c_str_out, gsize &len_out);

	static gbool MakeTrim(gchar *c_str, gsize size, gsize &len_out);
	static gbool MakeTrimLeft(gchar *c_str, gsize size, gsize &len_out);
	static gbool MakeTrimRight(gchar *c_str, gsize size, gsize &len_out);

	static gbool MakeUpper(gchar *c_str, gsize size);
	static gbool MakeLower(gchar *c_str, gsize size);

	// ע�⣺������ֵΪfalseʱ����ʾδ���κ��滻����ʱc_str_out��out_len���ֵ��������Ч��
	static gbool Replace(const gchar *c_str, gsize size,
		const gchar *from, gsize from_size,
		const gchar *to, gsize to_size,
		gbool bIsSensitive,
		gchar *c_str_out, gsize &out_size);
};

#endif // _CORE_C_STRING_HELPER_H_