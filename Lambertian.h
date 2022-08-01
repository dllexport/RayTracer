#pragma once

#include "Material.h"

class Lambertian : public Material
{
public:
    Lambertian(Eigen::Vector3f albedo);

    virtual bool scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered) final;

    Eigen::Vector3f albedo;
};
