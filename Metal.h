#pragma once

#include "Material.h"

class Metal : public Material
{
public:
    Metal(Eigen::Vector3f albedo, float fuzz);

    virtual bool scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered) final;

    Eigen::Vector3f albedo;
    float fuzz;
};
