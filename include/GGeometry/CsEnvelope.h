// �������
#ifndef _GEOMETRY_ENVELOPE_H_
#define _GEOMETRY_ENVELOPE_H_

// ע�⣺����ṹ�д洢��Zֵ�����ڽ����ڶ�ά�����ݳ��������д�������������
// ��ˣ��ýṹֻ����Ϊһ������ṹ��������Ϊ�洢�ṹ��

#include "CsGeometryGlobal.h"
#include "GCore/gobject.h"

class CsCoordinate;
class CsCoordinateSequence;

class GAPI CsEnvelope
	: public GObject
{
public:
	CsEnvelope();
	CsEnvelope(greal x, greal y);
	CsEnvelope(greal x, greal y, greal z);
	CsEnvelope(greal min_x, greal min_y, greal max_x, greal max_y);
	CsEnvelope(greal min_x, greal min_y, greal min_z, greal max_x, greal max_y, greal max_z);
	CsEnvelope(const CsCoordinate &min_c, const CsCoordinate &max_c);
	CsEnvelope(const CsCoordinateSequence &);
	CsEnvelope(const CsEnvelope &);

	CsCoordinate Min() const;
	CsCoordinate Max() const;
	CsCoordinate Center() const;

	greal MinX() const;
	greal MinY() const;
	greal MinZ() const;

	greal MaxX() const;
	greal MaxY() const;
	greal MaxZ() const;

	greal CenterX() const;
	greal CenterY() const;
	greal CenterZ() const;

	greal Length() const;
	greal Width() const;
	greal Height() const;

	gvoid SetMin(const CsCoordinate &);
	gvoid SetMax(const CsCoordinate &);
	gvoid SetCenter(const CsCoordinate &);

	gvoid SetMinX(greal);
	gvoid SetMinY(greal);
	gvoid SetMinZ(greal);

	gvoid SetMaxX(greal);
	gvoid SetMaxY(greal);
	gvoid SetMaxZ(greal);

	gvoid SetCenterX(greal);
	gvoid SetCenterY(greal);
	gvoid SetCenterZ(greal);

	gvoid SetLength(greal);
	gvoid SetWidth(greal);
	gvoid SetHeight(greal);

	guint Dimension() const;

private:
	// MinX, MinY(, MinZ), MaxX, MaxY(, MaxZ)
	greal m_tCoords[CS_ENVELOPE_SIZE];
};

#endif // _GEOMETRY_ENVELOPE_H_