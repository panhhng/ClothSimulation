#include <GLUT/glut.h>
#include <iostream>
#include "Cloth.h"

Cloth *cloth = nullptr;

int w = 600;
int h = 600;

bool isCurtain = false;

Cloth::SphereCollider sphere = {
    true,
    Point(0.0, -0.15, 0.0),
    0.25,
    0.02,
    0.05};

Cloth::PlatformCollider platform = {
    true,
    -0.8,
    0.02,
    0.05};

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

    cloth = new Cloth(25, 25);
    cloth->initGrid(Point(-0.9, .8, .1), 0.1);
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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0.2, 3.0,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    glRotatef(25, 1, 0, 0);
    glRotatef(-25, 0, 1, 0);

    if (isCurtain)
    {
        GLfloat light_position[] = {2.0, 1.0, -2.0, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }
    else
    {
        GLfloat light_position[] = {2.0, 3.0, 4.0, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    }

    if (platform.enabled)
    {
        glPushMatrix();
        glColor3f(0.3, 0.3, 0.3);
        glTranslatef(0.0, platform.y, 0.0);
        glScalef(5.0, 0.03, 5.0);
        glutSolidCube(1.0);
        glPopMatrix();
    }

    if (sphere.enabled)
    {
        glPushMatrix();
        glColor3f(0.0, 0.45, 1.0);
        glTranslatef(sphere.center.x(), sphere.center.y(), sphere.center.z());
        glutSolidSphere(sphere.radius, 40, 40);
        glPopMatrix();
    }

    renderCloth();

    glutSwapBuffers();
}

void update(int value)
{
    for (int i = 0; i < 100; i++)
    {
        cloth->update(0.00015, sphere, platform);
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
        delete cloth;

        isCurtain = false;
        sphere.enabled = true;
        platform.enabled = true;

        cloth = new Cloth(25, 25);
        cloth->initGrid(Point(-0.9, .8, .1), 0.1);

        glutPostRedisplay();
    }
    else if (key == 'b')
    {
        sphere.enabled = !sphere.enabled;
        glutPostRedisplay();
    }
    else if (key == 'p')
    {
        platform.enabled = !platform.enabled;
        glutPostRedisplay();
    }
    else if (key == 'c')
    {
        delete cloth;

        isCurtain = !isCurtain;

        if (isCurtain)
        {
            sphere.enabled = false;
            platform.enabled = false;

            cloth = new Cloth(10, 10);
            cloth->initGrid(Point(-0.5, 0.5, 0.0), 0.1);

            Particle ***p = cloth->getParticles();
            for (int j = 0; j < cloth->getCols(); j++)
            {
                p[0][j]->setFixed(true);
            }
        }
        else
        {
            sphere.enabled = true;
            platform.enabled = true;

            cloth = new Cloth(25, 25);
            cloth->initGrid(Point(-0.9, .8, .1), 0.1);
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