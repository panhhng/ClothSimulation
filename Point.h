#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

class Point {
private:
    float x_ = 0;
    float y_ = 0;
    float z_ = 0;

public:
    Point() = default;

    Point(float x, float y, float z);

    float x() const;
    float y() const;
    float z() const;

    bool operator==(const Point& p2) const;

    friend ostream& operator<<(ostream& os, const Point& point);
    friend istream& operator>>(istream& is, Point& point);
};

#endif