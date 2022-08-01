#pragma once

#include "Material.h"

class Dielectric : public Material
{
public:
    Dielectric(Eigen::Vector3f albedo, float index_of_refraction);

    virtual bool scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered) final;

    Eigen::Vector3f albedo;
    float index_of_refraction;
};
