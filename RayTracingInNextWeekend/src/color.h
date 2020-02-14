#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "material.h"
constexpr float max_float = std::numeric_limits<float>::max();
vec3 color(const ray& ry, hittable& world, int depth);
