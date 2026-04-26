#include <GLUT/glut.h>
#include <iostream>
#include "Cloth.h"

Cloth *cloth = nullptr;

int w = 600;
int h = 600;

bool showBall = true;
bool showPlatform = true;
bool curtainMode = false;

void init()
{
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);

    glEnable(GL_COLOR_MATERIAL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    GLfloat ambient[] = {0.35, 0.35, 0.35, 1.0};
    GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat specular[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat light_position[] = {2.0, 3.0, 4.0, 1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    cloth = new Cloth(30, 30);
    cloth->initGrid(Point(-0.9, .8, .1), 0.05);
}

void renderCloth()
{
    Particle ***particles = cloth->getParticles();
    int rows = cloth->getRows();
    int cols = cloth->getCols();

    glColor3f(0.7, 0.3, 0.3);
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < rows - 1; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            Point p1 = particles[i][j]->getPos();
            Point p2 = particles[i][j + 1]->getPos();
            Point p3 = particles[i + 1][j]->getPos();

            Vector v1 = p2 - p1;
            Vector v2 = p3 - p1;
            Unit normal = Unit(v1.cross(v2));

            glNormal3f(normal.x(), normal.y(), normal.z());
            glVertex3f(p1.x(), p1.y(), p1.z());
            glVertex3f(p2.x(), p2.y(), p2.z());
            glVertex3f(p3.x(), p3.y(), p3.z());

            Point p4 = particles[i + 1][j + 1]->getPos();

            v1 = p4 - p2;
            v2 = p3 - p2;
            normal = Unit(v1.cross(v2));

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

    gluLookAt(
        0.0, 0.2, 3.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    glRotatef(25, 1, 0, 0);
    glRotatef(-25, 0, 1, 0);

    if (showPlatform) {
        glPushMatrix();
        glColor3f(0.3, 0.3, 0.3);
        glTranslatef(0.0, -0.8, 0.0);
        glScalef(3.0, 0.03, 3.0);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    if (showBall) {
        glPushMatrix();
        glColor3f(0.0, 0.45, 1.0);
        glTranslatef(0.0, -0.15, 0.0);
        glutSolidSphere(0.25, 40, 40);
        glPopMatrix();
    }

    renderCloth();

    glutSwapBuffers();
}

void update(int value)
{
    for (int i = 0; i < 100; i++)
    {
        cloth->update(0.00015);
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
    {
        exit(0);
    }
    else if (key == 's')
    {
        update(0);
    }
    else if (key == 'r')
    {
        cloth = new Cloth(10, 10);
        cloth->initGrid(Point(-0.5, 0.5, 0.0), 0.1);

        glutPostRedisplay();
    }
    else if (key == 'b')
    {
        showBall = !showBall;
        glutPostRedisplay();
    }
    else if (key == 'p')
    {
        showPlatform = !showPlatform;
        glutPostRedisplay();
    }
    else if (key == 'c')
    {
        curtainMode = !curtainMode;

        delete cloth;
        cloth = new Cloth(20, 25);

        if (curtainMode)
        {
            cloth->initGrid(Point(-0.5, 0.5, 0.0), 0.1); // curtain
        }
        else
        {
            cloth->initGrid(Point(-0.9, 0.6, 0.9), 0.04); // sheet over ball
        }
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(w, h);
    glutCreateWindow("Cloth");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();

    return 0;
}