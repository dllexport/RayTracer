#include "Renderer.h"

#include <omp.h>

#include "HittableList.h"
#include "Dielectric.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Sphere.h"
#include "Camera.h"
#include "Random.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <spdlog/spdlog.h>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>

void Renderer::render()
{
    srand(time(nullptr));
    auto world = RandomScene();

    Eigen::Vector3f camera_position(5, 5, 3);
    Eigen::Vector3f look_at(0, 0, 2);

    Camera camera(camera_position, look_at, 60, float(width) / float(height));

    auto image_buffer = std::make_unique<float[]>(width * height * 3);
    auto image_buffer_uint8 = std::make_unique<uint8_t[]>(width * height * 3);
    memset(image_buffer.get(), 0, width * height * 3 * sizeof(float));
    memset(image_buffer_uint8.get(), 0, width * height * 3 * sizeof(uint8_t));

#pragma omp parallel for
    for (int row = height - 1; row >= 0; row--)
    {
#pragma omp parallel for
        for (int col = 0; col < width; col++)
        {
            auto idx = (height - 1 - row) * width * 3 + 3 * col;
            Eigen::Vector3f color = Eigen::Vector3f::Zero();
#pragma omp parallel for
            for (int sps = 0; sps < samples; ++sps)
            {
                float u = (float(col) + randomUnit()) / float(width);
                float v = (float(row) + randomUnit()) / float(height);
                Ray ray = camera.GetRay(u, v);
                auto part_color = tracing(ray, world, 0);
                image_buffer[idx] += part_color.x() / samples;
                image_buffer[idx + 1] += part_color.y() / samples;
                image_buffer[idx + 2] += part_color.z() / samples;
            }

            auto &r = image_buffer[idx];
            auto &g = image_buffer[idx + 1];
            auto &b = image_buffer[idx + 2];

            auto scale = 1.0;
            r = std::powf(scale * r, 1 / 2.2);
            g = std::powf(scale * g, 1 / 2.2);
            b = std::powf(scale * b, 1 / 2.2);
            image_buffer_uint8[idx] = r * 255.99;
            image_buffer_uint8[idx + 1] = g * 255.99;
            image_buffer_uint8[idx + 2] = b * 255.99;
        }
    }

    stbi_write_png("stbpng.png", width, height, 3, image_buffer_uint8.get(), width * 3);
}

std::shared_ptr<Hittable> Renderer::RandomScene()
{
    auto list = std::make_shared<HittableList>();
    auto lamberPlane = std::make_shared<Lambertian>(Eigen::Vector3f(0.5, 0.5, 0.5));
    list->Add(std::make_shared<Sphere>(Eigen::Vector3f(0, 0, -1000.0), 1000, lamberPlane));

    int ball_count = 2;

    for (int i = 0; i < ball_count; i++)
    {
        for (int rx = -4; rx < 4; rx++)
        {
            for (int ry = -4; ry < 4; ry++)
            {
                auto random = randomUnit();
                Eigen::Vector3f center(rx + 0.9 * randomUnit(), ry + 0.9 * randomUnit(), std::max(randomUnit(), 0.2f));
                if (random < 0.5)
                {
                    auto metal = std::make_shared<Metal>(Eigen::Vector3f(randomUnit(), randomUnit(), randomUnit()), randomUnit());
                    list->Add(std::make_shared<Sphere>(center, 0.2, metal));
                }
				else if (random >= 0.5 && random < 0.8)
                {
                    auto lamber = std::make_shared<Lambertian>(Eigen::Vector3f(randomUnit(), randomUnit(), randomUnit()));
                    list->Add(std::make_shared<Sphere>(center, 0.2, lamber));
                } else {
					auto dielectric = std::make_shared<Dielectric>(Eigen::Vector3f(randomUnit(), randomUnit(), randomUnit()), 1 + randomUnit());
					list->Add(std::make_shared<Sphere>(center, 0.2, dielectric));
                }
            }
        }
    }

    return list;
}

Eigen::Vector3f Renderer::tracing(Ray &ray, std::shared_ptr<Hittable> world, int depth)
{
    HitRecord record;
    if (world->Hit(ray, 0.001f, std::numeric_limits<float>::max(), record))
    {
        Ray scattered;
        Eigen::Vector3f attenuation;
        if (depth < max_depth && record.material->scatter(ray, record, attenuation, scattered))
        {
            auto next_result = tracing(scattered, world, depth + 1);
            auto mul = Eigen::Vector3f(attenuation.x() * next_result.x(), attenuation.y() * next_result.y(), attenuation.z() * next_result.z());
            return mul;
        }
        else
        {
            return Eigen::Vector3f(0, 0, 0);
        }
    }
    else
    {
        float t = 0.5f * (ray.Direction().z() + 1.0f);
        Eigen::Vector3f ret = Eigen::Vector3f(1.0f, 1.0f, 1.0f) * (1.0f - t) + Eigen::Vector3f(0.5f, 0.7f, 1.0f) * t;
        return ret;
    }
}
