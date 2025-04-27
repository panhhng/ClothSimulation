#include "Material.h"

void Material::load(const Color& color) const {
    float r = color.r();
    float g = color.g();
    float b = color.b();

    GLfloat mat_amb[]  = { ka * r, ka * g, ka * b, 1.0 }; 
	GLfloat mat_diff[] = { kd * r, kd * g, kd * b, 1.0 };  
	GLfloat mat_spec[] = { ks * r, ks * g, ks * b, 1.0 }; 
    GLfloat mat_phong[] = { n }; 

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_phong);
}

ostream& operator<<(ostream& os, const Material& mat) {
    os << "Mat(" << mat.ka << "," << mat.kd << "," << mat.ks << "," << mat.n << ")" << endl;
    return os;
}

istream& operator>>(istream& is, Material& mat) {
    string str;

    is >> str >> mat.ka;
    is >> str >> mat.kd;
    is >> str >> mat.ks;
    is >> str >> mat.n;
    is >> str;

    return is;
}