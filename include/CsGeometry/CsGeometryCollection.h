#ifndef _GEOMETRY_GEOMETRY_COLLECTION_H_
#define _GEOMETRY_GEOMETRY_COLLECTION_H_

#include "CsGeometry.h"

class GAPI CsGeometryCollection
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
	virtual gsize Size() const = 0;

	virtual CsGeometryP GetAt(gsize pos) = 0;
	virtual const CsGeometryP GetAt(gsize pos) const = 0;
	virtual gvoid SetAt(gsize pos, const CsGeometryP &geo) = 0;
};

#endif // _GEOMETRY_GEOMETRY_COLLECTION_H_