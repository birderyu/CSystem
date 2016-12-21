// ����ͼ
// ����ͼ����һ��ʵ�ʴ��ڵı�����������ĳһ�ű�Ĳ�������

#ifndef _CORE_TABLE_VIEW_H_
#define _CORE_TABLE_VIEW_H_

#include "CsTableGlobal.h"

class CsDataTable;
class CsVirtualTable;

class CS_API CsDataView
	: CsTableActionT<CsDataView>
{
public:
	CsDataView(CsDataTable &, CsSizeTypeArray *rows, CsSizeTypeArray *columns);

private:
	CsVirtualTable *m_pVirtualTable;
	CsSizeTypeArray *m_pRows;
	CsSizeTypeArray *m_pColumns;
};

#endif // _CORE_TABLE_VIEW_H_