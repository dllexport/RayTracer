#include "Ray.h"
Ray::Ray()
{
    this->origin = Eigen::Vector3f::Zero();
    this->direction = Eigen::Vector3f::Zero();
}

Ray::Ray(Eigen::Vector3f origin, Eigen::Vector3f direction, float time)
{
    this->direction = direction;
    this->direction.normalize();
    this->origin = origin;
    this->send_time = time;
}

Eigen::Vector3f Ray::PointAt(float t)
{
    return origin + t * direction;
}
