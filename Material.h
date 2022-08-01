#pragma once

#include <Eigen/Dense>

#include "Ray.h"

class HitRecord;

class Material
{
public:
    virtual bool scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered) = 0;
};