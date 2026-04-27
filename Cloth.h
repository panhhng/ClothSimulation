#ifndef CLOTH_H
#define CLOTH_H

#include "Particle.h"
#include "SpringDamper.h"
#include "Triangle.h"

class Cloth
{
private:
    Particle ***particles;
    vector<SpringDamper> springs;
    Triangle *triangles;

    int rows, cols;
    int num_tris;
    Vector gravity, wind;

public:
    Cloth(int rows, int cols);

    int getRows() const;
    int getCols() const;
    Particle ***getParticles() const;

    void setWindVelocity(const Vector &w);

    void initParticles(const Point &startPos, float dist);
    void initSprings();
    void initTris();
    void initGrid(const Point &startPos, float dist);

    struct SphereCollider
    {
        bool enabled;
        Point center;
        float radius;
        float offset;
        float friction;
    };

    struct PlatformCollider
    {
        bool enabled;
        float y;
        float offset;
        float friction;
    };

    void update(float delta, const SphereCollider &sphere, const PlatformCollider &platform);
};

#endif