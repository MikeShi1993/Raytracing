#pragma once
#include "ray.h"
#include "random.h"
constexpr float PI = 3.1415927;

inline vec3 random_in_unit_disk()
{
    vec3 p;
    do
    {
        p = 2.0 * vec3(random_double(), random_double(), 0.0f) - vec3(1.0f, 1.0f, 0.0f);
    } while (dot(p, p) >= 1.0);
    return p;
}

class camera
{
public:
    camera() : origin(0.0, 0.0, 0.0), lower_left_corner(-2.0, -1.0, -1.0), horizontal(4.0, 0.0, 0.0), vertical(0.0, 2.0, 0.0) {}
    ray get_ray(float s, float t) const;
    camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist);

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;
};

inline camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
{
    lens_radius = aperture / 2;
    float theta = vfov * PI / 180.0f;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    origin = lookfrom;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);
    lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - w * focus_dist;
    horizontal = 2 * half_width * focus_dist * u;
    vertical = 2 * half_height * focus_dist * v;
}

inline ray camera::get_ray(float s, float t) const
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}