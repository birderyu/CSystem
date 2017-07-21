/****************************************************************************
**
** gsystem: A quick, micro library of C++
**
** @file	ggeometry.h
** @brief	�������νӿڵĶ���
** @author	birderyu
** @contact	https://github.com/birderyu
** @date	2015-12-31
** @version	1.0
**
****************************************************************************/

#ifndef _GEOMETRY_GEOMETRY_H_
#define _GEOMETRY_GEOMETRY_H_

#include "GCore/gobject.h"
#include "ggeodef.h"

namespace gsystem { // gsystem
	namespace geom { // gsystem.geom
		class GGeometry;
		class GGeometryFactory;
		class GEnvelope;
		class GCoordinate;
		class GCoordinateSequence;
		typedef GSharedPointer<GGeometry> GGeometryPtr;
	} // namespace gsystem.geom
} // namespace gsystem

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

/****************************************************************************
**
** @brief		�������νӿ�
**
** �����������������м��ζ���ӿڵĻ��࣬����Ҫ��ģ�͵�˼�������һ��ӿڷ�װ��
**
****************************************************************************/
class GAPI GGeometry 
	: virtual public GObject
	, virtual public GSerializable
{
public:
	/****************************************************************************
	**
	** @name	~GGeometry
	** @brief	����������destructor��
	**
	** ��������Ӧ��������ģ�virtual����
	**
	****************************************************************************/
	virtual ~GGeometry() = 0;

	/****************************************************************************
	**
	** @name	Factory
	** @brief	��ȡ��ǰ���ζ���Ĺ���
	** @return	{const GGeometryFactory *} ���ζ��󹤳�
	**
	****************************************************************************/
	virtual const GGeometryFactory *Factory() const = 0;

	/****************************************************************************
	**
	** @name	Valid
	** @brief	��ǰʵ���Ƿ���Ч
	** @return	{gbool} ��Ч�򷵻�true�����򷵻�false
	**
	****************************************************************************/
	virtual gbool Valid() const = 0;

	/****************************************************************************
	**
	** @name	GeometryType
	** @brief	��ȡ��ǰ����ļ�������
	** @return	{GGeometryType} ��������ö��
	**
	****************************************************************************/
	virtual GGeometryType GeometryType() const = 0;

	/****************************************************************************
	**
	** @name	Dimension
	** @brief	��ȡ��ǰ�����ά��
	** @return	{GDimension} ά��ö��
	**
	****************************************************************************/
	virtual GDimension Dimension() const = 0;

	/****************************************************************************
	**
	** @name	Envelope
	** @brief	���ɵ�ǰ���ζ�������
	** @return	{GEnvelope} ���
	**
	****************************************************************************/
	virtual GEnvelope Envelope() const = 0;

	/****************************************************************************
	**
	** @name	CoordinateSequence
	** @brief	���ɵ�ǰ���ζ������������
	** @return	{GCoordinateSequence} ��������
	**
	****************************************************************************/
	virtual GCoordinateSequence CoordinateSequence() const = 0;

	virtual GDimension GetCoordinateDimension() const;
	virtual gbool IsEmpty() const;
	virtual gbool IsSimple() const;
	virtual gbool IsRing() const;

	virtual GGeometryPtr CloneGeometry() const;

	//virtual gbool Clear() = 0;
	//virtual GGeometryP Flatten() const = 0; // ����ά��ɶ�ά

	//virtual greal Distance(const GGeometry &geo) const = 0;
	//virtual gbool Touches(const GGeometry &geo) const = 0;
	//virtual gbool Intersects(const GGeometry &geo) const = 0;
	//virtual gbool Disjoint(const GGeometry &geo) const = 0;
	//virtual gbool Crosses(const GGeometry &geo) const = 0;
	//virtual gbool Within(const GGeometry &geo) const = 0;
	//virtual gbool Contains(const GGeometry &geo) const = 0;
	//virtual gbool Overlaps(const GGeometry &geo) const = 0;
	//virtual gbool Covers(const GGeometry &geo) const = 0;
	//virtual gbool CoveredBy(const GGeometry &geo) const = 0;

	//virtual GGeometryP Buffer() const = 0;
	//virtual GGeometryP Intersection(const GGeometry &geo) const = 0;
	//virtual GGeometryP Union(const GGeometry &geo) const = 0;
	//virtual GGeometryP Difference(const GGeometry &geo) const = 0;
};

}
}

#endif // _GEOMETRY_GEOMETRY_H_