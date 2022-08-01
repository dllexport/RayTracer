#include "Camera.h"

#include <cmath>
#include <cassert>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

static float radians(float degrees)
{
    return (EIGEN_PI / 180.0) * degrees;
}

static float degrees(float radians)
{
    return radians / (EIGEN_PI / 180.0);
}

Camera::Camera(Eigen::Vector3f position, Eigen::Vector3f target, float fov, float aspect_ratio) : position(position),
                                                                                                  target(target), fov(fov), aspect_ratio(aspect_ratio)
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

    auto half_height = viewport_height / 2.0;
    auto half_width = viewport_width / 2.0;

    bottom_left_position = position - half_height * y - half_width * x - 1 * z;
    Eigen::Vector3f top_left_position = position + half_height * y - half_width * x - 1 * z;
    Eigen::Vector3f top_right_position = position + half_height * y + half_width * x - 1 * z;
    Eigen::Vector3f bottom_right_position = position - half_height * y + half_width * x - 1 * z;

    spdlog::info("bottom_left_position: {},{},{}", bottom_left_position.x(), bottom_left_position.y(), bottom_left_position.z());
    spdlog::info("top_left_position: {},{},{}", top_left_position.x(), top_left_position.y(), top_left_position.z());
    spdlog::info("top_right_position: {},{},{}", top_right_position.x(), top_right_position.y(), top_right_position.z());
    spdlog::info("bottom_right_position: {},{},{}", bottom_right_position.x(), bottom_right_position.y(), bottom_right_position.z());
    spdlog::info("x: {},{},{}", x.x(), x.y(), x.z());
    spdlog::info("y: {},{},{}", y.x(), y.y(), y.z());
    spdlog::info("z: {},{},{}", z.x(), z.y(), z.z());

    Eigen::Vector3f xvec = x + position;
    Eigen::Vector3f yvec = y + position;
    Eigen::Vector3f zvec = z + position;
    spdlog::info("camera axe x : [{},{},{}]", xvec.x(), xvec.y(), xvec.z());
    spdlog::info("camera axe y: [{},{},{}]", yvec.x(), yvec.y(), yvec.z());
    spdlog::info("camera axe z: [{},{},{}]", zvec.x(), zvec.y(), zvec.z());

    vertical_direction = y * viewport_height;
    horizontal_direction = x * viewport_width;
}

Ray Camera::GetRay(float u, float v)
{
    assert(u >= 0);
    assert(v >= 0);
    assert(u <= 1.0f);
    assert(u <= 1.0f);

    Eigen::Vector3f test = bottom_left_position + horizontal_direction * u + vertical_direction * v - position;

    return Ray(position, test);
}
