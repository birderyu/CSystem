#ifndef _CORE_C_STRING_HELPER_H_
#define _CORE_C_STRING_HELPER_H_

#include "gtype.h"

#define G_USE_MSVC_STRCMP

#ifdef G_COMPILER_MSVC
#	ifdef G_USE_MSVC_STRCMP
#	define strcasecmp	_stricmp
#	define strncasecmp	_strnicmp 
#	else // !G_USE_MSVC_STRCMP
GAPI gsystem::gint strcasecmp(const gsystem::gchar *s1, gsystem::gchar *s2);
GAPI gsystem::gint strncasecmp(const gsystem::gchar *s1, gsystem::gchar *s2, /*register*/ gsystem::gint n);
#	endif // G_USE_MSVC_STRCMP
#endif // G_COMPILER_MSVC

namespace gsystem { // gsystem

// δ���пղ���
class GAPI GCString
{
public:
	// ������'\0'�ĳ���
	static gsize Size(gcstring str);
	static gsize Size(gcstring16 str);
	static gsize Size(gcstring32 str);

	// size = strlen(src) + 1��ĩβ��'\0'��
	static gvoid Copy(gcstring src, gsize size, gstring dest);

	static gvoid Trim(const gchar *c_str, gsize size,
		gchar *c_str_out, gsize &len_out);
	static gvoid TrimLeft(const gchar *c_str, gsize size,
		gchar *c_str_out, gsize &len_out);
	static gvoid TrimRight(const gchar *c_str, gsize size,
		gchar *c_str_out, gsize &len_out);

	static gvoid MakeTrim(gchar *c_str, gsize size, gsize &len_out);
	static gvoid MakeTrimLeft(gchar *c_str, gsize size, gsize &len_out);
	static gvoid MakeTrimRight(gchar *c_str, gsize size, gsize &len_out);

	static gvoid MakeUpper(gchar *c_str, gsize size);
	static gvoid MakeLower(gchar *c_str, gsize size);

	// ע�⣺������ֵΪfalseʱ����ʾδ���κ��滻����ʱc_str_out��out_len���ֵ��������Ч��
	static gbool Replace(const gchar *c_str, gsize size,
		const gchar *from, gsize from_size,
		const gchar *to, gsize to_size,
		gbool bIsSensitive,
		gchar *c_str_out, gsize &out_size);
};

} // namespace gsystem

#endif // _CORE_C_STRING_HELPER_H_