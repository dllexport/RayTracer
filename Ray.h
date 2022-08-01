#pragma once

#include <Eigen/Dense>

class Ray
{
public:
    Ray();

    Ray(Eigen::Vector3f origin, Eigen::Vector3f direction);

    Eigen::Vector3f PointAt(float t);

    Eigen::Vector3f Origin()
    {
        return origin;
    }

    Eigen::Vector3f Direction() const
    {
        return direction;
    }

private:
    Eigen::Vector3f origin = {};
    Eigen::Vector3f direction = {};
};