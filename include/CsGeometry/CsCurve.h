#ifndef _GEOMETRY_CURVE_H_
#define _GEOMETRY_CURVE_H_

#include "CsGeometry.h"
#include "CsPoint.h"

class CS_API CsCurve
	: virtual public CsGeometry
{
public:
	/****************************************************************************
	**
	** CsCurve
	**
	** @name	Length
	** @brief	��ȡ��ǰ���ζ���ĳ���
	** @return	{cs_real} ����ֵ��Ĭ�ϵ�λΪ��
	**
	****************************************************************************/
	virtual cs_real Length() const = 0;

	virtual CsPointP StartPoint() = 0;
	virtual const CsPointP StartPoint() const = 0;
	virtual CsPointP EndPoint() = 0;
	virtual const CsPointP EndPoint() const = 0;

	virtual cs_size_t PointCount() const = 0;
	virtual CsPointP GetPointAt(cs_size_t pos) = 0;
	virtual const CsPointP GetPointAt(cs_size_t pos) const = 0;
	virtual cs_void SetPointAt(cs_size_t pos, const CsPointP &poi) = 0;

	// �Ƿ�պ�
	virtual cs_bool IsClosed() const = 0;
};

#endif // _GEOMETRY_CURVE_H_