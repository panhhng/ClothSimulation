#include "Vector.h"
#include "Point.h"

#include <cmath>

Vector::Vector(float x, float y, float z)
    :
    x_(x), y_(y), z_(z)
{
}

Vector::Vector(const Point& p1, const Point& p2)
    :
    Vector(p2.x() - p1.x(), p2.y() - p1.y(), p2.z() - p1.z())
{
}

Vector::Vector(const Point& point)
    :
    Vector(point.x(), point.y(), point.z())
{
}

float Vector::x() const {
    return x_;
}

float Vector::y() const {
    return y_;
}

float Vector::z() const {
    return z_;
}

float Vector::sq_length() const {
    return x_ * x_ + y_ * y_ + z_ * z_;
}

float Vector::length() const {
    return sqrt(sq_length());
}

float dot(const Vector& v1, const Vector& v2) {
    float x = v1.x() * v2.x();
    float y = v1.y() * v2.y();
    float z = v1.z() * v2.z();

    return x + y + z;
}

Vector Vector::cross(const Vector& v2) const {
    float x = y_ * v2.z() - z_ * v2.y();
    float y = z_ * v2.x() - x_ * v2.z();
    float z = x_ * v2.y() - y_ * v2.x();

    return Vector(x, y, z);
}

Vector operator+(const Vector& v1, const Vector& v2) {
    float x = v1.x() + v2.x();
    float y = v1.y() + v2.y();
    float z = v1.z() + v2.z();

    Vector vector(x, y, z);
    return vector;
}

Vector Vector::operator-(const Vector& v2) const {
    float x = x_ - v2.x();
    float y = y_ - v2.y();
    float z = z_ - v2.z();

    Vector vector(x, y, z);
    return vector;
}

// Vector Vector::operator-() const{
//     Vector vector(-x_, -y_, -z_);
//     return vector;
// }

Vector operator-(const Vector& v) {
    Vector vector(-v.x(), -v.y(), -v.z());
    return vector;
}

Vector Vector::operator*(float alpha) const {
    float x = x_ * alpha;
    float y = y_ * alpha;
    float z = z_ * alpha;

    Vector vector(x, y, z);
    return vector;
}

Vector operator*(float alpha, const Vector& v) {
    return v * alpha;
}

Vector operator/(const Vector& v, float alpha) {
    return v * (1.0 / alpha);
}

Point operator+(const Point& p, const Vector& v) {
    Point point(p.x() + v.x(), p.y() + v.y(), p.z() + v.z());
    return point;
}

Point operator-(const Point& p, const Vector& v) {
    Point point(p.x() - v.x(), p.y() - v.y(), p.z() - v.z());
    return point;
}

ostream& operator<<(ostream& os, const Vector& v) {
    os << "Vector(" << v.x_ << ", " << v.y_ << ", " << v.z_ << ")";
    return os;
}

istream& operator>>(istream& is, Vector& v) {
    char ch;
    float x, y, z;

    is >> ch;
    is >> x;
    is >> ch;
    is >> y;
    is >> ch;
    is >> z;
    is >> ch;

    v = Vector(x, y, z);
    return is;
}

bool Vector::operator==(const Vector& v2) const {
    return x_ == v2.x() && y_ == v2.y() && z_ == v2.z();
}

Point Vector::point() const {
    return Point(x_, y_, z_);
}