/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonArray.h
** @brief	Json�������͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonArray
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

#include "CsJsonObject.h"
#include "CsList.h"
#include "CsVariant.h"

typedef CsList<CsVariant> CsVariantList;

class CS_API CsJsonArray
	: public CsJsonObject
{
public:
	CsJsonArray();
	CsJsonArray(const CsString &);
	CsJsonArray(const CsVariantList &);
	CsJsonArray(const CsJsonArray &);

private:
	CsString m_sKey;
	CsVariantList m_tValue;
};

#endif // _CORE_JSON_ARRAY_H_