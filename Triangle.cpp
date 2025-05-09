#include "Triangle.h"

bool Triangle::is_smooth = true;

Triangle::Triangle(Particle *p1, Particle *p2, Particle *p3,
                   float rho, float cd)
    : particles{p1, p2, p3}, airDensity(rho), drag(cd),
      colors{Color(0.7, 0.7, 0.7), Color(0.7, 0.7, 0.7), Color(0.7, 0.7, 0.7)},
      color(0.7, 0.7, 0.7)
{
    updateNormals();
}

void Triangle::updateNormals()
{
    Vector v1v2 = particles[1]->getPos() - particles[0]->getPos();
    Vector v1v3 = particles[2]->getPos() - particles[0]->getPos();

    flat_normal = Unit(v1v2.cross(v1v3));

    if (!is_smooth)
    {
        normals[0] = flat_normal;
        normals[1] = flat_normal;
        normals[2] = flat_normal;
    }
}

void Triangle::computeAerodynamicForce(const Vector &windVeloc)
{
    updateNormals();

    Vector surfaceVeloc = (particles[0]->getVelocity() +
                            particles[1]->getVelocity() +
                            particles[2]->getVelocity()) /
                            3.0;

    Vector relVeloc = surfaceVeloc - windVeloc;

    Vector edge1 = particles[1]->getPos() - particles[0]->getPos();
    Vector edge2 = particles[2]->getPos() - particles[0]->getPos();
    float area = 0.5 * edge1.cross(edge2).length();

    float dotProd = dot(flat_normal, relVeloc);

    if (gt_zero(dotProd))
    {
        return;
    }

    float relVelLength = relVeloc.length();
    float crossSecArea = area;
    if (gt_zero(relVelLength))
    {
        crossSecArea *= abs(dotProd) / relVelLength;
    }

    float forceMagnitude = - 0.5 * airDensity * relVelLength * relVelLength *
                           drag * crossSecArea;

    Vector force = flat_normal * forceMagnitude;
    force = force / 3.0;

    particles[0]->addForce(force);
    particles[1]->addForce(force);
    particles[2]->addForce(force);
}

void Triangle::draw(const Material &mat) const
{
    for (int i = 0; i < 3; i++)
    {
        if (is_smooth)
        {
            Vector normal = particles[i]->getNormal();
            glNormal3f(normal.x(), normal.y(), normal.z());
        }
        else
        {
            glNormal3f(flat_normal.x(), flat_normal.y(), flat_normal.z());
        }

        mat.load(colors[i]);

        Point curr_pos = particles[i]->getPos();
        glVertex3f(curr_pos.x(), curr_pos.y(), curr_pos.z());
    }
}

void Triangle::setSmooth(bool smooth)
{
    is_smooth = smooth;
    for (int i = 0; i < 3; i++)
    {
        Point pos = particles[i]->getPos();
        Unit unit(pos);

        colors[i] = Color(fabs(unit.x()), fabs(unit.y()), fabs(unit.z()));

        if (!smooth)
        {
            normals[i] = flat_normal;
        }
    }
}