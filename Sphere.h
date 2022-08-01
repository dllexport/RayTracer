#pragma once

#include <Eigen/Dense>
#include <memory>

#include "Hittable.h"
#include "Material.h"

class Sphere : public Hittable
{
public:
    Sphere(Eigen::Vector3f center, float radius, std::shared_ptr<Material> material);

    virtual bool Hit(Ray ray, float t_min, float t_max, HitRecord &record) final;

    Eigen::Vector3f center;
    float radius;
    std::shared_ptr<Material> material;
};