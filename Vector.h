#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

class Vector {
private:
    float x_ = 0;
    float y_ = 0;
    float z_ = 0;

public:
    Vector() = default;

    Vector(float x, float y, float z);

    Vector(const Point& p1, const Point& p2);

    Vector(const Point& point);

    float x() const;
    float y() const;
    float z() const;

    float sq_length() const;
    float length() const;

    Vector cross(const Vector& v2) const;

    Point point() const;

    Vector operator-(const Vector& v2) const;

    // Vector operator-() const;

    Vector operator*(float alpha) const;

    bool operator==(const Vector& v2) const;

    friend ostream& operator<<(ostream& os, const Vector& v);

    friend istream& operator>>(istream& is, Vector& v);
};

float dot(const Vector& v1, const Vector& v2);

Vector operator+(const Vector& v1, const Vector& v2);

Vector operator-(const Vector& v);

Vector operator*(float alpha, const Vector& v);

Vector operator/(const Vector& v, float alpha);

Point operator+(const Point& p, const Vector& v);

Point operator-(const Point& p, const Vector& v);

#endif