#ifndef LIGHT_H
#define LIGHT_H

#include "Point.h"
#include "Color.h"

#include <GLUT/glut.h>

struct Light {
    Point pos;
    Color col;

public:
    void load(int index) const;

    friend ostream& operator<<(ostream& os, const Light& light);
    friend istream& operator>>(istream& is, Light& light);
};

#endif