#ifndef HIT_H_
#define HIT_H_

#include "Point.h"
#include "Unit.h"
#include "Color.h"
#include "Material.h"

struct Hit {
    Point    pos;
    Unit     normal;
    Color    col;
    Material mat;
    float    t, u, v;
};

#endif