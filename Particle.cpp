#include "Particle.h"

Particle::Particle(const Point &p, float m)
    : pos(p), mass(m)
{
    acceleration = forces / mass;
    momentum = mass * velocity;
}

float Particle::getMass() const
{
    return mass;
}

Point Particle::getPos() const
{
    return pos;
}

Vector Particle::getVelocity() const
{
    return velocity;
}

Vector Particle::getNormal() const
{
    return normal;
}

void Particle::setFixed(bool val)
{
    fixed = val;
}

void Particle::addForce(const Vector &f)
{
    if (!isFixed())
    {
        forces = forces + f;
    }
}

bool Particle::isFixed() const
{
    return fixed;
}

void Particle::clearForces()
{
    forces = Vector(0, 0, 0);
}

void Particle::setPos(const Point &p)
{
    pos = p;
}

void Particle::setVelocity(const Vector &v)
{
    velocity = v;
}

void Particle::update(float dt)
{
    if (!fixed)
    {
        Vector acc = forces * (1.0 / mass);

        velocity = velocity + (acc * dt);
        pos = pos + (velocity * dt);

        float y0 = -0.8;
        float elasticity = 0.1;
        float friction = 0.05;

        if (pos.y() < y0)
        {
            pos = Point(pos.x(), y0, pos.z());

            velocity = Vector(
                velocity.x() * (1.0 - friction),
                -elasticity * velocity.y(),
                velocity.z() * (1.0 - friction));
        }
    }
}