#include "Unit.h"
#include "Vector.h"

Unit::Unit(float x, float y, float z) 
    :
    Unit(Vector(x, y, z))
{
}

Unit::Unit(const Vector& v) 
    :
    Vector(v / v.length())
{
}

Unit::Unit(const Point& p1, const Point& p2)
    :
    Unit(Vector(p1, p2))
{
}

ostream& operator<<(ostream& os, const Unit& u) {
    os << "Unit(" << u.x() << ", " << u.y() << ", " << u.z() << ")";
    return os;
}