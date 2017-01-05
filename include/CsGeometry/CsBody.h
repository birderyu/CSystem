#ifndef _GEOMETRY_BODY_H_
#define _GEOMETRY_BODY_H_

#include "CsGeometry.h"

class CS_API CsBody
	: virtual public CsGeometry
{
public:
	/****************************************************************************
	**
	** CsBody
	**
	** @name	Volume
	** @brief	��ȡ��ǰ���ζ�������
	** @return	{cs_real} ���ֵ��Ĭ�ϵ�λΪ������
	**
	****************************************************************************/
	virtual cs_real Volume() const = 0;
};

#endif // _GEOMETRY_BODY_H_