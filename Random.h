#pragma once

#include <Eigen/Dense>

inline Eigen::Vector3f RandomInUnitSphere()
{
    Eigen::Vector3f result = Eigen::Vector3f::Random();
    result.normalize();
    return result;
}

inline float randomUnit()
{
    // Returns a random real in [0,1).
    return float(rand() / (RAND_MAX + 1.0));
}
