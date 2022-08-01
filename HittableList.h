#pragma once

#include <Eigen/Dense>
#include <vector>
#include <memory>

#include "Hittable.h"

#include "Ray.h"

class HittableList : public Hittable
{
public:
    virtual bool Hit(Ray ray, float t_min, float t_max, HitRecord &record) final;

    void Add(std::shared_ptr<Hittable> object);

    void Clear();

private:
    std::vector<std::shared_ptr<Hittable>> list;
};