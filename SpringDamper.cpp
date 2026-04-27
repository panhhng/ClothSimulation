#include "SpringDamper.h"

SpringDamper::SpringDamper(Particle *p_1, Particle *p_2)
    : p1(p_1), p2(p_2)
{
    Vector delta = p2->getPos() - p1->getPos();
    restLen = delta.length();

    dampFactor = .5;
    springConst = 5000;
}

SpringDamper::SpringDamper(Particle *p_1, Particle *p_2, float l0, float ks, float kd)
    : p1(p_1), p2(p_2), springConst(ks), dampFactor(kd), restLen(l0)
{
}

void SpringDamper::computeForce() const
{
    Vector currPos(p1->getPos(), p2->getPos());
    Unit dir(currPos);
    float currLen = currPos.length();

    float maxLen = restLen * 1.25;

    if (currLen > maxLen)
    {
        float forceMagnitude = springConst * (maxLen - restLen);
        Vector force = dir * forceMagnitude;

        p1->addForce(force);
        p2->addForce(-force);
        return;
    }

    float extend = currLen - restLen;
    Vector velocity = p1->getVelocity() - p2->getVelocity();
    float velocProj = dot(velocity, dir);

    float forceMagnitude = springConst * extend + dampFactor * velocProj;
    Vector force = dir * forceMagnitude;

    p1->addForce(force);
    p2->addForce(-force);
}