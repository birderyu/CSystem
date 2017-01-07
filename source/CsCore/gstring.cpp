#include "gstring.h"
#include "gstringlist.h"
#include "gcstringhelper.h"

GString::GString()
{
	m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	m_tStringStore.m_sSmallStr.Initialize();
}

GString::GString(gchar cChar)
{
	m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
	m_tStringStore.m_sSmallStr.Initialize(cChar);
}

GString::GString(const gchar *pStr)
{
	gsize size = GCStringHelper::Size(pStr);
	if (size <= 0)
	{
		m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize();
	}
	else if (size <= GSmallStringStore::MAX_SIZE)
	{
		// С�ַ���
		m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize(pStr, size);
	}
	else if (size <= GNormalStringStore::MAX_SIZE)
	{
		// ��ͨ�ַ���
		m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
		m_tStringStore.m_sNormalStr.Initialize(pStr, size);
	}
	else
	{
		// ���ַ���
		m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_BIG;
		// TODO
	}
}

GString::GString(const GString &sStr)
{
	m_tStringStore.m_nType = sStr.m_tStringStore.m_nType;
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		m_tStringStore.m_sSmallStr.Initialize(sStr.m_tStringStore.m_sSmallStr);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		m_tStringStore.m_sNormalStr.Initialize(sStr.m_tStringStore.m_sNormalStr);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
		m_tStringStore.m_sSmallStr.Initialize();
		break;
	}
}

GString::~GString()
{
	Free();
}

GString GString::FromStdString(const std::string &sStr)
{
	return GString(sStr.c_str());
}

gbool GString::IsEmpty() const
{
	return Size() == 0;
}

GString GString::Trim() const
{
	GString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeTrim();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeTrim();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	return sStr;
}

GString GString::TrimLeft() const
{
	GString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeTrimLeft();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeTrimLeft();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	return sStr;
}

GString GString::TrimRight() const
{
	GString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeTrimRight();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeTrimRight();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}

	return sStr;
}

GString GString::ToUpper() const
{
	GString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeUpper();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeUpper();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}

	return sStr;
}

GString GString::ToLower() const
{
	GString sStr(*this);
	if (sStr.IsEmpty())
	{
		return sStr;
	}

	switch (sStr.m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		sStr.m_tStringStore.m_sSmallStr.MakeLower();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		sStr.m_tStringStore.m_sNormalStr.MakeLower();
		return sStr;
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}

	return sStr;
}

gcstring GString::CString() const
{
	if (IsEmpty())
	{
		return "";
	}
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.CString();
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.CString();
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	return "";
}

gsize GString::Size() const
{
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.Size();
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.Size();
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	return 0;
}

