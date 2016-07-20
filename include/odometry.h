#pragma once

#include <Eigen/Core>
#include "utility.h"

using namespace Eigen;

class odometry
{
public:
    odometry(const Vector2f &p);
    virtual ~odometry();

    void velocity_action(const Eigen::Vector2f &v, const float &dt);
    Eigen::Vector2f get_pos_estimate() const;
    Eigen::Matrix2f get_pos_covariance() const;

    void draw();

private:

    Eigen::Vector2f p_;
    Eigen::Matrix2f cov_;
    utility::pos2_track track;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};
