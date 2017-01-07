#include "gjsonpair.h"
#include "gjsonvalue.h"
#include "gliststack.h"

GJsonPair::GJsonPair()
: m_pValue(NULL)
{

}

GJsonPair::~GJsonPair()
{
	if (m_pValue)
	{
		delete m_pValue;
	}
}

gbool GJsonPair::Valid() const
{
	return m_pValue != NULL;
}

GString & GJsonPair::Key()
{
	return m_sKey;
}

const GString & GJsonPair::Key() const
{
	return m_sKey;
}

GJsonValue * GJsonPair::Value()
{
	return m_pValue;
}

const GJsonValue * GJsonPair::Value() const
{
	return m_pValue;
}

gbool GJsonPair::Parse(const GString &jsonStr, gsize cursor, GString *s_error)
{
	GListStack<gchar> stack;
	gbool has_key = false;

	gsize key_start = GString::NULL_POS;
	gsize value_start = GString::NULL_POS;

	GString parse_msg;

	do
	{
		gchar c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// �����ַ���������������ѭ��
			parse_msg = "�ַ�����ǰ������";
			break;
		}

		if (G_CHAR_IS_SPACE(c))
		{
			// ����ǿհ��ַ�����ֱ������
			continue;
		}

		// ���򣬽����ַ���
		if (!has_key)
		{
			// ��û�н�������
			if (c == '\"')
			{

			}

			if (c == ':')
			{
				// ������ð�ţ�˵�������Ѿ���������
				if (key_start == GString::NULL_POS)
				{
					break;
				}
				else
				{
					gsize key_size = cursor - key_start;
					if (key_size == 0)
					{
						parse_msg = "Json����Ϊ�ա�";
					}
					break;

					m_sKey = jsonStr.SubString(key_start, cursor - key_start).Trim();
					has_key = true;
				}
			}
			else
			{
				if (value_start == GString::NULL_POS)
				{
					value_start = cursor - 1;
				}

				if (G_CHAR_IS_DIGIT(c))
				{
					// �п�����Json���֣�Ҳ�п����Ǵ����Json�ַ���
				}
				else if (c == 't' || c == 'f')
				{
					// �п�����Json�����ͣ�Ҳ�п����Ǵ����Json�ַ���
				}
				else if (c == '\"')
				{
					// �п�����Json�ַ�����Ҳ�п����Ǵ����Json�ַ���
				}
				else if (c == '[')
				{
					// �п�����Json���飬Ҳ�п����Ǵ����Json�ַ���
				}
				else if (c == '{')
				{
					// �п�����Json����Ҳ�п����Ǵ����Json�ַ���
				}
				else
				{
					// �п�����JsonNull��Ҳ�п����Ǵ����Json�ַ���
				}
			}
		}
		else
		{
			// �Ѿ�������������
			if (key_start == GString::NULL_POS)
			{
				key_start = cursor - 1;
			}
		}
	} while (true);

	if (!m_pValue)
	{
		if (s_error)
		{
			*s_error = "Json����ʧ�ܣ�" + parse_msg;
		}
		return false;
	}
	return true;
}
