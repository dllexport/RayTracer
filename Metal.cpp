#include "Metal.h"

#include "Hittable.h"
#include "Random.h"

Metal::Metal(Eigen::Vector3f albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}

bool Metal::scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered)
{
    auto ray = in;
    Eigen::Vector3f reflected_direction = ray.Direction() - record.normal * (ray.Direction().transpose() * record.normal) * 2.0f;

    scattered = Ray(record.position, reflected_direction + RandomInUnitSphere() * fuzz, in.SendTime());
    attenuation = albedo;
    return true;
}
