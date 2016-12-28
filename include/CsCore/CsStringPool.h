/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @author	Birderyu
** @contact	https://github.com/birderyu
** @file	CsStringPool.h
** @date	2016-12-03
** @brief	�ַ��������͵Ķ���
**
****************************************************************************/

#ifndef _CORE_STRING_POOL_H_
#define _CORE_STRING_POOL_H_

#include "CsGlobal.h"
#include "CsMemoryStore.h"
#include "CsVector.h"
#include "CsMap.h"

/****************************************************************************
**
** CsStringPool.h
**
** @class	CsStringPool
** @module	CsCore
** @brief	�ַ���������
**
**	Ϊ�˴����ַ����ı䳤���ԣ����ö���������ڴ�ṹȥ�洢�ʹ����ַ�����
** 		���ַ������ڲ������ַ�����Ϊ���¼������ͣ��ֱ�������¼��ִ洢��ʽ��
** 1.STRING_POOL_SMALL_STRING�����ַ���������Ϊ1+1+�ַ�����ʵ�ʳ��ȣ�����'\0'������һ
**   ���������ڴ�洢��������֧�ֵ��ַ�������󳤶�Ϊ255��
** 2.STRING_POOL_NORMAL_STRING����ͨ�ַ���������Ϊ1+2+�ַ�����ʵ�ʳ��ȣ�����'\0'����
**   ��һ���������ڴ�洢��֧�ֵ��ַ�������󳤶�Ϊ65535�ͣ�nMaxSize-3���Ľ�С�ߣ�
** 3.STRING_POOL_PART_STRING_START�������ַ����ģ���λ����λ��
**   ����Ϊ1+4+CS_POINTER_ADDRESS_SIZE+��ǰ�����ַ����ĳ��ȣ�������֧�ֵ��ַ��������
**   ����Ϊ4294967295��
** 4.STRING_POOL_PART_STRING_MIDDLE�������ַ����ģ���λ���м䣬
**   ����Ϊ1+4+CS_POINTER_ADDRESS_SIZE+CS_POINTER_ADDRESS_SIZE+��ǰ�����ַ�����
**   ���ȣ�������֧�ֵ��ַ�������󳤶�Ϊ4294967295��
** 5.STRING_POOL_PART_STRING_END�������ַ����ģ���λ�ڽ�β��
**   ����Ϊ1+4+CS_POINTER_ADDRESS_SIZE+��ǰ�����ַ����ĳ��ȣ�������֧�ֵ��ַ��������
**   ����Ϊ4294967295��
** 6.STRING_POOL_REFERENCE_STRING�������ַ���������Ϊ1+CS_POINTER_ADDRESS_SIZE��
**   �洢��һ���ַ������׵�ַ������ʱ�����´���һ��ȫ�����ĸ�����
**
****************************************************************************/
class CS_API CsStringPool
{
	enum TYPE
	{
		STRING_POOL_SMALL_STRING = 0,
		STRING_POOL_NORMAL_STRING,
		STRING_POOL_PART_STRING_START,
		STRING_POOL_PART_STRING_MIDDLE,
		STRING_POOL_PART_STRING_END,
		STRING_POOL_REFERENCE_STRING,
	};

public:
	CsStringPool(cs_size_t nInitSzie = 2048, cs_size_t nMaxSize = 10240);
	cs_pointer Alloc(cs_size_t);
	cs_void Free(cs_pointer);

private:
	/// ����վ
	CsMap<cs_size_t, CsVector<cs_ptr_addr>> m_tRecycle;
	CsMemoryStore m_tStore;
};

#endif // _CORE_STRING_POOL_H_