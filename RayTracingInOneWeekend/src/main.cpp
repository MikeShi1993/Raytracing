#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8

#include <algorithm>
#include <array>
#include <chrono>
#include <limits>

#include <iostream>
using std::cout;
using std::endl;

#include <memory>
#include <numeric>
using std::shared_ptr;
using std::unique_ptr;

#include <vector>
using std::vector;

#include "camera.h"
#include "ray.h"
#include "random.h"
#include "vec3.h"
#include "sphere.h"
#include "hittable_list.h"
#include "stb_image_write.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "color.h"
#include "loop_func.h"

int main()
{
    constexpr int channel_num = 3;
    constexpr int quality = 100;
    constexpr int nx = 2000;
    constexpr int ny = 1000;
    constexpr int ns = 100;
    constexpr bool seq = true;

    // constexpr int nx = 200;
    // constexpr int ny = 100;
    // constexpr int ns = 50;

    auto start = std::chrono::system_clock::now();

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);

    hittable_list world;
    float R = cos(PI / 4);
    world.push_back(sphere(vec3(-R, 0.0f, -1.0f), R, std::make_shared<lambertian>(vec3(0.0f, 0.0f, 1.0f))));
    world.push_back(sphere(vec3(R, 0.0f, -1.0f), R, std::make_shared<lambertian>(vec3(1.0f, 0.0f, 0.0f))));

    // world.push_back(sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, std::make_shared<lambertian>(vec3(0.1f, 0.2f, 0.5f))));
    // world.push_back(sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, std::make_shared<lambertian>(vec3(0.8f, 0.8f, 0.0f))));
    // world.push_back(sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<metal>(vec3(0.8f, 0.6f, 0.2f), 0.3f)));
    // world.push_back(sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, std::make_shared<dielectric>(1.5f)));
    // world.push_back(sphere(vec3(-1.0f, 0.0f, -1.0f), -0.45f, std::make_shared<dielectric>(1.5f)));

    camera cam(90.0f, float(nx) / float(ny));
    unique_ptr<uint8_t[]> pixels(new uint8_t[nx * ny * channel_num]);
    if (seq) {
        int index = 0;
        for (int j = ny - 1; j >= 0; --j)
        {
            for (int i = 0; i != nx; ++i)
            {
                vec3 col(0.0f, 0.0f, 0.0f);
                for (int s = 0; s != ns; ++s)
                {
                    float u = (float(i) + random_double()) / float(nx);
                    float v = (float(j) + random_double()) / float(ny);
                    ray ry = cam.get_ray(u, v);
                    col += color(ry, world, 0);
                }
                col /= float(ns);
                col = sqrt(col);
                int ir = int(255.99 * col[0]);
                int ig = int(255.99 * col[1]);
                int ib = int(255.99 * col[2]);
                // int pos = ((ny - j - 1) * nx + i) * 3;
                // pixels[pos] = ir;
                // pixels[pos + 1] = ig;
                // pixels[pos + 2] = ib;
                pixels[index++] = ir;
                pixels[index++] = ig;
                pixels[index++] = ib;
            }
        }
    }
    else
    {
        vector<int> index(nx * ny);
    	std::iota(index.begin(), index.end(), 0);
    }
    //stbi_write_jpg("ray_tracing.jpg", nx, ny, channel_num, pixels.get(), quality);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "time usage: " << diff.count() << "s" << endl;
    return 0;
}
