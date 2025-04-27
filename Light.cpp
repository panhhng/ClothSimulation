#include "Light.h"

void Light::load(int index) const {
	float position[] = {pos.x(), pos.y(), pos.z(), 1.0};
    glLightfv(GL_LIGHT0+index, GL_POSITION, position);

	GLfloat  light_color[] = { col.r(), col.g(), col.b(), 1 };

    glLightfv(GL_LIGHT0+index, GL_DIFFUSE,  light_color);
    glLightfv(GL_LIGHT0+index, GL_SPECULAR, light_color);
    
	glEnable(GL_LIGHT0+index);
}

ostream& operator<<(ostream& os, const Light& light) {
    os << light.pos << ", " << light.col;
	return os;
}

istream& operator>>(istream& is, Light& light) {
    string tag;

	is >> tag;        
	is >> light.pos;                 
    is >> light.col;
	is >> tag;

	return is;
}