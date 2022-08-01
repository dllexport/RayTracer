#pragma once

#include <Eigen/Dense>
#include <memory>

#include "Ray.h"
#include "Material.h"

class HitRecord
{
public:
    float t;
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
    std::shared_ptr<Material> material;
};

class Hittable
{
public:
    virtual bool Hit(Ray ray, float t_min, float t_max, HitRecord &record) = 0;
};