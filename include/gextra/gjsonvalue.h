/****************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file	gjsonvalue.h
** @brief	Json值类型的定义
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2017-1-3
** @version	1.0
**
** Json值可以是:
** 数字：Number，包括整型（Integer）和浮点型（Float）
** 布尔型：Boolean
** 字符串：String
** 数组：Array
** 对象：Object
** Null
**
****************************************************************************/

#ifndef _CORE_JSON_VALUE_H_
#define _CORE_JSON_VALUE_H_

#include "gvariety.h"
#include "gobject.h"

namespace gsystem { // gsystem
	namespace json { // gsystem.json
		class GJsonObject;
		class GJsonArray;
		class GJsonParserMessage;
	} // namespace gsystem.json
} // namespace gsystem

namespace gsystem { // gsystem
namespace json { // gsystem.json

class GAPI GJsonValue
	: public GObject
{
public:
	enum JSON_VALUE_TYPE
	{
		JSON_VALUE_TYPE_ILLEGAL = 0,
		JSON_VALUE_TYPE_NULL,
		JSON_VALUE_TYPE_BOOLEAN,
		JSON_VALUE_TYPE_NUMBER,
		JSON_VALUE_TYPE_STRING,
		JSON_VALUE_TYPE_ARRAY,
		JSON_VALUE_TYPE_OBJECT,
	};

public:
	GJsonValue();
	~GJsonValue();

	gbool Valid();
	GString ToString() const;

	//JSON_VALUE_TYPE Type() const;
	gbool Parse(const GString &jsonStr, gsize *cursor = GNULL, GJsonParserMessage *msg = GNULL);

private:
	gbool Parse_Number(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg);
	gbool Parse_Boolean(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg);
	gbool Parse_String(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg);
	gbool Parse_Array(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg);
	gbool Parse_Object(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg);
	gbool Parse_Null(const GString &jsonStr, gsize &cursor, GJsonParserMessage *msg);

	gvoid Destroy();
	GVariety m_tValue;
	gbyte m_nType;
};

} // namespace gsystem.json
} // namespace gsystem

#endif // _CORE_JSON_VALUE_H_