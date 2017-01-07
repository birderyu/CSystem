#include "gvariant_ex.h"
#include "gstring.h"
#include "gnumber.h"

GVariant_Ex::GVariant_Ex()
: m_nType(VARIANT_TYPE_ILLEGAL)
, m_pVal(NULL)
{

}

GVariant_Ex::GVariant_Ex(gbool bValue)
: m_nType(VARIANT_TYPE_BOOL)
, m_bVal(bValue)
{

}

GVariant_Ex::GVariant_Ex(gchar cValue)
: m_nType(VARIANT_TYPE_CHAR)
, m_cVal(cValue)
{

}

GVariant_Ex::GVariant_Ex(gschar cValue)
: m_nType(VARIANT_TYPE_SCHAR)
, m_scVal(cValue)
{

}

GVariant_Ex::GVariant_Ex(guchar cValue)
: m_nType(VARIANT_TYPE_UCHAR)
, m_ucVal(cValue)
{

}

GVariant_Ex::GVariant_Ex(gwchar cValue)
: m_nType(VARIANT_TYPE_WCHAR)
, m_wcVal(cValue)
{

}

GVariant_Ex::GVariant_Ex(gshort nValue)
: m_nType(VARIANT_TYPE_SHORT)
, m_sVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gushort nValue)
: m_nType(VARIANT_TYPE_USHORT)
, m_usVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gint nValue)
: m_nType(VARIANT_TYPE_INT)
, m_iVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(guint nValue)
: m_nType(VARIANT_TYPE_UINT)
, m_uiVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(glong nValue)
: m_nType(VARIANT_TYPE_LONG)
, m_lVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gulong nValue)
: m_nType(VARIANT_TYPE_ULONG)
, m_ulVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(glonglong nValue)
: m_nType(VARIANT_TYPE_LONGLONG)
, m_llVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gulonglong nValue)
: m_nType(VARIANT_TYPE_ULONGLONG)
, m_ullVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gfloat nValue)
: m_nType(VARIANT_TYPE_FLOAT)
, m_fVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gdouble nValue)
: m_nType(VARIANT_TYPE_DOUBLE)
, m_dVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(gdecimal nValue)
: m_nType(VARIANT_TYPE_DECIMAL)
, m_decVal(nValue)
{

}

GVariant_Ex::GVariant_Ex(const GString &sValue)
: m_nType(VARIANT_TYPE_STRING)
, m_pVal(new GString(sValue))
{

}

GVariant_Ex::GVariant_Ex(const GObject &tValue)
: m_nType(VARIANT_TYPE_OBJECT)
, m_pVal(NULL)
{

}

GVariant_Ex::GVariant_Ex(const gpointer pValue)
: m_nType(VARIANT_TYPE_POINTER)
, m_pVal(pValue)
{

}

