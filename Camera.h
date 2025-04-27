#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include "Unit.h"

#include <iostream>
using namespace std;

struct Camera {
    Point E, C;
    Unit  U, V, W;

    int view_size;
    int samples;
    int depth;

    void lookAt(Point eye, Point center, Unit up);

    friend ostream& operator<<(ostream& os, const Camera& cam);
    friend istream& operator>>(istream& is, Camera& cam);
};

#endif