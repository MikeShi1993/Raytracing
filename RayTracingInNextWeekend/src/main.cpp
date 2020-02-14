#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8

#include <algorithm>
#include <array>
#include <chrono>
#include <execution>
#include <limits>

#include <iostream>
using std::cout;
using std::endl;

#include <functional>
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
#include "random_scene.h"

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

    vector<std::unique_ptr<int>> test;
    test.push_back(std::make_unique<int>(10));
    vector<std::unique_ptr<int>> test2(std::move(test));

    auto start = std::chrono::system_clock::now();
    hittable_list world(random_scene());
    // float R = cos(PI / 4);
    vec3 lookfrom(13.0f, 2.0f, 3.0f);
    vec3 lookat(0.0f, 0.0f, 0.0f);
    float dist_to_focus = 10.0f;
    float aperture = 0.1f;
    camera cam(lookfrom, lookat, vec3(0.0f, 1.0f, 0.0f), 20, float(nx) / float(ny), aperture, dist_to_focus);
    unique_ptr<uint8_t[]> pixels(new uint8_t[nx * ny * channel_num]);
    if (seq)
    {
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
                pixels[index++] = ir;
                pixels[index++] = ig;
                pixels[index++] = ib;
            }
            if (j % 10 == 0)
                cout << double((ny - j) / ny) << "\r";
        }
    }
    else
    {
        using std::placeholders::_1;
        vector<int> ind(nx * ny);
        vector<vec3> ret(nx * ny);
        std::iota(ind.begin(), ind.end(), 0);
        auto loop_func_bind = std::bind(loop_func, _1, nx, ny, ns, cam, &world);
        std::transform(std::execution::par_unseq, ind.begin(), ind.end(), ret.begin(), loop_func_bind);
        int index = 0;
        for (auto &col : ret)
        {
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            pixels[index++] = ir;
            pixels[index++] = ig;
            pixels[index++] = ib;
        }
    }
    stbi_write_jpg("ray_tracing.jpg", nx, ny, channel_num, pixels.get(), quality);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    cout << "time usage: " << diff.count() << "s" << endl;
    return 0;
}
