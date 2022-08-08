#include "MovingSphere.h"

bool MovingSphere::Hit(Ray ray, float t_min, float t_max, HitRecord &record) {
    Eigen::Vector3f center = Center(ray.SendTime());
    Eigen::Vector3f oc = ray.Origin() - center;
    float a = ray.Direction().transpose() * ray.Direction();
    float b = 2.0 * oc.transpose() * ray.Direction();
    float c = oc.dot(oc) - radius * radius;

    auto direction = ray.Direction();
    // spdlog::info("ray: [{},{},{}]", direction.x(), direction.y(), direction.z());

    auto discreminant = b * b - 4 * a * c;
    if (discreminant < 0)
    {
        return false;
    }

    auto root_1 = (-b - sqrtf(discreminant)) / (2 * a);
    if (root_1 > t_min && root_1 < t_max)
    {
        record.t = root_1;
        record.position = ray.PointAt(root_1);
        record.normal = (record.position - center) / radius;
        record.material = material;
        return true;
    }

    auto root_2 = (-b + sqrtf(discreminant)) / (2 * a);
    if (root_2 > t_min && root_2 < t_max)
    {
        record.t = root_2;
        record.position = ray.PointAt(root_2);
        record.normal = (record.position - center) / radius;
        record.material = material;
        return true;
    }

    return false;
}

Eigen::Vector3f MovingSphere::Center(float time_at) {
    return center_0 + ((time_at - time_0) / (time_1 - time_0)) * (center_1 - center_0);
}
