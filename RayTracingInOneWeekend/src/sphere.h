#pragma once
#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() = default;
    sphere(const vec3 &cen, float r) : sphere(cen, r, nullptr) {}
    sphere(const vec3 &cen, float r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {}
    virtual bool hit(const ray &ry, float t_min, float t_max, hit_record &rec) const override;

protected:
    vec3 center;
    float radius;
    std::shared_ptr<material> mat_ptr;
};

bool sphere::hit(const ray &ry, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = ry.origin() - center;
    float a = dot(ry.direction(), ry.direction());
    float b = 2 * dot(ry.direction(), oc);
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant > 0.0f)
    {
        float temp = (-b - sqrt(discriminant)) / (2.0f * a);
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = ry.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / (2.0f * a);
        // temp = (-b + sqrt(discriminant)) / (1.0f * a);
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = ry.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}