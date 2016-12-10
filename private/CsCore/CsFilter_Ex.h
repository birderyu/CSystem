#ifndef _CORE_FILTER_EX_H_
#define _CORE_FILTER_EX_H_

#include "CsDynamicArray.h"
#include "CsVariant.h"

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
		cs_bool SetFilter(const CsString &sFilter);
		cs_bool IsValid() const;
		cs_bool Release();
		CsString ToString() const;
		CsFilterCell &operator=(const CsFilterCell &tCell);

	private:		
		CsString m_sFieldName;
		CsVariant m_tFieldValue;
		CS_COMPARE_TYPE m_emCompareType;
	};

	struct CsFilterData
	{
		CsFilterData();
		CsFilterData(const CsFilterData &tData);
		cs_bool SetFilter(const CsString &sFilter);
		cs_bool IsValid() const;
		CsString ToString() const;
		cs_bool Release();
		CsFilterData &operator=(const CsFilterData &tData);

	private:
		CsDynamicArray<CsFilterData> m_tChildren;
		CsFilterCell m_tCell;
		CS_UNION_TYPE m_emUnionType;
	};

	struct CsFilterParse
	{
		// �����������ַ���
		static cs_bool ParseFilter(const CsString &sFilter, CS_UNION_TYPE &emUnionType, 
			CsDynamicArray<CsFilterData> &tData, CsFilterCell &tCell);

		// �����������ַ�����Ԥ�����ַ�������"OID = 1; NAME = 'ABC'"����Ϊ"OID = 1 AND NAME = ABC"
		static cs_bool ParseFilter_PreParseFilter(CsString &sFilter);
		// �����������ַ������������ϵķ��ţ���ȡ���ϵ�ö��ֵ
		static cs_bool ParseFilter_ParseUnionType(const CsString &sUnion, CS_UNION_TYPE &emUnionType);
		// �����������ַ������ж������Ƿ�Ϸ�
		static cs_bool ParseFilter_IsBracketLegal(const CsString &sFilter);
		// �����������ַ������Ƴ���ʼ��Ч�����ţ���"(OID = 1 AND TYPE = 2)"����Ϊ"OID = 1 AND TYPE = 2"
		static cs_bool ParseFilter_TrimBracket(CsString &sFilter);
		// �����������ַ�����ָ�����Ϸ���ȥ�ֽ�����
		// ֻ�ֽ��һ������
		// ��"(OID = 1 OR TYPE = 2) AND (NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		// ��Ϊ"(OID = 1 OR TYPE = 2)" �� "(NAME = ABC AND (CITY = 'BJ' OR SIZE = 100))"
		static cs_bool ParseFilter_BreakUpBracketOnOneLevel(const CsString &sFilter, const CsString &sUnion, CsStringList &tFilterList);
		// 
		static cs_bool ParseFilter_ParseCompareType(const CsString &sCompare, CS_COMPARE_TYPE &emCompareType);
		static cs_bool GetCompareString(CS_COMPARE_TYPE emCompareType, CsString &sCompare);
		static cs_bool GetUnionString(CS_UNION_TYPE emUnionType, CsString &sUnion);
	};

public:
	CsFilter_Ex(const CsString &sFilter);
	CsFilter_Ex(const CsFilter_Ex &tFilter);
	virtual ~CsFilter_Ex();
	virtual cs_bool SetFilter(const CsString &sFilter);
	virtual CsFilter_Ex &operator=(const CsFilter_Ex &tFilter);

	cs_bool IsValid() const;
	CsString ToString() const;

private:
	cs_bool Initialize();
	cs_bool Release();
	CsFilterData m_tFilterData;

private:
	static CsStringList m_tUnionSymbols;
	static cs_bool m_bInitializeUnionSymbols;

	static CsStringList m_tCompareSymbols;
	static cs_bool m_bInitializeCompareSymbols;
};

#endif // _CORE_FILTER_EX_H_