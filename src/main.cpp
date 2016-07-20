#include <GL/glut.h>
#include "engine.h"

#include <iostream>

void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    engine::get_instance()->draw();
    glutSwapBuffers();
}

void idle_event()
{
    glutPostRedisplay();
}

int main(int argc, char ** argv)
{
    engine::get_instance()->initialize();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize( 640, 480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("kalman_filter");

    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,1.0,0.0);
    glPointSize(5);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);

    glutDisplayFunc(render);
    glutIdleFunc(idle_event);
    glutMainLoop();


    return 0;
}
