// ����ͼ
// ����ͼ����һ��ʵ�ʴ��ڵı�����������ĳһ�ű�Ĳ�������

#ifndef _CORE_TABLE_VIEW_H_
#define _CORE_TABLE_VIEW_H_

#include "gtableglobal.h"

class GDataTable;
class GVirtualTable;

class GAPI GDataView
	: GTableActionT<GDataView>
{
public:
	GDataView(GDataTable &, CsSizeTypeArray *rows, CsSizeTypeArray *columns);

private:
	GVirtualTable *m_pVirtualTable;
	CsSizeTypeArray *m_pRows;
	CsSizeTypeArray *m_pColumns;
};

#endif // _CORE_TABLE_VIEW_H_