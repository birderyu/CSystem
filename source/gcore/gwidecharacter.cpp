#include "gwidecharacter.h"

namespace gsystem { // gsystem

GWideCharacter::GWideCharacter(gwchar val)
: GPackage<gwchar>(val)
{

}
GWideCharacter::GWideCharacter(const GWideCharacter &val)
: GPackage<gwchar>(val)
{

}

guint GWideCharacter::ClassCode() const GNOEXCEPT
{
	return static_cast<guint>(GClassCode::WindCharacter);
}

} // namespace gsystem
