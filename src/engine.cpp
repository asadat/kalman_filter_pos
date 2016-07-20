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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0,1,0);
    glBegin(GL_QUADS);
    glVertex3f(-1, 1, 0);
    glVertex3f( 1, 1, 0);
    glVertex3f( 1,-1, 0);
    glVertex3f(-1,-1, 0);
    glEnd();
}

void engine::mouse_click(const int &x, const int &y)
{
    robot_.set_goal(x,y);
}

void engine::keyboard_event(std::map<unsigned char, bool>& keys_pressed)
{
    robot_.change_vel(keys_pressed['h'], keys_pressed['k'], keys_pressed['u'], keys_pressed['j']);
}
