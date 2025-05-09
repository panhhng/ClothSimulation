#include <GLUT/glut.h>
#include <iostream>
#include "Cloth.h"

Cloth* cloth = nullptr;

int w = 600;
int h = 600;

void init() {
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1, -1, 1, -1, 1);
    
    glEnable( GL_COLOR_MATERIAL );
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    cloth = new Cloth(7, 10);
    cloth->initGrid(Point(-0.5, 0.5, 0.0), 0.1);
}

void renderCloth() {
    Particle*** particles = cloth->getParticles();
    int rows = cloth->getRows();
    int cols = cloth->getCols();
    
    glColor3f(0.7, 0.3, 0.3); 
    glBegin(GL_TRIANGLES);
    
    // glVertex3f(-.5, -.5, 0);
    // glVertex3f(0.5, -.5, 0);
    // glVertex3f(0, 0.5, 0);

    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols - 1; j++) {
            Point p1 = particles[i][j]->getPos();
            Point p2 = particles[i][j + 1]->getPos();
            Point p3 = particles[i + 1][j]->getPos();
            
            Vector v1 = p2 - p1;
            Vector v2 = p3 - p1;
            Unit normal = -v1.cross(v2);
            
            glNormal3f(normal.x(), normal.y(), normal.z());
            glVertex3f(p1.x(), p1.y(), p1.z());
            glVertex3f(p2.x(), p2.y(), p2.z());
            glVertex3f(p3.x(), p3.y(), p3.z());
            
            Point p4 = particles[i + 1][j + 1]->getPos();
            
            v1 = p4 - p2;
            v2 = p3 - p2;
            normal = -v1.cross(v2);
            
            glNormal3f(normal.x(), normal.y(), normal.z());
            glVertex3f(p2.x(), p2.y(), p2.z());
            glVertex3f(p4.x(), p4.y(), p4.z());
            glVertex3f(p3.x(), p3.y(), p3.z());
        }
    }
    
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // gluLookAt(0, 0, 10.0, 
    //           0, 0, 0.0,  
    //           0.0, 1.0, 0.0); 
    
    //glRotatef(90, 1, 0, 0);
    renderCloth();
    glFlush();
}

void update(int value) {
    cloth->update(0.01);
    
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { 
        exit(0);
    }
    else if (key == 's') { 
        update(0);
    } 
    else if (key == 'r') { 
        cloth = new Cloth(10, 10);
        cloth->initGrid(Point(-0.5, 0.5, 0.0), 0.1);

        glutPostRedisplay();
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(w, h);
    glutCreateWindow("Cloth");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    
    init();
    
    glutMainLoop();
    
    return 0;
}