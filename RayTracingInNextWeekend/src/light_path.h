#pragma once
#include "vec3.h"
vec3 reflect(const vec3 &v, const vec3 &n);
bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted);
float schlick(float cosine, float ref_idx);
