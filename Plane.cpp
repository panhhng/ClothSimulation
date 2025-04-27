#include "Plane.h"

optional<Hit> Plane::intersect(const Ray& ray) const {
    float denom = dot(normal, ray.dir());
    float num = -(dot(normal, ray.origin()) + d);

    float t = num / denom;

    optional<Hit> hit = validHit(t, ray);
    return hit;
}

optional<Hit> Plane::validHit(float t, const Ray& ray) const {
    if (!gt_zero(t)) {
        return {};
    }

    Point pos(ray.point(t));

    auto[u, v] = texel_uv(pos);
    if (!isVisible(u, v)) {
        return {};
    }

    Color color = selectColor(u, v);
    Unit n = bumpNormal(pos, normal, u, v);

    return Hit{pos, n, color, mat, t};
}

pair<float, float> Plane::texel_uv(const Point& point) const {
    Vector vector(normal * d);
    Point Q = vector.point();

    Unit y_axis(0, 1, 0);
    Unit U = y_axis.cross(normal);
    Unit V = normal.cross(U);

    Vector QP = Vector(Q, point);

    float u = dot(QP, U);
    float v = dot(QP, V);

    return {u, v};
}

Unit Plane::bumpNormal(const Point& point, const Unit& N, float u, float v) const {
    if (bump == nullptr) {
        return N;
    }

    Unit y_axis(0, 1, 0);
    Unit U = y_axis.cross(N);
    Unit V = N.cross(U);
    
    auto [du, dv] = bump->gradient_wh(u, v);
    
    return Unit(N + U * du + V * dv);
}

bool Plane::isVisible(float u, float v) const {
    if (mask == nullptr) {
        return true;
    }
    
    return gt_zero(mask->gray_wh(u, v));
}

Color Plane::selectColor(float u, float v) const {
    if (texture == nullptr) {
        return col;
    }

    return texture->rgb_wh(u, v);
}

istream& operator>>(istream& is, Plane& plane) {
    string str;

    is >> str;
    is >> plane.normal;

    is >> str;
    is >> plane.d;

    plane.readAppearance(is);

    return is;
}

ostream& operator<<(ostream& os, const Plane& plane) {
    os << "Plane: " << plane.normal << " " << plane.d << endl;
    return os;
}