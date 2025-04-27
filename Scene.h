#ifndef SCENE_H
#define SCENE_H

#include "Light.h"
#include "Color.h"
#include "Camera.h"
#include "Image.h"
#include "Hit.h"
#include "Shape.h"
#include "Plane.h"

#include <string>
#include <fstream>
#include <cfloat>
#include <GLUT/glut.h>

class Scene {
private:
    Camera         cam;
    Color          ambient;
    vector<Light>  lights;
    vector<Shape*> shapes;

    int   frames;
    float radius;
    float height;

public:
    Scene(const string& filename); 
    ~Scene();

    int get_size() const;
    int get_samples() const;

    void render(const string& filename) const;
    Color trace(const Ray& ray, int depth) const;

    void draw() const;
    void setup_lighting() const;

    void animate(const string& moviePath);
    void animate_spherical(const string& moviePath);
    void animate_cylindrical(const string& moviePath);

    optional<Hit> findClosestHit(const Ray& ray, const vector<Shape*>& shapes, float maxDist = FLT_MAX) const;
};

#endif