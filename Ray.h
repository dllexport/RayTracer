#pragma once

#include <Eigen/Dense>

class Ray
{
public:
    Ray();

    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float time = 0.0f);

    Eigen::Vector3f PointAt(float t);

    Eigen::Vector3f Origin()
    {
        return origin;
    }

    Eigen::Vector3f Direction() const
    {
        return direction;
    }

    float SendTime() const {
        return send_time;
    }

private:
    Eigen::Vector3f origin = {};
    Eigen::Vector3f direction = {};
    float send_time = 0.0f;
};