#include "Scene.h"

#include <fstream>
#include <string>

#include <iostream>
using namespace std;

Scene::Scene(const string& filename) {
    string str;

    ifstream ifs(filename);

    cout << "Scene: " << filename << endl;

    while (ifs >> str) {
        if (str == "light_ambient") {
            ifs >> ambient;
            ifs >> str;
        }
        else if (str == "light_source") {  
            Light light;        
            ifs >> light;
            lights.push_back(light);
        }
        else if (str == "camera") {
            ifs >> cam;
            cout << cam << endl;
        }
        else if (str == "plane") {
            Plane* shape = new Plane();
            ifs >> *shape;
            shapes.push_back(shape);
        }
        else if (str == "movie") {
            ifs >> str >> frames;
            ifs >> str >> radius;
            ifs >> str >> height;
            ifs >> str;
        }
    }
}

Scene::~Scene() {
    for (Shape* shape : shapes) {
        delete shape;
    }

    shapes.clear();
}

int Scene::get_size() const {
    return cam.view_size;
}

int Scene::get_samples() const {
    return cam.samples;
}

void Scene::render(const string& filename) const {
    Image canvas(cam.samples, cam.samples);

    float step = float(cam.view_size) / (cam.samples - 1);

    float dist = cam.view_size / 2.0;
    Point UL = cam.C - dist * cam.W + dist * cam.U;

    for (int j = 0; j < cam.samples; j++) {
        for (int i = 0; i < cam.samples; i++) {
            Point P = UL + i * step * cam.W - j * step * cam.U;
            
            Ray ray(cam.E, P);
            Color col = trace(ray, cam.depth); 
            
            canvas.setPixel(i, j, col);
        }
    }

    canvas.saveImage(filename);
    canvas.clear();
}

void Scene::draw() const {
    // glPushMatrix();  	 

	for (const Shape* shape : shapes) {
        glPushMatrix();
        shape->draw();
        glPopMatrix();
    }

	glFlush();              
}

void Scene::setup_lighting() const {
    glEnable(GL_LIGHTING);

    GLfloat amb_color[] = { ambient.r(), ambient.g(), ambient.b(), 1 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_color );

    for (int i = 0; i < lights.size() && i < 8; i++) {
        lights[i].load(i);
    }
}

void Scene::animate(const string& moviePath) {
    Point center(0, 0, 0);  
    Unit up(0, 1, 0);    
    
    for (int frame = 0; frame < frames; frame++) {
        float theta = frame * frames; 

        float xP = radius * sin(theta);
        float yP = radius;  
        float zP = radius * cos(theta);
        
        Point eye(xP, yP, zP);
        cam.lookAt(eye, center, up);
        
        string filename = moviePath + to_string(100 + frame) + ".ppm";
        render(filename);
    }
}

void Scene::animate_spherical(const string& moviePath) {
    Point center(0, 0, 0);
    Unit up(0, 1, 0);    

    float d_theta = 2 * M_PI / frames;
    float d_phi = (M_PI / 2 - M_PI / 3) / frames;

    for (int frame = 0; frame < frames; frame++) {
        float theta = frame * d_theta;
        float phi = M_PI / 2 - frame * d_phi; 

        float x = radius * sin(phi) * sin(theta);
        float y = radius * cos(phi);
        float z = radius * sin(phi) * cos(theta);
        Point eye(x, y, z);

        Unit curr_theta = up.cross(-cam.V);
        Unit curr_phi(-cam.V.cross(curr_theta));
        
        cam.lookAt(eye, center, curr_phi);
        
        string filename = moviePath + to_string(100 + frame) + ".ppm";
        render(filename);
    }
}

void Scene::animate_cylindrical(const string& moviePath) {
    Unit up(0, 1, 0);

    float d_Theta = 2 * M_PI / frames;

    for (int frame = 0; frame < frames; frame++) {
        float theta = frame * d_Theta;

        float x = radius * sin(theta);
        float y = height * (1 - cos(theta)) / 2;
        float z = radius * cos(theta);
        Point eye(x, y, z);

        float theta_pi = theta + M_PI;
        float sin_pi = sin(theta_pi);
        float cos_pi = cos(theta_pi);
        float denom = 1 + pow(sin_pi, 2);

        float px = -(radius / 10) * sin_pi * cos_pi / denom;
        float py = 0;
        float pz = (radius / 10) * cos_pi / denom;

        Point point(px, py, pz);

        cam.lookAt(eye, point, up);
        string filename = moviePath + to_string(100 + frame) + ".ppm";
        render(filename);
    }
}

Color Scene::trace(const Ray& ray, int depth) const {
    if (depth == 0) {
        return Color(0, 0, 0); 
    }

    optional<Hit> hit = findClosestHit(ray, shapes);
    if (!hit) {
        return Color(0, 0, 0);
    }

    Color ambient_comp(hit->mat.ka * hit->col * ambient);

    Point Q = hit->pos;
    Unit  N = hit->normal;
    Unit  V = -ray.dir();

    Color diffuse_comp(0, 0, 0);
    Color specular_comp(0, 0, 0);

    if (dot(N, V) < 0) {
        return ambient_comp;
    }

    for (const Light& curr_light : lights) {
        Unit L(Q, curr_light.pos);
        
        Ray shadow(Q, L);
        float dist = Vector(Q, curr_light.pos).length();
        optional<Hit> rHit = findClosestHit(shadow, shapes, dist);

        if (!rHit && dot(N, L) > 0) {
            Unit R = 2 * N * dot(N, L) - L;

            diffuse_comp = diffuse_comp + hit->mat.kd * hit->col * curr_light.col * dot(N, L);

            if (dot(R, V) > 0) {
                specular_comp = specular_comp + hit->mat.ks * hit->col * curr_light.col * pow(dot(R, V), hit->mat.n);
            }
        }
    }

    Unit V_R = 2 * N * dot(N, V) - V;
    Ray reflect(Q, V_R);

    Color reflection_comp = hit->mat.ks * trace(reflect, depth - 1);

    return ambient_comp + diffuse_comp + specular_comp + reflection_comp;
}

optional<Hit> Scene::findClosestHit(const Ray& ray, const vector<Shape*>& shapes, float maxDist) const {
    optional<Hit> closest;

    float currDist = maxDist;
    for (const Shape* curr_shape : shapes) {
        optional<Hit> hit = curr_shape->intersect(ray);

        if (hit && hit->t < currDist) {
            currDist = hit->t;
            closest = hit;
        }
    }

    return closest;
}