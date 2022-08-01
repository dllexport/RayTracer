#include "HittableList.h"

bool HittableList::Hit(Ray ray, float t_min, float t_max, HitRecord &record)
{
    HitRecord result;
    bool hitted = false;
    float nearest_distance = std::numeric_limits<float>::max();

    for (auto &object : list)
    {
        if (object->Hit(ray, t_min, nearest_distance, result))
        {
            hitted = true;
            nearest_distance = result.t;
            record = result;
        }
    }

    return hitted;
}

void HittableList::Add(std::shared_ptr<Hittable> object)
{
    list.push_back(object);
}

void HittableList::Clear()
{
    std::vector<std::shared_ptr<Hittable>>().swap(list);
}