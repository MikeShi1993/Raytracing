#pragma once
#include "vec3.h"
#include "camera.h"
#include "hittable_list.h"
#include "random.h"
#include "color.h"
vec3 loop_func(int ele_index, int nx, int ny, int ns, const camera& cam, const hittable_list& world);
