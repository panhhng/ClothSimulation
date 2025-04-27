#ifndef SHAPE_H
#define SHAPE_H

#include "Ray.h"
#include "Hit.h"
#include "Material.h"
#include "Point.h"
#include "utils.h"
#include "Image.h"

#include <GLUT/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

class Shape {
protected:
    Material mat;
    Color col;
    Image *texture = nullptr;
    Image *mask    = nullptr;
    Image *bump    = nullptr;

public:
    ~Shape();

    virtual void draw() const {

    };

    virtual optional<Hit> intersect(const Ray& ray) const = 0;
    virtual optional<Hit> validHit(float t, const Ray& ray) const = 0;
    
    pair<float, float> solveEquation(float a, float b, float c) const;
    istream& readAppearance(istream& is);

    virtual pair<float, float> texel_uv(const Point& point) const = 0;
    virtual bool isVisible(float u, float v) const;

    virtual Color selectColor(float u, float v) const;

    virtual Unit bumpNormal(const Point& point, const Unit& N, float u, float v) const = 0;
};

#endif