/****************************************************************************
**
** CNova: A quick, micro library of C++
**
** @file	CsJsonObject.h
** @brief	Json�������͵Ķ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		CsJsonObject
**
** Json�����ڻ���������д��
** ������԰���������� / ֵ�ԣ�
** { "firstName": "John", "lastName": "Doe" }
**
****************************************************************************/

#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "CsObject.h"
#include "CsString.h"
#include "CsMap.h"

class CsJsonPair;

class CS_API CsJsonObject
	: public CsNewT<CsJsonObject>
	, public CsObject
{
public:
	CsJsonObject();
	CsJsonObject(const CsString &jsonStr);
	CsJsonObject(const CsJsonObject &jsonObj);
	~CsJsonObject();

	cs_bool Valid() const;

	// �ַ���������cursorΪ�α�
	cs_bool Parse(const CsString &jsonStr, cs_size_t cursor = 0, CsString *s_error = NULL);

private:
	CsMap<CsString, CsJsonPair*> m_tJsonPairs;
	cs_bool m_bValid;
};

#endif // _CORE_JSON_OBJECT_H_