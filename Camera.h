#pragma once

#include <Eigen/Dense>

#include "Ray.h"

class Camera
{
public:
    Camera(Eigen::Vector3f position, Eigen::Vector3f target, float fov, float aspect_ratio, float apart, float focal_dist, float time_from, float time_to);

    Ray GetRay(float u, float v);

    Eigen::Vector3f position;
    Eigen::Vector3f target;
    Eigen::Vector3f bottom_left_position;
    Eigen::Vector3f horizontal_direction;
    Eigen::Vector3f vertical_direction;

    // in degrees
    float fov;
    float aspect_ratio;
    float apart;
    float focal_dist;

    Eigen::Vector3f x;
    Eigen::Vector3f y;
    Eigen::Vector3f z;

    float time_from;
    float time_to;

private:
    void update();
};