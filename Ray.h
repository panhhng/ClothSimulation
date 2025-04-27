#ifndef RAY_H
#define RAY_H

#include "Point.h"
#include "Unit.h"

class Ray {
private:
    Point origin_;
    Unit dir_;

public:
    Ray(const Point& p, const Vector& d);

    Ray(const Point& p1, const Point& p2);

    Point origin() const;

    Vector dir() const;

    Point point(float t) const;

    friend ostream& operator<<(ostream& os, const Ray& r);
};

#endif