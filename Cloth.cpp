#include "Cloth.h"

Cloth::Cloth(int x, int y)
    : particles(nullptr), triangles(nullptr),
    rows(x), cols(y), 
    num_tris(0),
    gravity(Vector(0, -9.8, 0)), wind(Vector(50, 5, 0))
{
}

int Cloth::getRows() const
{
    return rows;
}

int Cloth::getCols() const
{
    return cols;
}

Particle*** Cloth::getParticles() const
{
    return particles;
}

void Cloth::setWindVelocity(const Vector& w) {
    wind = w;
}

void Cloth::initParticles(const Point &startPos, float dist)
{
    particles = new Particle **[rows];
    for (int i = 0; i < rows; i++)
    {
        particles[i] = new Particle *[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            double xd = ((drand48() * 2 - 1) / 50);
            double yd = ((drand48() * 2 - 1) / 50);
            double zd = ((drand48() * 2 - 1) / 50);     

            Point pos = startPos + Vector(j * dist + xd, -i * dist + yd, zd);

            bool isFixed = i == 0;

            particles[i][j] = new Particle(pos, 1.0);
            particles[i][j]->setFixed(isFixed);
        }
    }
}

void Cloth::initSprings()
{
    //num_springs = (rows - 1) * cols + rows * (cols - 1) + 2 * (rows - 1) * (cols - 1) + rows * (cols - 2) + (rows - 2) * cols;
    springs.clear();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (j < cols - 1)
            {
                springs.push_back(SpringDamper(particles[i][j], particles[i][j + 1]));
            }

            if (i < rows - 1)
            {
                springs.push_back(SpringDamper(particles[i][j], particles[i + 1][j]));
            }

            if (i < rows - 1 && j < cols - 1)
            {
                springs.push_back(SpringDamper(particles[i][j], particles[i + 1][j + 1]));
                springs.push_back(SpringDamper(particles[i + 1][j], particles[i][j + 1]));
            }

            if (j < cols - 2)
            {
                Vector v(particles[i][j]->getPos(), particles[i][j + 2]->getPos());
                float l = v.length();

                springs.push_back(SpringDamper(particles[i][j], particles[i][j + 2], l, 100.0, 0));
            }

            if (i < rows - 2)
            {
                Vector v(particles[i][j]->getPos(), particles[i + 2][j]->getPos());
                float l = v.length();

                springs.push_back(SpringDamper(particles[i][j], particles[i + 2][j], l, 100.0, 0));
            }
        }
    }
}

void Cloth::initTris()
{
    num_tris = 2 * (rows - 1) * (cols - 1);
    triangles = new Triangle[num_tris];

    int index = 0;
    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            triangles[index++] = Triangle(particles[i][j], particles[i][j + 1], particles[i + 1][j]);
            triangles[index++] = Triangle(particles[i][j + 1], particles[i + 1][j + 1], particles[i + 1][j]);
        }
    }
}

void Cloth::initGrid(const Point &startPos, float dist)
{
    initParticles(startPos, dist);
    initSprings();
    initTris();
}

void Cloth::update(float delta)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == 2) {
                ;
            }
            particles[i][j]->clearForces();
            particles[i][j]->addForce(gravity * particles[i][j]->getMass());
        }
    }

    for (SpringDamper& dampers : springs)
    {
        dampers.computeForce();
    }

    for (int i = 0; i < num_tris; i++)
    {
        triangles[i].computeAerodynamicForce(wind);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            particles[i][j]->update(delta);
        }
    }
}