gbool GString::Resize(gsize size)
{
	if (size == 0)
	{
		Free();
	}

	// ת��Ϊֵ����
	ToValue();

	// size��������κβ���
	if (size == Size())
	{
		return true;
	}

	// �ж�Resize֮�������
	GStringStore::TYPE emType = GetTypeBySize(size);
	if (emType == GStringStore::STRING_STORE_TYPE_VALUE_SMALL)
	{
		// Resize֮��Ӧ��ΪС�ַ���
		if (!Switch(emType))
		{
			return false;
		}
		m_tStringStore.m_sSmallStr.m_nSize = size;
		m_tStringStore.m_sSmallStr.m_cStr[size] = '\0';
		return true;
	}
	else if (emType == GStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
	{
		// Resize֮��Ӧ��Ϊ��ͨ�ַ���
		if (m_tStringStore.m_nType == GStringStore::STRING_STORE_TYPE_VALUE_SMALL)
		{
			// ԭ����С�ַ���
			GString str_copy(*this);
			m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
			if (!m_tStringStore.m_sNormalStr.Initialize(size))
			{
				// �����ڴ�
				return false;
			}
			if (!m_tStringStore.m_sNormalStr.CopyString(str_copy.CString(), str_copy.Size()))
			{
				// ����ԭ���ַ���
				return false;
			}
			// �ı�Size
			m_tStringStore.m_sNormalStr.m_pStr[size] = '\0';
			m_tStringStore.m_sNormalStr.m_nSize = static_cast<guint16>(size);
			return true;
		}
		else if (m_tStringStore.m_nType == GStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
		{
			// ԭ������ͨ�ַ���
			return m_tStringStore.m_sNormalStr.Resize(size);
		}
		else
		{
			// ԭ���Ǵ��ַ���
			// TODO
		}
	}
	else
	{
		// CsStringStore::STRING_STORE_TYPE_VALUE_BIG
		// Resize֮��Ӧ��Ϊ���ַ���
		// TODO
	}
	return false;
}

gchar GString::GetAt(gsize pos) const
{
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.GetAt(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.GetAt(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
}

gchar &GString::GetAt(gsize pos)
{
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.GetAt(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.GetAt(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
}

const gchar *GString::Cursor(gsize pos) const
{
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.Cursor(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.Cursor(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	return NULL;
}

gchar *GString::Cursor(gsize pos)
{
	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
		return m_tStringStore.m_sSmallStr.Cursor(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
		return m_tStringStore.m_sNormalStr.Cursor(pos);
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
		// TODO
		break;
	case GStringStore::STRING_STORE_TYPE_REFERENCE:
		// TODO
		break;
	default:
		break;
	}
	return NULL;
}

GString &GString::Replace(const GString &from, const GString &to, gbool bIsSensitive)
{
	gsize size = Size();
	gsize from_size = from.Size();
	if (size <= 0 || from_size <= 0)
	{
		return *this;
	}

	gcstring cfrom = from.CString();
	gcstring cto = to.CString();
	gsize to_size = to.Size();

	if (!cfrom ||
		(!cto && to_size >= 0))
	{
		return *this;
	}

	// ת��Ϊֵ����
	ToValue();

	// Ԥ��һ���滻����ĳ��ȣ����Ȱ��������ܴ�ȥ����
	gsize estimate_size = size;
	if (from_size < to_size)
	{
		// �п��ܻᱻ����
		estimate_size = size * to_size / from_size + 1;
	}
	GStringStore::TYPE nEstimateType = GetTypeBySize(estimate_size);

	if (nEstimateType == GStringStore::STRING_STORE_TYPE_VALUE_SMALL)
	{
		// �滻֮��ΪС�ַ���
		gchar cStr[CS_SMALL_STRING_MAX_SIZE];
		gsize out_len = 0;
		if (!GCStringHelper::Replace(CString(), size, cfrom, from_size, cto, to_size, bIsSensitive,
			cStr, out_len))
		{
			return *this;
		}
		Free();
		m_tStringStore.m_nType = nEstimateType;
		m_tStringStore.m_sSmallStr.Initialize(cStr, out_len);
		return *this;
	}
	else if (nEstimateType == GStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
	{
		// �滻֮��Ϊ��ͨ�ַ���
		gchar *pStr = (gchar*)GMalloc((estimate_size + 1) * sizeof(gchar));
		gsize out_len = 0;
		if (!GCStringHelper::Replace(CString(), size, cfrom, from_size, cto, to_size, bIsSensitive,
			pStr, out_len))
		{
			GFree(pStr);
			return *this;
		}
		Free();
		m_tStringStore.m_nType = nEstimateType;
		m_tStringStore.m_sNormalStr.m_pStr = pStr;
		m_tStringStore.m_sNormalStr.m_nSize = out_len;
		return *this;
	}
	else
	{
		// CsStringStore::STRING_STORE_TYPE_VALUE_BIG
		// �滻֮��Ϊ���ַ���
		// TODO
	}
	return *this;
}

GStringList GString::Split(const GString &sSep, gbool bIgnoreEmpty, gbool bIsSensitive) const
{
	// TODO
	GStringList t;
	return t;
}

gsize GString::Find(gchar c, gsize start, gbool bIsSensitive) const
{
	// TODO
	return NULL_POS;
}

gsize GString::Find(const GString &str, gsize start, gbool bIsSensitive) const
{
	// TODO
	return NULL_POS;
}

GString GString::SubString(gsize start, gsize length) const
{
	return GString();
}

gbool GString::Equals(const GString &str, gbool bIsSensitive) const
{
	if (bIsSensitive)
	{
		return *this == str;
	}
	return false;
}

gbool GString::Switch(GStringStore::TYPE emType)
{
	if (m_tStringStore.m_nType == emType)
	{
		return true;
	}

	switch (m_tStringStore.m_nType)
	{
	case GStringStore::STRING_STORE_TYPE_VALUE_SMALL:
	{
		if (emType == GStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
		{
			GString str_copy(*this);
			Free();
			m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_NORMAL;
			str_copy.m_tStringStore.m_sSmallStr.SwitchToNormal(m_tStringStore.m_sNormalStr);
			return true;
		}
		else if (emType == GStringStore::STRING_STORE_TYPE_VALUE_BIG)
		{
			// TODO
		}
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_NORMAL:
	{
		if (emType == GStringStore::STRING_STORE_TYPE_VALUE_SMALL)
		{
			// TODO
			if (m_tStringStore.m_sNormalStr.CanSwithToSmall())
			{
				GString str_copy(*this);
				Free();
				m_tStringStore.m_nType = GStringStore::STRING_STORE_TYPE_VALUE_SMALL;
				str_copy.m_tStringStore.m_sNormalStr.SwitchToSmall(m_tStringStore.m_sSmallStr);
				return true;
			}			
		}
		else if (emType == GStringStore::STRING_STORE_TYPE_VALUE_BIG)
		{
			// TODO
		}
	}
		break;
	case GStringStore::STRING_STORE_TYPE_VALUE_BIG:
	{
		if (emType == GStringStore::STRING_STORE_TYPE_VALUE_SMALL)
		{
			// TODO
		}
		else if (emType == GStringStore::STRING_STORE_TYPE_VALUE_NORMAL)
		{
			// TODO
		}
	}
		break;
	default:
		break;
	}

	return false;
}

gbool GString::StartWith(gchar c) const
{
	return GetAt(0) == c;
}

gbool GString::EndWith(gchar c) const
{
	return GetAt(Size() - 1) == c;
}
