#pragma once

#include <Eigen/Dense>
#include <random>

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

inline float randomBetween(float from, float to)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_real_distribution<float> dist(from, to);
    return dist(rng);
}
