#include "hittable_list.h"

bool hittable_list::hit(const ray &ry, float t_min, float t_max, hit_record &rec) const
{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = t_max;
    for (size_t i = 0; i != list.size(); ++i)
    {
        if (list[i]->hit(ry, t_min, closest_so_far, temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}
