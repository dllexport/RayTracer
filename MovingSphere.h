#pragma once

#include "Hittable.h"
#include "Material.h"

class MovingSphere : public Hittable {
public:
    MovingSphere(Eigen::Vector3f center_0, Eigen::Vector3f center_1, float time_0, float time_1, float radius, std::shared_ptr<Material> material)
    : center_0(center_0), center_1(center_1), time_0(time_0), time_1(time_1), radius(radius), material(material)
    {};

    virtual bool Hit(Ray ray, float t_min, float t_max, HitRecord &record) final;

    Eigen::Vector3f Center(float time_at);

    Eigen::Vector3f center_0;
    Eigen::Vector3f center_1;
    float time_0;
    float time_1;
    float radius;
    std::shared_ptr<Material> material;
};