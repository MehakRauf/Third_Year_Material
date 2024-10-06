#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;
float deg = 0.0;
void tooth0()
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(0, 0);
    glVertex2f(0.2, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.6, 0.8);
    glVertex2f(0.2, 0.8);
    glVertex2f(0, 1.0);
    glEnd();
}
void tooth1(double r)
{
    double rad = 6 * 3.1416 / 180.0, sin6 = r * sin(rad), cos6 = r * cos(rad);
    glPushMatrix();
    glTranslatef(cos6, -sin6, 0.0);
    glScalef(2.0 * sin6, 2.0 * sin6, 1.0);
    tooth0();
    glPopMatrix();
}
void gear(double r)
{
    glPushMatrix();
    for (int i = 0; i <= 30; ++i)
    {
        tooth1(r);
        glRotatef(12.0, 0, 0, 1.0);
    }
    glPopMatrix();
}
void move()
{
    float speed = 0.000001;
    static int oldTime = clock(), newTime;
    newTime = clock();
    deg += (newTime - oldTime) * speed;
    oldTime = newTime;
    glutPostRedisplay();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1);
    glColor3f(0.0f, 1.0f, 0.0f);
    move();
    glRotatef(deg, 0.0, 0.0, 1.0);
    gear(10.0);
    glFlush();
}
void reshape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-20, 20, -20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Gear Wheel");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}