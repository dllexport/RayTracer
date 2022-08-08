#include "Camera.h"

#include <cmath>
#include <cassert>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "Random.h"

static float radians(float degrees)
{
    return (EIGEN_PI / 180.0) * degrees;
}

static float degrees(float radians)
{
    return radians / (EIGEN_PI / 180.0);
}

Eigen::Vector3f randomInUnitDisk()
{
    while (true)
    {
        auto p = Eigen::Vector3f(randomUnit() - 1, randomUnit() - 1, 0);
        if (float(p.transpose() * p) >= 1)
            continue;
        return p;
    }
}

Camera::Camera(Eigen::Vector3f position, Eigen::Vector3f target, float fov, float aspect_ratio, float apart, float focal_dist, float time_from, float time_to) : position(position),
                                                                                                                                 target(target), fov(fov), aspect_ratio(aspect_ratio), apart(apart), focal_dist(focal_dist), time_from(time_from), time_to(time_to)
{
    update();
}

void Camera::update()
{
    Eigen::Vector3f world_up(0, 0, 1);

    auto theta = radians(fov);
    auto h = tan(theta / 2);

    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    z = position - target;
    z.normalize();

    x = world_up.cross(z);
    x.normalize();

    y = z.cross(x);
    y.normalize();

    horizontal_direction = x * viewport_width * focal_dist;
    vertical_direction = y * viewport_height * focal_dist;

    bottom_left_position = position - horizontal_direction * 0.5f - vertical_direction * 0.5f - z * focal_dist;
}

Ray Camera::GetRay(float u, float v)
{
    assert(u >= 0);
    assert(v >= 0);
    assert(u <= 1.0f);
    assert(u <= 1.0f);

    float lens_radius = apart / 2;
    Eigen::Vector3f rd = lens_radius * randomInUnitDisk();
    Eigen::Vector3f offset = x * rd.x() + y * rd.y();

    Eigen::Vector3f test = bottom_left_position + horizontal_direction * u + vertical_direction * v - position - offset;

    return Ray(position + offset, test, randomBetween(time_from, time_to));
}
