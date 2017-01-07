#ifndef _CORE_C_STRING_HELPER_H_
#define _CORE_C_STRING_HELPER_H_

#include "CsGlobal.h"

#define CS_USE_MSVC_STRCMP

#ifdef _MSC_VER
#	ifdef CS_USE_MSVC_STRCMP
#	define strcasecmp	_stricmp
#	define strncasecmp	_strnicmp 
#	else 
CS_API cs_int strcasecmp(const cs_char *s1, cs_char *s2);
CS_API cs_int strncasecmp(const cs_char *s1, cs_char *s2, /*register*/ cs_int n);
#	endif
#endif

// δ���пղ���
class CS_API CsCStringHelper
{
public:
	// ������'\0'�ĳ���
	static cs_size_t Size(const cs_char *c_str);

	// size = strlen(src) + 1��ĩβ��'\0'��
	static cs_bool Copy(const cs_char *src, cs_size_t size, cs_char *dest);

	static cs_bool Trim(const cs_char *c_str, cs_size_t size,
		cs_char *c_str_out, cs_size_t &len_out);
	static cs_bool TrimLeft(const cs_char *c_str, cs_size_t size,
		cs_char *c_str_out, cs_size_t &len_out);
	static cs_bool TrimRight(const cs_char *c_str, cs_size_t size,
		cs_char *c_str_out, cs_size_t &len_out);

	static cs_bool MakeTrim(cs_char *c_str, cs_size_t size, cs_size_t &len_out);
	static cs_bool MakeTrimLeft(cs_char *c_str, cs_size_t size, cs_size_t &len_out);
	static cs_bool MakeTrimRight(cs_char *c_str, cs_size_t size, cs_size_t &len_out);

	static cs_bool MakeUpper(cs_char *c_str, cs_size_t size);
	static cs_bool MakeLower(cs_char *c_str, cs_size_t size);

	// ע�⣺������ֵΪfalseʱ����ʾδ���κ��滻����ʱc_str_out��out_len���ֵ��������Ч��
	static cs_bool Replace(const cs_char *c_str, cs_size_t size,
		const cs_char *from, cs_size_t from_size,
		const cs_char *to, cs_size_t to_size,
		cs_bool bIsSensitive,
		cs_char *c_str_out, cs_size_t &out_size);
};

#endif // _CORE_C_STRING_HELPER_H_