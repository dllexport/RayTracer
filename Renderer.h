#pragma once

#include <Eigen/Dense>
#include <memory>
#include "Hittable.h"

class Renderer
{
public:
    void render();

private:
    const int width = 800;
    const int height = 600;
    const int max_depth = 3;
    const int samples = 5;

    std::shared_ptr<Hittable> RandomScene();

    Eigen::Vector3f tracing(Ray &ray, std::shared_ptr<Hittable> world, int depth);
};