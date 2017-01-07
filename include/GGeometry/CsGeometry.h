/****************************************************************************
**
** GNova: A quick, micro library of C++
**
** @file	CsGeometry.h
** @brief	�������νӿڵĶ���
** @author	Birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _GEOMETRY_GEOMETRY_H_
#define _GEOMETRY_GEOMETRY_H_

#include "CsGeometryGlobal.h"
#include "GCore/gobject.h"

class CsGeometry;
class CsGeometryFactory;
class CsEnvelope;
class CsCoordinate;
class CsCoordinateSequence;
typedef GSharedPointer<CsGeometry> CsGeometryP;

/****************************************************************************
**
** CsGeometry.h
**
** @class		CsGeometry
** @brief		�������νӿ�
** @module		CsCore
**
** �����������������м��ζ���ӿڵĻ��࣬����Ҫ��ģ�͵�˼�������һ��ӿڷ�װ��
**
****************************************************************************/
class GAPI CsGeometry 
	: public GObject
{
public:
	enum { CLASS_CODE = CLASS_CODE_GEOMETRY, };

public:
	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	~CsGeometry
	** @brief	����������destructor��
	**
	** ��������Ӧ��������ģ�virtual����
	**
	****************************************************************************/
	virtual ~CsGeometry() = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	GeometryFactory
	** @brief	��ȡ��ǰ���ζ���Ĺ���
	** @return	{const CsGeometryFactory *} ���ι���
	**
	****************************************************************************/
	virtual const CsGeometryFactory *GeometryFactory() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	Valid
	** @brief	��ǰʵ���Ƿ���Ч
	** @return	{cs_bool} ��Ч�򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual gbool Valid() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	GeometryType
	** @brief	��ȡ��ǰ����ļ�������
	** @return	{cs_int} �������ͣ���ֵ����ö�� {CS_GEOMETRY_TYPE}
	** @see		{CS_GEOMETRY_TYPE}
	**
	****************************************************************************/
	virtual gint GeometryType() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	Dimension
	** @brief	��ȡ��ǰ�����ά��
	** @return	{cs_int} ά�ȣ���ֵ����ö�� {CS_GEOMETRY_DIMENSION}
	** @see		{CS_GEOMETRY_DIMENSION}
	**
	****************************************************************************/
	virtual guint Dimension() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	Envelope
	** @brief	��ȡ��ǰ���ζ�������
	** @return	{CsEnvelope} ���
	** @see		{CsEnvelope}
	**
	****************************************************************************/
	virtual CsEnvelope Envelope() const = 0;

	/****************************************************************************
	**
	** CsGeometry
	**
	** @name	CoordinateSequence
	** @brief	��ȡ��ǰ���ζ������������
	** @return	{CsCoordinateSequence} ��������
	** @see		{CsCoordinateSequence}
	**
	****************************************************************************/
	virtual CsCoordinateSequence CoordinateSequence() const = 0;
	
	//virtual cs_bool IsEmpty() const = 0;
	//virtual cs_bool IsSimple() const = 0;
	//virtual cs_bool Clear() = 0;
	//virtual CsGeometryP Flatten() const = 0; // ����ά��ɶ�ά

	//virtual cs_real Distance(const CsGeometry &geo) const = 0;
	//virtual cs_bool Touches(const CsGeometry &geo) const = 0;
	//virtual cs_bool Intersects(const CsGeometry &geo) const = 0;
	//virtual cs_bool Disjoint(const CsGeometry &geo) const = 0;
	//virtual cs_bool Crosses(const CsGeometry &geo) const = 0;
	//virtual cs_bool Within(const CsGeometry &geo) const = 0;
	//virtual cs_bool Contains(const CsGeometry &geo) const = 0;
	//virtual cs_bool Overlaps(const CsGeometry &geo) const = 0;
	//virtual cs_bool Covers(const CsGeometry &geo) const = 0;
	//virtual cs_bool CoveredBy(const CsGeometry &geo) const = 0;

	//virtual CsGeometryP Buffer() const = 0;
	//virtual CsGeometryP Intersection(const CsGeometry &geo) const = 0;
	//virtual CsGeometryP Union(const CsGeometry &geo) const = 0;
	//virtual CsGeometryP Difference(const CsGeometry &geo) const = 0;
};

#endif // _GEOMETRY_GEOMETRY_H_