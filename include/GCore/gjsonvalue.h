/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gjsonvalue.h
** @brief	Jsonֵ���͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonValue
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

#include "gobject.h"
#include "gvariant.h"

class GJsonArray;
class GJsonArray;

class GAPI GJsonValue
	: public GObject
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
	//GJsonValue();
	//~GJsonValue();

	//JSON_VALUE_TYPE Type() const;
	gbool Parse(const GString &jsonStr, gsize cursor = 0, GString *s_error = NULL);

private:
	GVariant m_tValue;
	gbyte m_nType;
};

#endif // _CORE_JSON_VALUE_H_