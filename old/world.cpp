#include "world.h"

bool World::hit(const Ray &r, Interval r_t, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = r_t.max;

    for (const auto &object : objects)
    {
        // execute to intersection test about current primitive
        if (object->hit(r, Interval(r_t.min, closest_so_far), temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
