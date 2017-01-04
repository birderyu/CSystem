/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonValue.h
** @brief	Jsonֵ���͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonValue
**
** Jsonֵ������:
** ���ͣ�Integer
** �����ͣ�Float
** �ַ�����String
** �����ͣ�Boolean
** ���飺Array
** ����Object
** Null
**
****************************************************************************/

#ifndef _CORE_JSON_VALUE_H_
#define _CORE_JSON_VALUE_H_

#include "CsJsonObject.h"
#include "CsVariant.h"

class CS_API CsJsonValue
	: public CsJsonObject
{
public:
	CsJsonValue();
	CsJsonValue(const CsString &);
	CsJsonValue(const CsJsonValue &);

private:
	CsVariant m_tVariant;
};

#endif // _CORE_JSON_VALUE_H_