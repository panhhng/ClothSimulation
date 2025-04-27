#ifndef CLOTH_H
#define CLOTH_H

#include "Particle.h"
#include "SpringDamper.h"
#include "Triangle.h"

class Cloth {
private:
    // vector<vector<Particle>> particles;
    Particle** *particles;
    vector<SpringDamper>     springs;
    // SpringDamper* springs;
    // vector<Triangle>         triangles;
    Triangle* triangles;

    int rows, cols;
    int num_tris;
    Vector gravity, wind;

public:
    Cloth(int rows, int cols);

    int getRows() const;
    int getCols() const;
    Particle*** getParticles() const;

    void setWindVelocity(const Vector& w);

    void initParticles(const Point& startPos, float dist);
    void initSprings();
    void initTris();
    void initGrid(const Point& startPos, float dist);

    void update(float delta);
};

#endif