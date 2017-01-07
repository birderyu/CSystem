#include "gssonobject.h"
#include "gstring.h"
#include "gliststack.h"
#include "gjsonpair.h"

GJsonObject::GJsonObject()
: m_bValid(true)
{

}

GJsonObject::GJsonObject(const GString &jsonStr)
: m_bValid(true)
{
	Parse(jsonStr);
}

GJsonObject::GJsonObject(const GJsonObject &jsonObj)
{

}

GJsonObject::~GJsonObject()
{

}

gbool GJsonObject::Parse(const GString &jsonStr, gsize cursor, GString *s_error)
{
	GListStack<gchar> char_stack;
	GString parse_msg;

	do 
	{
		gchar c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// �����ַ���������������ѭ��
			break;
		}

		if (G_CHAR_IS_SPACE(c))
		{
			// ����ǿհ��ַ�����ֱ������
			continue;
		}

		// ���򣬽����ַ���
		if (c == '{')
		{
			char_stack.Push(c);
		}
		else if (c == '}')
		{
			char_stack.Pop();
			if (char_stack.IsEmpty())
			{
				// 
				break;
			}
		}
		else
		{
			// �����˵�һ���ǿա��ǿհס��Ǵ����ŵ��ַ���˵�������˵�һ��JsonPair
			GJsonPair *pair = new GJsonPair();
			if (!pair->Parse(jsonStr, cursor))
			{
				delete pair;
				break;
			}
			m_tJsonPairs.Insert(pair->Key(), pair);
		}
	} while (true);

	return !char_stack.IsEmpty();
}
