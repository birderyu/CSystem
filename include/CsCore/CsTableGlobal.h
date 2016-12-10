#ifndef _CORE_TABLE_GLOBAL_H_
#define _CORE_TABLE_GLOBAL_H_

#include "CsObject.h"
#include "CsVariant.h"

class CsIntArray;

class CsDataTable;
class CsDataView;
template<typename TableT> class CsTableCell;
template<typename TableT> class CsTableField;
template<typename TableT> class CsTableFields;
template<typename TableT> class CsTableRow;
template<typename TableT> class CsTableRows;
template<typename TableT> class CsTableColumn;
template<typename TableT> class CsTableColumns;

// ������
enum CS_TABLE_TYPE
{
	TABLE_TYPE_SERIAL,		// �����ڴ��Ĭ�ϣ�
	TABLE_TYPE_SIMPLE,		// ���ڴ��
	TABLE_TYPE_VARIANT,		// �������ͱ�
	TABLE_TYPE_OBJECT,		// �����
};

// ���ֶ�����
enum CS_TABLE_FIELD_TYPE
{
	TABLE_FIELD_TYPE_ILLEGAL = -1,
	TABLE_FIELD_TYPE_BOOL,
	TABLE_FIELD_TYPE_CHAR,
	TABLE_FIELD_TYPE_SCHAR,
	TABLE_FIELD_TYPE_UCHAR,
	TABLE_FIELD_TYPE_WCHAR,
	TABLE_FIELD_TYPE_SHORT,
	TABLE_FIELD_TYPE_USHORT,
	TABLE_FIELD_TYPE_INT,
	TABLE_FIELD_TYPE_UINT,
	TABLE_FIELD_TYPE_LONG,
	TABLE_FIELD_TYPE_ULONG,
	TABLE_FIELD_TYPE_LONGLONG,
	TABLE_FIELD_TYPE_ULONGLONG,
	TABLE_FIELD_TYPE_FLOAT,
	TABLE_FIELD_TYPE_DOUBLE,
	TABLE_FIELD_TYPE_DECIMAL,
	TABLE_FIELD_TYPE_STRING,	// �ַ���
	TABLE_FIELD_TYPE_GEOMETRY,	// �����ֶ�
};

// ����������
enum CS_TABLE_INDEX_TYPE
{
	TABLE_INDEX_TYPE_NULL,		// ������
	TABLE_INDEX_TYPE_UNORDER,	// ��������
	TABLE_INDEX_TYPE_ORDER,		// ��������
	TABLE_INDEX_TYPE_SPATIAL,	// �ռ�����
};

#endif // _CORE_TABLE_GLOBAL_H_