#include "Lambertian.h"

#include "Hittable.h"
#include "Random.h"

Lambertian::Lambertian(Eigen::Vector3f albedo) : albedo(albedo) {}

bool Lambertian::scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered)
{
    Eigen::Vector3f target = record.position + record.normal + RandomInUnitSphere();
    scattered = Ray(record.position, target - record.position, in.SendTime());
    attenuation = 0.5 * albedo;
    return true;
}
