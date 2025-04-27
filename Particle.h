#ifndef PARTICLE_H
#define PARTICLE_H

#include "Point.h"
#include "Vector.h"

class Particle {
private:
    Point  pos;
    Vector velocity;
    Vector acceleration;
    float  mass;
    Vector momentum;
    Vector forces;
    bool fixed;
    Vector normal;

public:
    Particle() = default;
    Particle(const Point& p, float m);

    Point getPos() const;
    Vector getVelocity() const;
    float getMass() const;
    Vector getNormal() const;

    void setFixed(bool val);
    void addForce(const Vector& f);
    void update(float dt);
    bool isFixed() const;

    void clearForces();
};

#endif