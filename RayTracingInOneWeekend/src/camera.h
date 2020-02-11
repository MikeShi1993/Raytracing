#pragma once
#include "ray.h"

constexpr float PI = 3.1415927;

class camera
{
public:
    camera() : origin(0.0, 0.0, 0.0), lower_left_corner(-2.0, -1.0, -1.0), horizontal(4.0, 0.0, 0.0), vertical(0.0, 2.0, 0.0) {}
    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }
    camera(float vfov, float aspect);

private:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

inline camera::camera(float vfov, float aspect)
{
    float theta = vfov * PI / 180.0f;
    float half_height = tan(theta / 2);
    float half_width = aspect * half_height;
    lower_left_corner = vec3(-half_width, -half_height, -1.0f);
    horizontal = vec3(2 * half_width, 0.0f, 0.0f);
    vertical = vec3(0.0f, 2 * half_height, 0.0f);
    origin = vec3(0.0f, 0.0f, 0.0f);
}
