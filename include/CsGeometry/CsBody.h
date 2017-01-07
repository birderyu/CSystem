#ifndef _GEOMETRY_BODY_H_
#define _GEOMETRY_BODY_H_

#include "CsGeometry.h"

class GAPI CsBody
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
	virtual greal Volume() const = 0;
};

#endif // _GEOMETRY_BODY_H_