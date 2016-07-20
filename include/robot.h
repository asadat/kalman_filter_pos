#pragma once

#include <Eigen/Eigen>
#include <mutex>

#include "odometry.h"

class robot
{
public:
    robot();
    ~robot();

    void run();

    void stop();
    void change_vel(bool l, bool r, bool u, bool d);

    Eigen::Vector2f get_p();

    void draw();

private:

    Eigen::Vector2f get_v();

    void update();
    void set_p(const Eigen::Vector2f &);
    void set_v(const Eigen::Vector2f &);

    void update_state(const float &dt);
    bool is_stopped();

    odometry odom;

    std::mutex state_mutex_;

    Eigen::Vector2f p_;
    Eigen::Vector2f v_;
    float speed_;

    bool stop_;

    const float speed_rate_;
    const float dir_rate_;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
