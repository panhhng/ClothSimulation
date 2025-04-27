#include "Ray.h"
#include "Vector.h"

Ray::Ray(const Point& p, const Vector& d) 
    :
    origin_(p), dir_(d)
{
}

Ray::Ray(const Point& p1, const Point& p2) 
    :
    Ray(p1, Vector(p1, p2))
{
}

Point Ray::origin() const {
    return origin_;
}

Vector Ray::dir() const {
    return dir_;
}

Point Ray::point(float t) const {
    return origin_ + dir_ * t;
}

ostream& operator<<(ostream& os, const Ray& r) {
    os << r.origin() << ", " << r.dir();
    return os;
}