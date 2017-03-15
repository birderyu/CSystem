#ifndef _GEOMETRY_GEOMETRY_HELPER_H_
#define _GEOMETRY_GEOMETRY_HELPER_H_

#include "ggeometryinterface.h"

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

class GAPI GGeometryHelper
{
public:
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(GGeometryP &geo);
	template<typename GeometryT> static GSharedPointer<GeometryT> ConvertTo(GPointP &point);
};

}
}

#include "ggeometryhelper.inl"

#endif // _GEOMETRY_GEOMETRY_HELPER_H_