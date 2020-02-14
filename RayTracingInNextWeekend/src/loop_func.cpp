#include "loop_func.h"
#include "material.h"
vec3 loop_func(int ele_index, int nx, int ny, int ns, const camera &cam, hittable_list *world_ptr)
{
	vec3 col(0.0f, 0.0f, 0.0f);
	int i = ele_index % nx;
	int j = ny - ele_index / nx - 1;
	for (int s = 0; s != ns; ++s)
	{
		float u = (float(i) + random_double()) / float(nx);
		float v = (float(j) + random_double()) / float(ny);
		ray ry = cam.get_ray(u, v);
		col += color(ry, *world_ptr, 0);
	}
	col /= float(ns);
	col = sqrt(col);
	return col;
}
