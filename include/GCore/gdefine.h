/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gdefine.h
** @brief	ȫ�ֺ궨��
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
** ȫ�ֺ궨����һЩȫ�ֵĺ곣���������ݲ�ͬ����ϵͳ�Ͳ�ͬ������������Ӧ�ĵ�����
**
****************************************************************************/

#ifndef _CORE_DEFINE_H_
#define _CORE_DEFINE_H_

/****************************************************************************
**
** gdefine.h
** ����ϵͳ
** G_SYSTEM_WINDOWS: Windows
** G_COMPILER_LINUX: Linux
**
****************************************************************************/
#if defined (_WIN32) || defined(_WIN64)
# define G_SYSTEM_WINDOWS
#endif // _WIN32 or _WIN64

#ifdef _LINUX
# define G_SYSTEM_LINUX
#endif // _LINUX

/****************************************************************************
**
** gdefine.h
** ������
** G_COMPILER_MSVC: MSVC++
** G_COMPILER_GCC: GCC
**
****************************************************************************/
#ifdef _MSC_VER
# define G_COMPILER_MSVC
#endif // _MSC_VER

#ifdef __GNUC__
# define G_COMPILER_GCC
#endif // __GNUC__

#ifdef G_SYSTEM_WINDOWS
#	ifdef _WIN64
#		define G_64_BIT
#	else
#		define G_32_BIT
#	endif // _WIN64
#endif // G_SYSTEM_WINDOWS

// ����API
#ifdef _DLL
	#define GDLL
#endif // _DLL

#ifdef G_COMPILER_MSVC
#	ifdef GDLL
#		define GAPI __declspec(dllexport)
#	else // !GDLL 
#		define GAPI __declspec(dllimport)
#	endif // GDLL
#else
#	define GAPI
#endif // G_COMPILER_MSVC

#define GOFFSET(type, member) ((gsize)&(((type *)0)->member))
typedef struct dummy
{
	void *p;
	unsigned char slot;
}dummy_t;
#define G_X86_64 (GOFFSET(dummy_t, slot) == 8) //��64λϵͳ�£�ָ��Ѱַ8���ֽڴ�С�ĵ�ַ�ռ�
#define G_X86_32 (GOFFSET(dummy_t, slot) == 4) //��32λϵͳ�£�ָ��Ѱַ4���ֽڴ�С�ĵ�ַ�ռ�

#ifndef NULL
#	define NULL	0
#endif // !NULL

//#if __cplusplus >= 201103L
#	define G_CPP_11
//#endif

#ifndef G_CPP_11
#	define nullptr NULL
#	define override
#	define constexpr
#	define final
#endif // for C++11

#define G_BEGIN_NAMESPACE namespace GNova {
#define G_END_NAMESPACE }

#ifdef __cplusplus
#	define G_DECLARE_NOTHROW  throw()
#endif

#ifdef _DEBUG
#	define GDEBUG
#endif

#ifdef GDEBUG
#	include <assert.h>  
#	define GASSERT(e) assert(e)
#else // !GDEBUG
#	define GASSERT(e) do { } while ((false) && (e))
#endif // GDEBUG

#if defined (i386) || defined (__i386__) || defined (_M_IX86) || \
	defined (vax) || defined (__alpha) || defined (__LITTLE_ENDIAN__) || \
	defined (ARM) || defined (_M_IA64) || defined (_M_AMD64) || \
	defined (__amd64) || \
	((defined (__ia64__) || defined (__ia64)) && !defined (__hpux))
#	define G_LITTLE_ENDIAN 0x0123
#	define G_BYTE_ORDER G_LITTLE_ENDIAN
#else
#	define G_BIG_ENDIAN 0x3210
#	define G_BYTE_ORDER G_BIG_ENDIAN
#endif

#define G_POINTER_ADDRESS_SIZE	4

#define G_INT8_MAX		0x7f
#define G_INT8_MIN		(-0x80)
#define G_UINT8_MAX		0xff

#define G_INT16_MAX		0x7fff
#define G_INT16_MIN		(-0x8000)
#define G_UINT16_MAX	0xffff

#define G_INT32_MAX		0x7fffffff
#define G_INT32_MIN		(-0x7fffffff - 1)
#define G_UINT32_MAX	0xffffffffU

#define G_INT32L_MAX	0x7fffffffL
#define G_INT32L_MIN	(-0x7fffffffL - 1)
#define G_UINT32L_MAX	0xffffffffUL

#define G_INT64_MAX		0x7fffffffffffffffLL
#define G_INT64_MIN		(-0x7fffffffffffffffLL - 1)
#define G_UINT64_MAX	0xffffffffffffffffULL

#define G_LIST_MAX_SIZE (G_UINT32_MAX - 1)
#define G_LIST_NULL_POS G_UINT32_MAX

#ifdef __cplusplus__
extern "C"{
#endif

#ifdef __cplusplus__
}
#endif

// 
#ifndef GINTERFACE
#	define GINTERFACE	struct
#endif // !GINTERFACE

#ifndef GINLINE
#	define GINLINE	inline
#endif // !GINLINE

// �ַ�����
#define GUCHAR(c)				((guchar)(c))
#define G_CHAR_IS_ASCII(c)		(isascii(GUCHAR(c)) != 0)
#define G_CHAR_IS_ALNUM(c)		(isalnum(GUCHAR(c)) != 0)
#define G_CHAR_IS_ALPHA(c)		(isalpha(GUCHAR(c)) != 0)
#define G_CHAR_IS_BLANK(c)		(isblank(GUCHAR(c)) != 0)
#define G_CHAR_IS_CNTRL(c)		(iscntrl(GUCHAR(c)) != 0)
#define G_CHAR_IS_DIGIT(c)		(isdigit(GUCHAR(c)) != 0)
#define G_CHAR_IS_DIGIT_X(c)	(isxdigit(GUCHAR(c)) != 0)
#define G_CHAR_IS_GRAPH(c)		(isgraph(GUCHAR(c)) != 0)
#define G_CHAR_IS_LOWER(c)		(islower(GUCHAR(c)) != 0)
#define G_CHAR_IS_PRINT(c)		(isprint(GUCHAR(c)) != 0)
#define G_CHAR_IS_PUNCT(c)		(ispunct(GUCHAR(c)) != 0)
#define G_CHAR_IS_SPACE(c)		(isspace(GUCHAR(c)) != 0)
#define G_CHAR_IS_UPPER(c)		(isupper(GUCHAR(c)) != 0)
#define G_CHAR_TO_LOWER(c)		tolower(GUCHAR(c))
#define G_CHAR_TO_UPPER(c)		toupper(GUCHAR(c))

// ���ú���
#define G_CALL_AT_EXIT atexit
#define G_MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define G_MIN(a,b)  (((a) < (b)) ? (a) : (b))

#endif // _CORE_DEFINE_H_
