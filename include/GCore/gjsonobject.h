/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file	gjsonobject.h
** @brief	Json�������͵Ķ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
** @see		GJsonObject
**
** Json�����ڻ���������д��
** ������԰���������� / ֵ�ԣ�
** { "firstName": "John", "lastName": "Doe" }
**
****************************************************************************/

#ifndef _CORE_JSON_OBJECT_H_
#define _CORE_JSON_OBJECT_H_

#include "gobject.h"
#include "gstring.h"
#include "gmap.h"

namespace gnova {
	namespace json {
		class GJsonPair;
		class GJsonParserMessage;
	}
}

namespace gnova {
namespace json {

class GAPI GJsonObject
	: public GNewT<GJsonObject>
	, public GObject
{
public:
	GJsonObject();
	GJsonObject(const GString &jsonStr);
	GJsonObject(const GJsonObject &jsonObj);
	~GJsonObject();

	gbool test(GJsonPair &p) const;

	gbool Valid() const;
	GString ToString() const;

	// �ַ���������cursorΪ�α�
	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gvoid Dispose();
	GMap<GString, GJsonPair*> m_tJsonPairs;
};

}
}

#endif // _CORE_JSON_OBJECT_H_