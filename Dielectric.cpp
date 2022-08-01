#include "Dielectric.h"

#include "Hittable.h"
#include "Random.h"

#include <utility>

Eigen::Vector3f refract(const Eigen::Vector3f &uv, const Eigen::Vector3f &n, double etai_over_etat)
{
    auto cos_theta = std::min(float((-uv).transpose() * n), 1.0f);
    Eigen::Vector3f r_out_perp = etai_over_etat * (uv + cos_theta * n);
    Eigen::Vector3f r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.norm() * r_out_perp.norm())) * n;
    return r_out_perp + r_out_parallel;
}

Dielectric::Dielectric(Eigen::Vector3f albedo, float index_of_refraction) : albedo(albedo), index_of_refraction(index_of_refraction) {}

bool Dielectric::scatter(const Ray &in, const HitRecord &record, Eigen::Vector3f &attenuation, Ray &scattered)
{
    attenuation = Eigen::Vector3f(1.0, 1.0, 1.0);
    Eigen::Vector3f hit_point_normal = record.normal;

    double refraction_ratio = 1.0f / index_of_refraction;
    if (float(hit_point_normal.transpose() * in.Direction()) > 0)
    {
        refraction_ratio = index_of_refraction;
    }

    auto unitInDirection = in.Direction();
    unitInDirection.normalize();

    Eigen::Vector3f refracted = refract(unitInDirection, record.normal, refraction_ratio);

    scattered = Ray(record.position, refracted);
    return true;
}
