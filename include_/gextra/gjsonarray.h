/****************************************************************************
**
** GSystem: A quick, micro library of C++
**
** @file gjsonarray.h
** @brief Json����
** @author birderyu
** @contact https://github.com/birderyu
** @date 2017-1-3
** @version 0.5.0
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

namespace gsystem { // gsystem
	namespace json { // gsystem.json
		class GJsonValue;
		class GJsonParserMessage;
	} // namespace gsystem.json
} // namespace gsystem

namespace gsystem { // gsystem
namespace json { // gsystem.json

class GAPI GJsonArray
	: public GObject
{
	friend class GJsonObject;

public:
	GJsonArray();
	~GJsonArray();

	gbool Valid() const;

	GString ToString() const;

	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gbool Parse(const GString &jsonStr, gsize *cursor);
	gvoid Destroy();
	GList<GJsonValue*> m_tJsonValues;
};

} // namespace gsystem.json
} // namespace gsystem

#endif // _CORE_JSON_ARRAY_H_