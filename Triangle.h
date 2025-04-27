#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Particle.h"
#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include "Unit.h"
#include "Material.h"
#include "Ray.h"
#include "Hit.h"
#include "utils.h"

#include <array>
#include <optional>

using namespace std;

class Triangle {
private:
    array<Particle*, 3> particles; 
    array<Vector, 3> normals;     
    array<Color, 3> colors;      
    Vector flat_normal;          
    Color color;                
    
    float airDensity;      
    float drag;       
    
    static bool is_smooth;      
    
    void updateNormals();       

public:
    Triangle() = default;
    Triangle(Particle* p1, Particle* p2, Particle* p3, 
             float rho = 1.225, float cd = 1.0);
    
    void computeAerodynamicForce(const Vector& windVeloc);
    void draw(const Material& mat) const;
    void setSmooth(bool smooth);

    static void setGlobalSmooth(bool smooth) { is_smooth = smooth; }
};

#endif