GVariant_Ex::GVariant_Ex(const GVariant_Ex &tOther)
: m_nType(tOther.m_nType)
{
	switch (m_nType)
	{
	case VARIANT_TYPE_ILLEGAL:
		break;
	case VARIANT_TYPE_BOOL:
		m_bVal = tOther.m_bVal;
		break;
	case VARIANT_TYPE_CHAR:
		m_cVal = tOther.m_cVal;
		break;
	case VARIANT_TYPE_UCHAR:
		m_ucVal = tOther.m_ucVal;
		break;
	case VARIANT_TYPE_WCHAR:
		m_wcVal = tOther.m_wcVal;
		break;
	case VARIANT_TYPE_SHORT:
		m_sVal = tOther.m_sVal;
		break;
	case VARIANT_TYPE_USHORT:
		m_usVal = tOther.m_usVal;
		break;
	case VARIANT_TYPE_INT:
		m_iVal = tOther.m_iVal;
		break;
	case VARIANT_TYPE_UINT:
		m_uiVal = tOther.m_uiVal;
		break;
	case VARIANT_TYPE_LONG:
		m_lVal = tOther.m_lVal;
		break;
	case VARIANT_TYPE_ULONG:
		m_ulVal = tOther.m_ulVal;
		break;
	case VARIANT_TYPE_LONGLONG:
		m_llVal = tOther.m_llVal;
		break;
	case VARIANT_TYPE_ULONGLONG:
		m_ullVal = tOther.m_ullVal;
		break;
	case VARIANT_TYPE_FLOAT:
		m_fVal = tOther.m_fVal;
		break;
	case VARIANT_TYPE_DOUBLE:
		m_dVal = tOther.m_dVal;
		break;
	case VARIANT_TYPE_STRING:
	{
		if (tOther.m_pVal)
		{
			m_pVal = new GString(*(GString*)tOther.m_pVal);
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
	{
		if (tOther.m_pVal)
		{
			//m_pVal = static_cast<GObject*>(tOther.m_pVal)->Clone();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		m_pVal = tOther.m_pVal;
		break;
	default:
		break;
	}
}

GVariant_Ex::~GVariant_Ex()
{
	ClearMemery();
}

G_VARIANT_TYPE GVariant_Ex::GetVariantType() const
{
	return static_cast<G_VARIANT_TYPE>(m_nType);
}

gpointer GVariant_Ex::GetPoiter() const
{
	if (m_nType == VARIANT_TYPE_POINTER)
	{
		return m_pVal;
	}
	return NULL;
}

gvoid GVariant_Ex::SetPoiter(const gpointer pValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_POINTER;
	m_pVal = pValue;
}

gvoid GVariant_Ex::SetValue(gbool bValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_BOOL;
	m_bVal = bValue;
}

gvoid GVariant_Ex::SetValue(gchar cValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_CHAR;
	m_cVal = cValue;
}

gvoid GVariant_Ex::SetValue(guchar cValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_USHORT;
	m_ucVal = cValue;
}

gvoid GVariant_Ex::SetValue(gwchar cValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_WCHAR;
	m_wcVal = cValue;
}

gvoid GVariant_Ex::SetValue(gshort nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_SHORT;
	m_sVal = nValue;
}

gvoid GVariant_Ex::SetValue(gushort nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_USHORT;
	m_usVal = nValue;
}

gvoid GVariant_Ex::SetValue(gint nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_INT;
	m_iVal = nValue;
}

gvoid GVariant_Ex::SetValue(guint nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_UINT;
	m_uiVal = nValue;
}

gvoid GVariant_Ex::SetValue(glong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_LONG;
	m_lVal = nValue;
}

gvoid GVariant_Ex::SetValue(gulong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_ULONG;
	m_ulVal = nValue;
}

gvoid GVariant_Ex::SetValue(glonglong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_LONGLONG;
	m_llVal = nValue;
}

gvoid GVariant_Ex::SetValue(gulonglong nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_ULONGLONG;
	m_ullVal = nValue;
}

gvoid GVariant_Ex::SetValue(gfloat nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_FLOAT;
	m_fVal = nValue;
}

gvoid GVariant_Ex::SetValue(gdouble nValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_DOUBLE;
	m_dVal = nValue;
}

gvoid GVariant_Ex::SetValue(const GString &sValue)
{
	if (m_nType == VARIANT_TYPE_STRING && m_pVal)
	{
		GString &sStr = *(GString*)m_pVal;
		sStr = sValue;
	}
	else
	{
		m_nType = VARIANT_TYPE_STRING;
		m_pVal = new GString(sValue);
	}
}

gvoid GVariant_Ex::SetValue(const GObject &tValue)
{
	ClearMemery();
	m_nType = VARIANT_TYPE_OBJECT;
	//m_pVal = tValue.Clone();
}

gbool GVariant_Ex::ToBool(const gbool bDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_BOOL:
		return m_bVal;
	case VARIANT_TYPE_CHAR:
		return m_cVal != 0;
	case VARIANT_TYPE_UCHAR:
		return m_ucVal != 0;
	case VARIANT_TYPE_WCHAR:
		return m_wcVal != 0;
	case VARIANT_TYPE_SHORT:
		return m_sVal != 0;
	case VARIANT_TYPE_USHORT:
		return m_usVal != 0;
	case VARIANT_TYPE_INT:
		return m_iVal != 0;
	case VARIANT_TYPE_UINT:
		return m_uiVal != 0;
	case VARIANT_TYPE_LONG:
		return m_lVal != 0;
	case VARIANT_TYPE_ULONG:
		return m_ulVal != 0;
	case VARIANT_TYPE_LONGLONG:
		return m_llVal != 0;
	case VARIANT_TYPE_ULONGLONG:
		return m_ullVal != 0;
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			GString sStr = static_cast<GString*>(m_pVal)->ToUpper();
			if (sStr == "TRUE")
			{
				return true;
			}
			else if (sStr == "FALSE")
			{
				return false;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gbool, GBoolean>(CLASS_CODE_BOOLEAN, bDefValue);
		break;
	default:
		break;
	}
	return bDefValue;
}

gchar GVariant_Ex::ToChar(const gchar cDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_CHAR:
		return m_cVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_UCHAR:
		return static_cast<gchar>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gchar>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gchar>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gchar>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gchar>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gchar>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gchar>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gchar>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gchar>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gchar>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gchar>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gchar>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			GString *pStr = static_cast<GString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return pStr->CString()[0];
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gchar, GChar>(CLASS_CODE_CHARACTER, cDefValue);
	default:
		break;
	}
	return cDefValue;
}

guchar GVariant_Ex::ToUChar(const guchar cDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<guchar>(m_cVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<guchar>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<guchar>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<guchar>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<guchar>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<guchar>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<guchar>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<guchar>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<guchar>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<guchar>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<guchar>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<guchar>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			GString *pStr = static_cast<GString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return static_cast<guchar>(pStr->CString()[0]);
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<guchar, GUChar>(CLASS_CODE_UNSIGNED_CHARACTER, cDefValue);
		break;
	default:
		break;
	}
	return cDefValue;
}

gwchar GVariant_Ex::ToWChar(const gwchar cDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_WCHAR:
		return m_wcVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return m_cVal;
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
	case VARIANT_TYPE_SHORT:
		return static_cast<gwchar>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gwchar>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gwchar>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gwchar>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gwchar>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gwchar>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gwchar>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gwchar>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gwchar>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gwchar>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			GString *pStr = static_cast<GString*>(m_pVal);
			if (!pStr->IsEmpty())
			{
				return static_cast<gwchar>(pStr->CString()[0]);
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gwchar, GWChar>(CLASS_CODE_WIND_CHARACTER, cDefValue);
		break;
	default:
		break;
	}
	return cDefValue;
}

gsmall GVariant_Ex::ToSmall(const gsmall nDefValue) const
{
	// TODO
	return 0;
}

gusmall GVariant_Ex::ToUSmall(const gusmall nDefValue) const
{
	// TODO
	return 0;
}

gshort GVariant_Ex::ToShort(const gshort nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_SHORT:
		return m_sVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gshort>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gshort>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gshort>(m_wcVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gshort>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gshort>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gshort>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gshort>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gshort>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gshort>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gshort>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gshort>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gshort>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gshort nValue = static_cast<GString*>(m_pVal)->ToShort(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gshort, GShort>(CLASS_CODE_SHORT_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

gushort GVariant_Ex::ToUShort(const gushort nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_USHORT:
		return m_usVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gushort>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gushort>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gushort>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gushort>(m_sVal);
	case VARIANT_TYPE_INT:
		return static_cast<gushort>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gushort>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gushort>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gushort>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gushort>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gushort>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gushort>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gushort>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gushort nValue = static_cast<GString*>(m_pVal)->ToUShort(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gushort, GUShort>(CLASS_CODE_UNSIGNED_SHORT_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

gint GVariant_Ex::ToInt(const gint nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_INT:
		return m_iVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gint>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gint>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gint>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gint>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gint>(m_usVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gint>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gint>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gint>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gint>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gint>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gint>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gint>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gint nValue = static_cast<GString*>(m_pVal)->ToInt(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gint, GInteger>(CLASS_CODE_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

guint GVariant_Ex::ToUInt(const guint nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_UINT:
		return m_uiVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<guint>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<guint>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<guint>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<guint>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<guint>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<guint>(m_iVal);
	case VARIANT_TYPE_LONG:
		return static_cast<guint>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<guint>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<guint>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<guint>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<guint>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<guint>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			guint nValue = static_cast<GString*>(m_pVal)->ToUInt(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<guint, GUInteger>(CLASS_CODE_UNSIGNED_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

glong GVariant_Ex::ToLong(const glong nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_LONG:
		return m_lVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<glong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<glong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<glong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<glong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<glong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<glong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<glong>(m_uiVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<glong>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<glong>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<glong>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<glong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<glong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			glong nValue = static_cast<GString*>(m_pVal)->ToLong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<glong, GLong>(CLASS_CODE_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

gulong GVariant_Ex::ToULong(const gulong nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_ULONG:
		return m_ulVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gulong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gulong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gulong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gulong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gulong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gulong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gulong>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gulong>(m_lVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gulong>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gulong>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gulong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gulong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gulong nValue = static_cast<GString*>(m_pVal)->ToULong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gulong, GULong>(CLASS_CODE_UNSIGNED_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

glonglong GVariant_Ex::ToLongLong(const glonglong nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_LONGLONG:
		return m_llVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<glonglong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<glonglong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<glonglong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<glonglong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<glonglong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<glonglong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<glonglong>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<glonglong>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<glonglong>(m_ulVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<glonglong>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<glonglong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gulong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			glonglong nValue = static_cast<GString*>(m_pVal)->ToLongLong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<glonglong, GLongLong>(CLASS_CODE_LONG_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

gulonglong GVariant_Ex::ToULongLong(const gulonglong nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_ULONGLONG:
		return m_ullVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gulonglong>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gulonglong>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gulonglong>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gulonglong>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gulonglong>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gulonglong>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gulonglong>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gulonglong>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gulonglong>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gulonglong>(m_llVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gulonglong>(m_fVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gulonglong>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gulonglong nValue = static_cast<GString*>(m_pVal)->ToULongLong(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gulonglong, GULongLong>(CLASS_CODE_UNSIGNED_LONG_LONG_INTEGER, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

gfloat GVariant_Ex::ToFloat(const gfloat nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_FLOAT:
		return m_fVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gfloat>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gfloat>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gfloat>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gfloat>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gfloat>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gfloat>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gfloat>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gfloat>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gfloat>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gfloat>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gfloat>(m_ullVal);
	case VARIANT_TYPE_DOUBLE:
		return static_cast<gfloat>(m_dVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gfloat nValue = static_cast<GString*>(m_pVal)->ToFloat(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gfloat, GFloat>(CLASS_CODE_SINGLE_FLOAT, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

gdouble GVariant_Ex::ToDouble(const gdouble nDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_DOUBLE:
		return m_dVal;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return 1;
		else return 0;
		break;
	case VARIANT_TYPE_CHAR:
		return static_cast<gdouble>(m_cVal);
	case VARIANT_TYPE_UCHAR:
		return static_cast<gdouble>(m_ucVal);
	case VARIANT_TYPE_WCHAR:
		return static_cast<gdouble>(m_wcVal);
	case VARIANT_TYPE_SHORT:
		return static_cast<gdouble>(m_sVal);
	case VARIANT_TYPE_USHORT:
		return static_cast<gdouble>(m_usVal);
	case VARIANT_TYPE_INT:
		return static_cast<gdouble>(m_iVal);
	case VARIANT_TYPE_UINT:
		return static_cast<gdouble>(m_uiVal);
	case VARIANT_TYPE_LONG:
		return static_cast<gdouble>(m_lVal);
	case VARIANT_TYPE_ULONG:
		return static_cast<gdouble>(m_ulVal);
	case VARIANT_TYPE_LONGLONG:
		return static_cast<gdouble>(m_llVal);
	case VARIANT_TYPE_ULONGLONG:
		return static_cast<gdouble>(m_ullVal);
	case VARIANT_TYPE_FLOAT:
		return static_cast<gdouble>(m_fVal);
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			gbool bIsOK = false;
			gdouble nValue = static_cast<GString*>(m_pVal)->ToDouble(&bIsOK);
			if (bIsOK)
			{
				return nValue;
			}
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
		return ToNumber<gdouble, GDoubleFloat>(CLASS_CODE_DOUBLE_FLOAT, nDefValue);
		break;
	default:
		break;
	}
	return nDefValue;
}

GString GVariant_Ex::ToString(const GString &sDefValue) const
{
	switch (m_nType)
	{
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			return *(GString*)m_pVal;
		}
	}
		break;
	case VARIANT_TYPE_BOOL:
		if (m_bVal) return "true";
		else return "false";
		break;
	case VARIANT_TYPE_CHAR:
		return m_cVal;
		break;
	case VARIANT_TYPE_UCHAR:
		return m_ucVal;
		break;
	case VARIANT_TYPE_WCHAR:
		return m_wcVal;
		break;
	case VARIANT_TYPE_SHORT:
		return GString::FromNum(m_sVal);
		break;
	case VARIANT_TYPE_USHORT:
		return GString::FromNum(m_usVal);
		break;
	case VARIANT_TYPE_INT:
		return GString::FromNum(m_iVal);
		break;
	case VARIANT_TYPE_UINT:
		return GString::FromNum(m_uiVal);
		break;
	case VARIANT_TYPE_LONG:
		return GString::FromNum(m_lVal);
		break;
	case VARIANT_TYPE_ULONG:
		return GString::FromNum(m_ulVal);
		break;
	case VARIANT_TYPE_LONGLONG:
		return GString::FromNum(m_llVal);
		break;
	case VARIANT_TYPE_ULONGLONG:
		return GString::FromNum(m_ullVal);
		break;
	case VARIANT_TYPE_FLOAT:
		return GString::FromNum(m_fVal);
		break;
	case VARIANT_TYPE_DOUBLE:
		return GString::FromNum(m_dVal);
		break;
	case VARIANT_TYPE_OBJECT:
	{
		if (m_pVal)
		{
			GObject *pObjcet = static_cast<GObject*>(m_pVal);
			return pObjcet->ToString();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		break;
	default:
		break;
	}
	return sDefValue;
}

GObject *GVariant_Ex::ToObject() const
{
	/*
	switch (m_emType)
	{
	case VARIANT_TYPE_OBJECT:
	{
		if (m_pVal)
		{
			//return static_cast<GObject*>(m_pVal)->Boxing();
		}
	}
		break;
	case VARIANT_TYPE_BOOL:
		return new GBoolean(m_bVal);
		break;
	case VARIANT_TYPE_CHAR:
		return new GCharacter(m_cVal);
		break;
	case VARIANT_TYPE_UCHAR:
		return new GUCharacter(m_ucVal);
		break;
	case VARIANT_TYPE_WCHAR:
		return new GWCharacter(m_wcVal);
		break;
	case VARIANT_TYPE_SHORT:
		return new GShort(m_sVal);
		break;
	case VARIANT_TYPE_USHORT:
		return new GUShort(m_usVal);
		break;
	case VARIANT_TYPE_INT:
		return new GInteger(m_iVal);
		break;
	case VARIANT_TYPE_UINT:
		return new GUInteger(m_uiVal);
		break;
	case VARIANT_TYPE_LONG:
		return new GLong(m_lVal);
		break;
	case VARIANT_TYPE_ULONG:
		return new GULong(m_ulVal);
		break;
	case VARIANT_TYPE_LONGLONG:
		return new GLongLong(m_llVal);
		break;
	case VARIANT_TYPE_ULONGLONG:
		return new GULongLong(m_ullVal);
		break;
	case VARIANT_TYPE_FLOAT:
		return new GFloat(m_fVal);
		break;
	case VARIANT_TYPE_DOUBLE:
		return new GDouble(m_dVal);
		break;
	case VARIANT_TYPE_STRING:
	{
		if (m_pVal)
		{
			return static_cast<GString*>(m_pVal)->Boxing();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		break;
	default:
		break;
	}
	*/
	return NULL;
}

gbool GVariant_Ex::IsValid() const
{
	if (m_nType == VARIANT_TYPE_ILLEGAL)
	{
		return false;
	}
	else if (m_nType == VARIANT_TYPE_STRING
		|| m_nType == VARIANT_TYPE_OBJECT
		|| m_nType == VARIANT_TYPE_POINTER)
	{
		return m_pVal != NULL;
	}
	return true;
}

GVariant_Ex &GVariant_Ex::operator = (const GVariant_Ex &var)
{
	m_nType = var.m_nType;
	switch (m_nType)
	{
	case VARIANT_TYPE_ILLEGAL:
		break;
	case VARIANT_TYPE_BOOL:
		m_bVal = var.m_bVal;
		break;
	case VARIANT_TYPE_CHAR:
		m_cVal = var.m_cVal;
		break;
	case VARIANT_TYPE_UCHAR:
		m_ucVal = var.m_ucVal;
		break;
	case VARIANT_TYPE_WCHAR:
		m_wcVal = var.m_wcVal;
		break;
	case VARIANT_TYPE_SHORT:
		m_sVal = var.m_sVal;
		break;
	case VARIANT_TYPE_USHORT:
		m_usVal = var.m_usVal;
		break;
	case VARIANT_TYPE_INT:
		m_iVal = var.m_iVal;
		break;
	case VARIANT_TYPE_UINT:
		m_uiVal = var.m_uiVal;
		break;
	case VARIANT_TYPE_LONG:
		m_lVal = var.m_lVal;
		break;
	case VARIANT_TYPE_ULONG:
		m_ulVal = var.m_ulVal;
		break;
	case VARIANT_TYPE_LONGLONG:
		m_llVal = var.m_llVal;
		break;
	case VARIANT_TYPE_ULONGLONG:
		m_ullVal = var.m_ullVal;
		break;
	case VARIANT_TYPE_FLOAT:
		m_fVal = var.m_fVal;
		break;
	case VARIANT_TYPE_DOUBLE:
		m_dVal = var.m_dVal;
		break;
	case VARIANT_TYPE_STRING:
	{
		if (var.m_pVal)
		{
			m_pVal = new GString(*(GString*)var.m_pVal);
		}
	}
		break;
	case VARIANT_TYPE_OBJECT:
	{
		if (var.m_pVal)
		{
			//m_pVal = static_cast<GObject*>(var.m_pVal)->Clone();
		}
	}
		break;
	case VARIANT_TYPE_POINTER:
		m_pVal = var.m_pVal;
		break;
	default:
		break;
	}
	return *this;
}

void GVariant_Ex::ClearMemery()
{
	if (!m_pVal)
	{
		return;
	}
	if (m_nType == VARIANT_TYPE_STRING)
	{
		GString *pString = static_cast<GString*>(m_pVal);
		delete pString;
	}
	else if (m_nType == VARIANT_TYPE_OBJECT)
	{
		GObject *pObject = static_cast<GObject*>(m_pVal);
		delete pObject;
	}
	m_pVal = NULL;
}