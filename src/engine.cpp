#include "engine.h"
#include <GL/glut.h>

using namespace std;

shared_ptr<engine> engine::instance_=nullptr;

engine::engine():robot_()
{

}

engine::~engine()
{
    robot_.stop();
}

void engine::initialize()
{
    robot_.run();
}

void engine::draw()
{
    auto p = robot_.get_p();

    glColor3f(0,0,1);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(p[0], p[1]);
    glEnd();
}
