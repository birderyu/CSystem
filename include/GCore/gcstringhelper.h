#ifndef _CORE_C_STRING_HELPER_H_
#define _CORE_C_STRING_HELPER_H_

#include "gglobal.h"

#define G_USE_MSVC_STRCMP

#ifdef G_COMPILER_MSVC
#	ifdef G_USE_MSVC_STRCMP
#	define strcasecmp	_stricmp
#	define strncasecmp	_strnicmp 
#	else // !G_USE_MSVC_STRCMP
GAPI gnova::gint strcasecmp(const gnova::gchar *s1, gnova::gchar *s2);
GAPI gnova::gint strncasecmp(const gnova::gchar *s1, gnova::gchar *s2, /*register*/ gnova::gint n);
#	endif // G_USE_MSVC_STRCMP
#endif // G_COMPILER_MSVC

namespace gnova { // gnova

// 未做判空操作
class GAPI GCStringHelper
{
public:
	// 不包含'\0'的长度
	static gsize Size(const gchar *c_str);

	// size = strlen(src) + 1（末尾的'\0'）
	static gvoid Copy(const gchar *src, gsize size, gchar *dest);

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

	// 注意：当返回值为false时，表示未做任何替换，此时c_str_out和out_len里的值可能是无效的
	static gbool Replace(const gchar *c_str, gsize size,
		const gchar *from, gsize from_size,
		const gchar *to, gsize to_size,
		gbool bIsSensitive,
		gchar *c_str_out, gsize &out_size);

	template <typename T>
	static T ToNum(const gchar *c_str, gbool *isok);
};

} // namespace gnova

#endif // _CORE_C_STRING_HELPER_H_