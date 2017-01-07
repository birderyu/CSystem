#ifndef _CORE_FILTER_EX_H_
#define _CORE_FILTER_EX_H_

#include "gdynamicarray.h"
#include "gvariant.h"

class CsFilter_Ex
{
protected:
	// ��������
	enum CS_UNION_TYPE
	{
		UNION_TYPE_ERROR = -1,
		UNION_TYPE_SINGLE = 0,	// �����Ϲ�ϵ��ֻ��һ��������
		UNION_TYPE_AND,			// �߼���
		UNION_TYPE_OR,			// �߼���
	};

	/// �Ƚ�����
	enum CS_COMPARE_TYPE
	{
		COMPARE_TYPE_ERROR = -1,		// �Ƿ��ıȽ�����
		COMPARE_TYPE_EQUAL,			// ����
		COMPARE_TYPE_LESS,			// С��
		COMPARE_TYPE_LESS_EQUAL,	// С�ڵ���
		COMPARE_TYPE_GREATER,		// ����
		COMPARE_TYPE_GREATER_EQUAL,	// ���ڵ���
		COMPARE_TYPE_NOTEQUAL,		// ������
		COMPARE_TYPE_LIKE,			// ģ���Ƚ�
	};

private:
	class CsFilterCell
	{
	public:
		CsFilterCell();
		CsFilterCell(const CsFilterCell &tCell);
		virtual ~CsFilterCell();
		gbool SetFilter(const GString &sFilter);
		gbool IsValid() const;
		gbool Release();
		GString ToString() const;
		CsFilterCell &operator=(const CsFilterCell &tCell);

	private:		
		GString m_sFieldName;
		GVariant m_tFieldValue;
		CS_COMPARE_TYPE m_emCompareType;
	};

	struct CsFilterData
	{
		CsFilterData();
		CsFilterData(const CsFilterData &tData);
		gbool SetFilter(const GString &sFilter);
		gbool IsValid() const;
		GString ToString() const;
		gbool Release();
		CsFilterData &operator=(const CsFilterData &tData);

	private:
		GDynamicArray<CsFilterData> m_tChildren;
		CsFilterCell m_tCell;
		CS_UNION_TYPE m_emUnionType;
	};

	struct CsFilterParse
	{
		// �����������ַ���
		static gbool ParseFilter(const GString &sFilter, CS_UNION_TYPE &emUnionType, 
			GDynamicArray<CsFilterData> &tData, CsFilterCell &tCell);

		// �����������ַ�����Ԥ�����ַ�������"OID = 1; NAME = 'ABC'"����Ϊ"OID = 1 AND NAME = ABC"
		static gbool ParseFilter_PreParseFilter(GString &sFilter);
		// �����������ַ������������ϵķ��ţ���ȡ���ϵ�ö��ֵ
		static gbool ParseFilter_ParseUnionType(const GString &sUnion, CS_UNION_TYPE &emUnionType);
		// �����������ַ������ж������Ƿ�Ϸ�
		static gbool ParseFilter_IsBracketLegal(const GString &sFilter);
		// �����������ַ������Ƴ���ʼ��Ч�����ţ���"(OID = 1 AND TYPE = 2)"����Ϊ"OID = 1 AND TYPE = 2"
		static gbool ParseFilter_TrimBracket(GString &sFilter);
		// �����������ַ�����ָ�����Ϸ���ȥ�ֽ�����
		// ֻ�ֽ��һ������
		// ��"(OID = 1 OR TYPE = 2) AND (NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		// ��Ϊ"(OID = 1 OR TYPE = 2)" �� "(NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		static gbool ParseFilter_BreakUpBracketOnOneLevel(const GString &sFilter, const GString &sUnion, GStringList &tFilterList);
		// 
		static gbool ParseFilter_ParseCompareType(const GString &sCompare, CS_COMPARE_TYPE &emCompareType);
		static gbool GetCompareString(CS_COMPARE_TYPE emCompareType, GString &sCompare);
		static gbool GetUnionString(CS_UNION_TYPE emUnionType, GString &sUnion);
	};

public:
	CsFilter_Ex(const GString &sFilter);
	CsFilter_Ex(const CsFilter_Ex &tFilter);
	virtual ~CsFilter_Ex();
	virtual gbool SetFilter(const GString &sFilter);
	virtual CsFilter_Ex &operator=(const CsFilter_Ex &tFilter);

	gbool IsValid() const;
	GString ToString() const;

private:
	gbool Initialize();
	gbool Release();
	CsFilterData m_tFilterData;

private:
	static GStringList m_tUnionSymbols;
	static gbool m_bInitializeUnionSymbols;

	static GStringList m_tCompareSymbols;
	static gbool m_bInitializeCompareSymbols;
};

#endif // _CORE_FILTER_EX_H_