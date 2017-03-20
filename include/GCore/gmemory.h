/// C�����ڴ����

#ifndef _CORE_MEMORY_H_
#define _CORE_MEMORY_H_

#include "gglobal.h"

namespace gsystem { // gsystem

/****************************************************************************
**
** GNew
**
** @name		GMalloc
** @brief		�����ڴ�
** @param[in]	size {gsize} �����ڴ�Ĵ�С����λ�ֽ�
** @return		{gptr} �����ڴ���׵�ַ��������ʧ���򷵻�NULL
**
****************************************************************************/
GAPI gptr GMalloc(gsize size);

/****************************************************************************
**
** GNew
**
** @name		GCalloc
** @brief		�����ڴ�
** @param[in]	n {gsize} �����ڴ�Ĵ�С����λ��
** @param[in]	size {gsize} �����ڴ�Ĵ�С����λ�ֽ�
** @return		{gptr} �����ڴ���׵�ַ����СΪn*size���ֽڣ�������ʧ���򷵻�NULL
**
****************************************************************************/
GAPI gptr GCalloc(gsize n, gsize size);

/****************************************************************************
**
** GNew
**
** @name		GRealloc
** @brief		���·����ڴ�
** @param[in]	oldptr {gptr} ���ڴ��׵�ַ
** @param[in]	newsize {gsize} ���ڴ�Ĵ�С����λ�ֽ�
** @return		{gptr} �·����ڴ���׵�ַ��������ʧ���򷵻�NULL
**
****************************************************************************/
GAPI gptr GRealloc(gptr oldptr, gsize newsize);

/****************************************************************************
**
** GNew
**
** @name		GFree
** @brief		�ͷ��ڴ�
** @param[in]	pfree {gptr} �ڴ��׵�ַ
**
****************************************************************************/
GAPI gvoid GFree(gptr pfree);

/****************************************************************************
**
** GNew
**
** @name		GMemCopy
** @brief		�ڴ濽��
** @param[in]	dst {gptr} �ڴ濽����Ŀ��
** @param[in]	src {gcptr} �ڴ濽������Դ
** @param[in]	size {gsize} �ڴ濽���Ĵ�С����λ�ֽ�
** @return		{gptr} ���������ڴ���׵�ַ
**
****************************************************************************/
GAPI gptr GMemCopy(gptr dst, gcptr src, gsize size);

/****************************************************************************
**
** GNew
**
** @name		GMemMove
** @brief		�ڴ��ƶ�
** @param[in]	dst {gptr} �ڴ��ƶ�����׵�ַ
** @param[in]	src {gcptr} �ڴ��ƶ�ǰ���׵�ַ
** @param[in]	size {gsize} �ڴ��ƶ��Ĵ�С����λ�ֽ�
** @return		{gptr} �ڴ��ƶ�����׵�ַ
**
****************************************************************************/
GAPI gptr GMemMove(gptr dst, gcptr src, gsize size);

/****************************************************************************
**
** GNew
**
** @name		GMemSet
** @brief		�ڴ�����
** @param[in]	dst {gptr} ����ֵ�ڴ���׵�ַ
** @param[in]	value {gbyte} ֵ
** @param[in]	size {gsize} �ڴ����õĴ�С����λ�ֽ�
** @return		{gptr} �ڴ����ú���׵�ַ
**
****************************************************************************/
GAPI gptr GMemSet(gptr dst, gbyte value, gsize size);

} // namespace gsystem

#endif // _CORE_MEMORY_H_
