#include "gbyte.h"

namespace gnova { // gnova

GByte::GByte(gbyte val)
: GPackage<gbyte>(val)
{

}

GByte::GByte(const GByte &val)
: GPackage<gbyte>(val)
{

}

guint GByte::ClassCode() const
{
	return GByte::CLASS_CODE;
}

}
