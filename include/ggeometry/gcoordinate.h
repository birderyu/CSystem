#ifndef _GEOMETRY_COORDINATE_H_
#define _GEOMETRY_COORDINATE_H_

#include "ggeodef.h"
#include "GCore/gobject.h"

namespace gsystem { // gsystem
namespace geom { // gsystem.geom

class GAPI GCoordinate final
	: public GObject
{
	friend class GEnvelope;

public:
	GCoordinate();
	GCoordinate(greal x, greal y);
	GCoordinate(greal x, greal y, greal z);
	GCoordinate(const greal *p_c, gsize size);
	GCoordinate(const GCoordinate &coord);

	greal &X();
	greal  X() const;
	greal &Y();
	greal  Y() const;
	greal &Z();
	greal  Z() const;

	gvoid SetX(greal);
	gvoid SetY(greal);
	gvoid SetZ(greal);

	guint Dimension() const;

	const greal *Cursor() const;

private:
	greal m_tCoord[G_COORDINATE_SIZE];
};

}
}

#endif // _GEOMETRY_COORDINATE_EX_H_