#ifndef UNIT_H
#define UNIT_H

#include "Vector.h"
#include "Point.h"

class Unit : public Vector {
public:
    Unit() = default;
    
    Unit(float x, float y, float z);

    Unit(const Vector& v);

    Unit(const Point& p1, const Point& p2);

    friend ostream& operator<<(ostream& os, const Unit& u);
};

#endif