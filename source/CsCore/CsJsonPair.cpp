#include "CsJsonPair.h"
#include "CsJsonValue.h"
#include "CsListStack.h"

CsJsonPair::CsJsonPair()
: m_pValue(NULL)
{

}

CsJsonPair::~CsJsonPair()
{
	if (m_pValue)
	{
		delete m_pValue;
	}
}

cs_bool CsJsonPair::Valid() const
{
	return m_pValue != NULL;
}

CsString & CsJsonPair::Key()
{
	return m_sKey;
}

const CsString & CsJsonPair::Key() const
{
	return m_sKey;
}

CsJsonValue * CsJsonPair::Value()
{
	return m_pValue;
}

const CsJsonValue * CsJsonPair::Value() const
{
	return m_pValue;
}

cs_bool CsJsonPair::Parse(const CsString &jsonStr, cs_size_t cursor, CsString *s_error)
{
	CsListStack<cs_char> stack;
	cs_bool has_key = false;

	cs_size_t key_start = CsString::NULL_POS;
	cs_size_t value_start = CsString::NULL_POS;

	CsString parse_msg;

	do
	{
		cs_char c = jsonStr.GetAt(cursor++);
		if (c == '\0')
		{
			// �����ַ���������������ѭ��
			parse_msg = "�ַ�����ǰ������";
			break;
		}

		if (CS_CHAR_IS_SPACE(c))
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
				if (key_start == CsString::NULL_POS)
				{
					break;
				}
				else
				{
					cs_size_t key_size = cursor - key_start;
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
				if (value_start == CsString::NULL_POS)
				{
					value_start = cursor - 1;
				}

				if (CS_CHAR_IS_DIGIT(c))
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
			if (key_start == CsString::NULL_POS)
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
