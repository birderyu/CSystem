#ifndef _GEOMETRY_GEOMETRY_COLLECTION_H_
#define _GEOMETRY_GEOMETRY_COLLECTION_H_

#include "CsGeometry.h"

class CS_API CsGeometryCollection
	: public CsGeometry
{
public:
	virtual ~CsGeometryCollection() = 0;

	/****************************************************************************
	**
	** CsGeometryCollection
	**
	** @name	Size
	** @brief	��ȡ��ǰ���ζ��������
	** @return	{cs_size_t} ����
	**
	****************************************************************************/
	virtual cs_size_t Size() const = 0;

	virtual CsGeometryP GetAt(cs_size_t pos) = 0;
	virtual const CsGeometryP GetAt(cs_size_t pos) const = 0;
	virtual cs_void SetAt(cs_size_t pos, const CsGeometryP &geo) = 0;
};

#endif // _GEOMETRY_GEOMETRY_COLLECTION_H_