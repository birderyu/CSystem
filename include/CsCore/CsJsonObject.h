#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "CsObject.h"
#include "CsStructure.h"

// һ��Json����
class CS_API CsJsonObject
	: public CsPreviousNextNodeT<CsJsonObject>
	, public CsChildNodeT<CsJsonObject>
	, public CsNewT<CsJsonObject>
	, public CsObject
{
public:
	enum TYPE
	{
		JSON_OBJECT,	// ����
		JSON_VALUE,		// ��ֵ��
		JSON_ARRAY,		// ����
	};

public:
	CsJsonObject();
	CsJsonObject(const CsJsonObject &);

	virtual ~CsJsonObject();

	virtual TYPE Type();
};

#endif // _CORE_JSON_OBJECT_H_