#include "Particle.h"
#include "Unit.h"

class SpringDamper {
private:
    Particle* p1;
    Particle* p2;
    float springConst, dampFactor;
    float restLen;

public:
    SpringDamper() = default;
    SpringDamper(Particle* p1, Particle* p2);
    SpringDamper(Particle* p1, Particle* p2, float restLen, float sprConst, float dampFact);

    void computeForce() const;
};