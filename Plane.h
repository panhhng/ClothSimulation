#ifndef PLANE_H_
#define PLANE_H_

#include "Unit.h"
#include "Shape.h"
#include "Vector.h"

class Plane : public Shape {
private:
    Unit normal;
    float d;

public: 
    optional<Hit> intersect(const Ray& ray) const override;
    optional<Hit> validHit(float t, const Ray& ray) const override;

    pair<float, float> texel_uv(const Point& point) const override;

    Unit bumpNormal(const Point& point, const Unit& N, float u, float v) const override;
    bool isVisible(float u, float v) const override;
    Color selectColor(float u, float v) const override;

    friend ostream& operator<<(ostream& os, const Plane& plane);
    friend istream& operator>>(istream& is, Plane& plane);
};

#endif