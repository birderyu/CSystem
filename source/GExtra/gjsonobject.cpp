#include "gjsonobject.h"
#include "gstring.h"
#include "gliststack.h"
#include "gjsonpair.h"
#include "gjsonparsermessage.h"
#include <ctype.h>

namespace gsystem { // gsystem
namespace json { // gsystem.json

GJsonObject::GJsonObject()
{

}

GJsonObject::GJsonObject(const GString &jsonStr)
{
	if (!Parse(jsonStr))
	{
		Destroy();
	}
}

GJsonObject::GJsonObject(const GJsonObject &jsonObj)
{

}

GJsonObject::~GJsonObject()
{
	Destroy();
}

gbool GJsonObject::Valid() const
{
	return !m_tJsonPairs.IsEmpty();
}

GString GJsonObject::ToString() const
{
	if (!Valid())
	{
		return GString();
	}

	GString jsonStr = "{";
	gsize size = m_tJsonPairs.Size();
	gsize pos = 0;
	for (GMap<GString, GJsonPair*>::ConstIterator citer = m_tJsonPairs.ConstBegin();
		citer != m_tJsonPairs.ConstEnd(); citer++)
	{
		if (!citer.Value())
		{
			return GString();
		}
		else
		{
			jsonStr += citer.Value()->ToString();
		}
		
		if (pos < size - 1)
		{
			jsonStr += ",";
		}
		pos++;
	}
	jsonStr += "}";
	return jsonStr;
}

gbool GJsonObject::Parse(const GString &jsonStr, gsize *cursor, GJsonParserMessage *msg)
{
	Destroy(); // ���������ݣ���������
	GString parse_msg; // ��������˴��󣬷��ؿ��ܵ�ԭ��
	gsize _cursor = 0;
	if (cursor)
	{
		_cursor = *cursor;
	}

	// �ַ�ջ
	// �����ַ�������ջ��'{'��','
	// �������������ַ����ҷ��Ϲ���ʱ��������ջ
	// ������'}'�ҷ��Ϲ���ʱ��'{'��ջ
	// ��һ��JsonPair�����������Ҹ�JsonPair���ǵ�һ��ʱ��','��ջ
	GListStack<gchar> char_stack;

	// ѭ������
	while (true)
	{
		gchar c = jsonStr.GetAt(_cursor); // ��ȡһ���ַ�

		if (c == '\0')
		{
			// �����ַ���������������ѭ������ʱ�������ж��Ƿ��Ѿ������ɹ�
			parse_msg = "�ַ�����ǰ����";
			break;
		}
		else if (!G_CHAR_IS_ASCII(c))
		{
			// �����Ƿ����ַ�������ʧ�ܣ�ֱ���˳�
			if (cursor)
			{
				*cursor = _cursor;
			}
			if (msg)
			{
				msg->SetIsSuccess(false);
				msg->SetErrorCursor(_cursor);
				msg->SetErrorMessage("�Ƿ����ַ�");
			}
			Destroy();
			return false;
		}
		else if (G_CHAR_IS_SPACE(c))
		{
			// �հ��ַ��������κβ���
		}
		else if (c == '{')
		{
			// ����'{'��˵��Ӧ�ÿ�ʼ����JsonObject
			if (!char_stack.IsEmpty())
			{
				// '{'֮ǰ��ջ���Ѿ������ݣ�����ʧ�ܣ�ֱ���˳�
				if (cursor)
				{
					*cursor = _cursor;
				}
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(_cursor);
					msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
				}
				Destroy();
				return false;
			}

			//����'{'��ջ
			char_stack.Push(c); // '{'��ջ
		}
		else if (c == '}')
		{
			// ����'}'����������������ѭ������ʱ�������ж��Ƿ��Ѿ������ɹ�
			char_stack.Pop(); // '{'��ջ
			parse_msg = "�Ƿ��Ĺ����ַ�";
			break;
		}
		else if (c == ',')
		{
			// ������','��˵���Ѿ�������������һ��JsonPair
			if (m_tJsonPairs.IsEmpty())
			{
				// δ����JsonPair��������','������ʧ�ܣ�ֱ���˳�
				if (cursor)
				{
					*cursor = _cursor;
				}
				if (msg)
				{
					msg->SetIsSuccess(false);
					msg->SetErrorCursor(_cursor);
					msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
				}
				Destroy();
				return false;
			}

			//����','��ջ
			char_stack.Push(c); // ','��ջ
		}
		else
		{
			// ��������֮����κ��ַ���˵��������һ��JsonPair
			GJsonPair *pair = new GJsonPair();
			if (!pair->Parse(jsonStr, &_cursor, msg))
			{
				// JsonPair����ʧ�ܣ��ͷ��ڴ棬ֱ���˳�
				if (cursor)
				{
					*cursor = _cursor;
				}
				delete pair;
				Destroy();
				return false;
			}

			if (!m_tJsonPairs.IsEmpty())
			{
				gchar _c = '\0';
				char_stack.Pop(&_c); // ','��ջ
				if (_c != ',')
				{
					// ����ʧ�ܣ��ͷ��ڴ棬ֱ���˳�
					if (cursor)
					{
						*cursor = _cursor;
					}
					if (msg)
					{
						msg->SetIsSuccess(false);
						msg->SetErrorCursor(_cursor);
						msg->SetErrorMessage("�Ƿ��Ĺ����ַ�");
					}
					delete pair;
					Destroy();
					return false;
				}
			}

			// �������ɹ���JsonPair����JsonPairs
			m_tJsonPairs.Insert(pair->Key(), pair);
		}

		// ������
		_cursor++;
	} // while

	// �Ƿ�����ɹ�
	gbool success = (char_stack.IsEmpty()) && (!m_tJsonPairs.IsEmpty());
	if (!success)
	{
		// ����ʧ�ܣ������ڴ�
		Destroy();
	}

	if (cursor)
	{
		// ����ǰ���д����Ϣ
		*cursor = _cursor;
	}
	if (msg)
	{
		// ����Ϣд����Ϣ
		msg->SetIsSuccess(success);
		if (!success)
		{
			msg->SetErrorCursor(_cursor);
			if (!parse_msg.IsEmpty())
			{
				msg->SetErrorMessage(parse_msg);
			}
			else
			{
				msg->SetErrorMessage("δ֪��ԭ��");
			}
		}
	}
	return success;
}

gvoid GJsonObject::Destroy()
{
	for (GMap<GString, GJsonPair*>::Iterator iter = m_tJsonPairs.Begin();
		iter != m_tJsonPairs.End(); iter++)
	{
		if (iter.Value())
		{
			delete iter.Value();
		}
	}
	m_tJsonPairs.Clear();
}

} // namespace gsystem.json
} // namespace gsystem
