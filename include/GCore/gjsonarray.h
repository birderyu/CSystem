/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	gssonarray.h
** @brief	Json�������͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonArray
**
** Json�����ڷ���������д��
** ����ɰ����������
** {
**	"employees":[
**		{ "firstName":"John", "lastName" : "Doe" },
** 		{ "firstName":"Anna", "lastName" : "Smith" },
** 		{ "firstName":"Peter", "lastName" : "Jones" }
**	]
** }
** ������������У����� "employees" �ǰ���������������飬ÿ������
** ����һ������ĳ�ˣ����պ������ļ�¼��
**
****************************************************************************/

#ifndef _CORE_JSON_ARRAY_H_
#define _CORE_JSON_ARRAY_H_

#include "glist.h"

class GJsonValue;

class GAPI GJsonArray
{
public:
	GJsonArray();
	GJsonArray(const GString &);
	GJsonArray(const GJsonArray &);

	gbool Parse(const GString &jsonStr, gsize cursor = 0, GString *s_error = NULL);

private:
	GList<GJsonValue*> m_tList;
};

#endif // _CORE_JSON_ARRAY_H_