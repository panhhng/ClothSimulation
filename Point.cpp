#include "Point.h"

Point::Point(float x, float y, float z)
    :
    x_(x), y_(y), z_(z)
{
}

float Point::x() const {
    return x_;
}

float Point::y() const {
    return y_;
}

float Point::z() const {
    return z_;
}

bool Point::operator==(const Point& p2) const {
    return x_ == p2.x() && y_ == p2.y() && z_ == p2.z();
}

ostream& operator<<(ostream& os, const Point& point) {
    os << "Point(" << point.x_ << ", " << point.y_ << ", " << point.z_ << ")";
    return os;
}

istream& operator>>(istream& is, Point& point) {
	char ch;
	float x, y, z;

    is >> ch;
    is >> x >> ch;
    is >> y >> ch;
    is >> z;
    is >> ch;

    point = Point(x, y, z);

    return is;
}