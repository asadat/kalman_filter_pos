#pragma once

#include <random>
#include <GL/glut.h>
#include <Eigen/Core>
#include <vector>

class utility
{
public:

typedef std::vector<Eigen::Vector2f> pos2_track;

static float generate_normal_sample(const float &m, const float &s)
{
    static std::default_random_engine generator;

    std::normal_distribution<float> distribution(m, s);

    return distribution(generator);
}

static void draw_track(const pos2_track& track,
                const Eigen::Vector3f &color=Eigen::Vector3f(0,0,0),
                const float &point_size = 2.0)
{
    if(track.empty()) return;

    float d_alpha = 1.0/track.size();
    float alpha = 1.0;

    glPointSize(point_size);

    glBegin(GL_POINTS);
    for(auto v: track)
    {
        alpha -= d_alpha;
        glColor4f(color[0],color[1],color[2],alpha);
        glVertex3f(v[0], v[1], 0);
    }
    glEnd();
}
};
