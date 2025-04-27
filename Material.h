#ifndef MATERIAL_H
#define MATERIAL_H

#include "Color.h"

#include <GLUT/glut.h>
#include <iostream>
using namespace std;

struct Material {
    float ka, kd, ks, n;

public:
    void load(const Color& color) const;

    friend ostream& operator<<(ostream& is, const Material& mat);
    friend istream& operator>>(istream& is, Material& mat);
};

#endif /* MATERIAL_H */