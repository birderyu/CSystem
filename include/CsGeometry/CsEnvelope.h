// �������
#ifndef _CORE_ENVELOPE_H_
#define _CORE_ENVELOPE_H_
// ע�⣺����ṹ�д洢��Zֵ�����ڽ����ڶ�ά�����ݳ��������д�������������
// ��ˣ��ýṹֻ����Ϊһ������ṹ��������Ϊ�洢�ṹ��

#include "CsGeometry.h"
#include "CsCoordinate.h"

class CS_API CsEnvelope
{
public:
	CsEnvelope();
	CsEnvelope(const CsCoordinate &, const CsCoordinate &);

	CsCoordinate Max() const;
	CsCoordinate Min() const;
	CsCoordinate Center() const;

	cs_real MaxX() const;
	cs_real MaxY() const;

	cs_real MinX() const;
	cs_real MinY() const;

	cs_real CenterX() const;
	cs_real CenterY() const;

	cs_real Length() const;
	cs_real Width() const;

	cs_void SetMax(const CsCoordinate &) const;
	cs_void SetMin(const CsCoordinate &) const;
	cs_void SetCenter(const CsCoordinate &) const;

	cs_void SetMaxX(cs_real);
	cs_void SetMaxY(cs_real);

	cs_void SetMinX(cs_real);
	cs_void SetMinY(cs_real);

	cs_void SetCenterX(cs_real);
	cs_void SetCenterY(cs_real);

	cs_void SetLength(cs_real);
	cs_void SetWidth(cs_real);

	virtual cs_uint Dimension() const;

private:
	// MinX, MinY, MinZ, MaxX, MaxY, MaxZ
	cs_real m_tMinCoord[6];
};

#endif // _CORE_ENVELOPE_H_