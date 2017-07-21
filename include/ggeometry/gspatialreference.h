#ifndef _GEOMETRY_SPATIAL_REFERENCE_H_
#define _GEOMETRY_SPATIAL_REFERENCE_H_

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

enum class GCoordinateSystemType
{
	/// \brief δ֪����
	Unknown = -1,

	/// \brief ��������ϵͳ
	Geocentric = 0x0001,

	/// \brief ��������ϵͳ
	Geographic = 0x0002,

	/// \brief ͶӰ����ϵͳ
	Projected = 0x0004
};

class GSpatialReference
{
public:
	gint GetSRID() const;
	GCoordinateSystemType GetCoordinateSystemType() const;
};

}
}

#endif // _GEOMETRY_SPATIAL_REFERENCE_H_