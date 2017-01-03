#ifndef _CORE_JSON_VALUE_H_
#define _CORE_JSON_VALUE_H_

#include "CsJsonObject.h"
#include "CsVariant.h"

// JSON ֵ������:
// ���ͣ�Integer
// �����ͣ�Float
// �ַ�����String
// �����ͣ�Boolean
// ���飺Array
// ����Object
// Null

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