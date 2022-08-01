#pragma once

#include <Eigen/Dense>
#include <memory>
#include "Hittable.h"

class Renderer
{
public:
    void render();
    std::shared_ptr<Hittable> RandomScene();

private:
    const int width = 1920;
    const int height = 1080;
    const int max_depth = 5;
    const int samples = 1;

    Eigen::Vector3f tracing(Ray &ray, std::shared_ptr<Hittable> world, int depth);
};