// ע�⣺����ṹ�д洢��Zֵ�����ڽ����ڶ�ά�����ݳ��������д�������������
// ��ˣ��ýṹֻ����Ϊһ������ṹ��������Ϊ�洢�ṹ��

#ifndef _GEOMETRY_COORDINATE_H_
#define _GEOMETRY_COORDINATE_H_

#include "CsGeometry.h"

class CS_API CsCoordinate
{
public:
	CsCoordinate();
	CsCoordinate(cs_real x, cs_real y, cs_real z);

	cs_real X() const;
	cs_real Y() const;
	cs_real Z() const;

	cs_void SetX(cs_real);
	cs_void SetY(cs_real);
	cs_void SetZ(cs_real);

private:
	cs_real m_tCoordinate[CsGeometry::DIMENSION_3];
};

#endif // _GEOMETRY_COORDINATE_EX_H_