#include "CsJsonObject.h"
#include "CsString.h"
#include "CsListStack.h"
#include "CsJsonPair.h"

CsJsonObject::CsJsonObject()
: m_bValid(true)
{

}

CsJsonObject::CsJsonObject(const CsString &jsonStr)
: m_bValid(true)
{
	Parse(jsonStr);
}

CsJsonObject::CsJsonObject(const CsJsonObject &jsonObj)
{

}

CsJsonObject::~CsJsonObject()
{

}

cs_bool CsJsonObject::Parse(const CsString &jsonStr, cs_size_t cursor, CsString *s_error)
{
	CsListStack<cs_char> char_stack;
	CsString parse_msg;

	do 
	{
		cs_char c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// �����ַ���������������ѭ��
			break;
		}

		if (CS_CHAR_IS_SPACE(c))
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
			CsJsonPair *pair = new CsJsonPair();
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
