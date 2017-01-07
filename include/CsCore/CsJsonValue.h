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
** ���֣�Number���������ͣ�Integer���͸����ͣ�Float��
** �����ͣ�Boolean
** �ַ�����String
** ���飺Array
** ����Object
** Null
**
****************************************************************************/

#ifndef _CORE_JSON_VALUE_H_
#define _CORE_JSON_VALUE_H_

#include "CsObject.h"
#include "CsVariant.h"

class CsJsonArray;
class CsJsonArray;

class CS_API CsJsonValue
	: public CsObject
{
public:
	enum JSON_VALUE_TYPE
	{
		JSON_VALUE_TYPE_NULL,
		JSON_VALUE_TYPE_BOOLEAN,
		JSON_VALUE_TYPE_NUMBER,
		JSON_VALUE_TYPE_STRING,
		JSON_VALUE_TYPE_ARRAY,
		JSON_VALUE_TYPE_OBJECT,
	};

public:
	//CsJsonValue();
	//~CsJsonValue();

	//JSON_VALUE_TYPE Type() const;
	cs_bool Parse(const CsString &jsonStr, cs_size_t cursor = 0, CsString *s_error = NULL);

private:
	CsVariant m_tValue;
	cs_byte m_nType;
};

#endif // _CORE_JSON_VALUE_H_