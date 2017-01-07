#ifndef _GEOMETRY_SURFACE_H_
#define _GEOMETRY_SURFACE_H_

#include "CsGeometry.h"

class GAPI CsSurface
	: virtual public CsGeometry
{
public:
	/****************************************************************************
	**
	** CsSurface
	**
	** @name	Area
	** @brief	��ȡ��ǰ���ζ�������
	** @return	{cs_real} ���ֵ��Ĭ�ϵ�λΪƽ����
	**
	****************************************************************************/
	virtual greal Area() const = 0;
};

#endif // _GEOMETRY_SURFACE_H_