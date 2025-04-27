#include "Camera.h"

void Camera::lookAt(Point eye, Point center, Unit up) {
    E = eye;
    C = center;
    
    U = up;
    V = Unit(E, C);
    W = V.cross(U);
}

ostream& operator<<(ostream& os, const Camera& cam) {
    os << "Camera: " << "pos " << cam.E << " " << cam.view_size << "cm " << cam.samples << "px " 
       << "center " << cam.C << " up " << cam.U << "V " << cam.V << " W " << cam.W <<endl;
    return os;
}

istream& operator>>(istream& is, Camera& cam) {
    string str;

    is >> str >> cam.E;
    is >> str >> cam.view_size;
    is >> str >> cam.samples;
    is >> str >> cam.depth;
    is >> str >> cam.C;
    is >> str >> cam.U;

    cam.lookAt(cam.E, cam.C, cam.U);

    return is;
}