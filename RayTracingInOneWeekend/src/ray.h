#pragma once
#include "vec3.h"
class ray
{
public:
    ray() = default;
    ray(const vec3 &lhs, const vec3 &rhs) : A(lhs), B(rhs) {}
    vec3 origin() const { return A; }
    vec3 direction() const { return B; }
    vec3 point_at_parameter(float t) const { return A + t * B; }

private:
    vec3 A;
    vec3 B;
};
