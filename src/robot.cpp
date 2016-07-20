#include <robot.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;
using namespace Eigen;

robot::robot(): p_(0,0),
    v_(5,5),
    stop_(false)
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
    v_=v;
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
    std::cout << "dt: " << dt << std::endl;

    auto p = get_p();
    auto v = get_v();

    p += dt*v;

    set_p(p);
}

void robot::update()
{
    static auto last_time = chrono::steady_clock::now();

    while(!is_stopped())
    {
       this_thread::sleep_for(chrono::milliseconds(100));

       auto t = chrono::steady_clock::now();
       auto dur = t-last_time;
       update_state(chrono::duration_cast<chrono::milliseconds>(dur).count()*0.001);
       last_time = t;
    }
}

