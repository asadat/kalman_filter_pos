#include <thread>
#include <chrono>
#include <iostream>
#include <GL/glut.h>

#include "robot.h"
#include "utility.h"

using namespace std;
using namespace Eigen;

robot::robot():
    p_(-10,-10),
    v_(1,0),
    speed_(1),
    stop_(false),
    speed_rate_(0.01),
    dir_rate_(0.01),
    odom(Vector2f(-10,-10))
{

}

robot::~robot()
{
}

Vector2f robot::get_p()
{
    lock_guard<mutex> lck(state_mutex_);
    return p_;
}

Vector2f robot::get_v()
{
    lock_guard<mutex> lck(state_mutex_);
    return v_;
}

void robot::set_p(const Vector2f & p)
{
    lock_guard<mutex> lck(state_mutex_);
    p_=p;
}

void robot::set_v(const Vector2f & v)
{
    lock_guard<mutex> lck(state_mutex_);
    v_=v.normalized();
}

void robot::run()
{
    thread t(&robot::update, this);
    t.detach();
}

bool robot::is_stopped()
{
    lock_guard<mutex> lck(state_mutex_);
    return stop_;
}

void robot::stop()
{
    lock_guard<mutex> lck(state_mutex_);
    stop_ = true;
}

void robot::update_state(const float &dt)
{
    auto p = get_p();
    auto v = get_v();

    float deg_noise = utility::generate_normal_sample(0, 0.3);
    Matrix2f noisey_dir;
    noisey_dir << cos(deg_noise), sin(deg_noise), -sin(deg_noise), cos(deg_noise);

    float noise_speed = utility::generate_normal_sample(0, 0.5);

    auto noisy_v = noisey_dir*v;
    auto noisy_speed = speed_ + noise_speed;

    p += dt*noisy_speed*noisy_v;

    set_p(p);

    odom.velocity_action(speed_*v, dt);
}

void robot::update()
{
    static auto last_time = chrono::steady_clock::now();

    while(!is_stopped())
    {
       this_thread::sleep_for(chrono::milliseconds(33));

       auto t = chrono::steady_clock::now();
       auto dur = t-last_time;
       update_state(chrono::duration_cast<chrono::milliseconds>(dur).count()*0.001);
       last_time = t;
    }
}


void robot::change_vel(bool l, bool r, bool u, bool d)
{
    float ddir=0;
    if(u) speed_+=speed_rate_;
    if(d) speed_-=speed_rate_;
    if(r) ddir += dir_rate_;
    if(l) ddir -= dir_rate_;

    if(l^r)
    {
        Matrix2f rot;
        rot << cos(ddir), sin(ddir), -sin(ddir), cos(ddir);
        auto v = get_v();
        v = rot*v;
        set_v(v);
    }
}

void robot::draw()
{
    glColor3f(0,0,1);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(p_[0], p_[1]);
    glEnd();


    odom.draw();
}
