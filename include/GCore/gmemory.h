/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gmemory.h
** @brief	C风格内存操作的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0.0
**
****************************************************************************/

#ifndef _CORE_MEMORY_H_
#define _CORE_MEMORY_H_

#include "gtype.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** @name		GMalloc
** @brief		分配内存
** @param[in]	size {gsize} 分配内存的大小，单位字节
** @return		{gptr} 分配内存的首地址，若分配失败则返回GNULL
** @note		该方法不会抛出异常，而是会在内存分配失败时返回一个空指针
**
****************************************************************************/
GAPI gptr GMalloc(gsize size) GNOEXCEPT;

/****************************************************************************
**
** @name		GCalloc
** @brief		分配内存
** @param[in]	n {gsize} 分配内存的大小，单位个
** @param[in]	size {gsize} 分配内存的大小，单位字节
** @return		{gptr} 分配内存的首地址，大小为n*size个字节，若分配失败则返回GNULL
** @note		该方法不会抛出异常，而是会在内存分配失败时返回一个空指针
**
****************************************************************************/
GAPI gptr GCalloc(gsize n, gsize size) GNOEXCEPT;

/****************************************************************************
**
** @name		GRealloc
** @brief		重新分配内存
** @param[in]	oldptr {gptr} 旧内存首地址
** @param[in]	newsize {gsize} 新内存的大小，单位字节
** @return		{gptr} 新分配内存的首地址，若分配失败则返回GNULL
** @note		该方法不会抛出异常，而是会在内存分配失败时返回一个空指针
**
****************************************************************************/
GAPI gptr GRealloc(gptr oldptr, gsize newsize) GNOEXCEPT;

/****************************************************************************
**
** GNew
**
** @name		GFree
** @brief		释放内存
** @param[in]	pfree {gptr} 内存首地址
**
****************************************************************************/
GAPI gvoid GFree(gptr pfree) GNOEXCEPT;

/****************************************************************************
**
** @name		GMemCopy
** @brief		内存拷贝
** @param[in]	dst {gptr} 内存拷贝的目标
** @param[in]	src {gcptr} 内存拷贝的来源
** @param[in]	size {gsize} 内存拷贝的大小，单位字节
** @return		{gptr} 拷贝过后内存的首地址
**
****************************************************************************/
GAPI gptr GMemCopy(gptr dst, gcptr src, gsize size);

/****************************************************************************
**
** @name		GMemMove
** @brief		内存移动
** @param[in]	dst {gptr} 内存移动后的首地址
** @param[in]	src {gcptr} 内存移动前的首地址
** @param[in]	size {gsize} 内存移动的大小，单位字节
** @return		{gptr} 内存移动后的首地址
**
****************************************************************************/
GAPI gptr GMemMove(gptr dst, gcptr src, gsize size);

/****************************************************************************
**
** @name		GMemSet
** @brief		内存设置
** @param[in]	dst {gptr} 待赋值内存的首地址
** @param[in]	value {gbyte} 值
** @param[in]	size {gsize} 内存设置的大小，单位字节
** @return		{gptr} 内存设置后的首地址
**
****************************************************************************/
GAPI gptr GMemSet(gptr dst, gbyte value, gsize size);

} // namespace gsystem

#endif // _CORE_MEMORY_H_
