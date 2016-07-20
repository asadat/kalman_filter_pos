#include <GL/glut.h>
#include <iostream>

#include "odometry.h"

using namespace Eigen;

odometry::odometry(const Vector2f &p):
    p_(p)
{
    cov_<< 1,0,0,1;

    std::cout << "domonetry initialized at " << p_ << std::endl;
}

odometry::~odometry()
{

}

void odometry::velocity_action(const Vector2f &v, const float &dt)
{
    track.insert(track.begin(), p_);
    if(track.size() > 100)
        track.pop_back();

    p_ += dt*v;
}

Matrix2f odometry::get_pos_covariance() const
{
    return cov_;
}

Vector2f odometry::get_pos_estimate() const
{
    return p_;
}

void odometry::draw()
{
    glColor3f(1,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(p_[0], p_[1]);
    glEnd();

    utility::draw_track(track, Vector3f(1,0,0));
}
