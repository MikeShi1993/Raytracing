#include "random_scene.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "sphere.h"

hittable_list random_scene()
{
    hittable_list world;
    world.push_back(sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<lambertian>(vec3(0.5f, 0.5f, 0.5f))));
    for (int a = -11; a < 11; ++a)
    {
        for (int b = -11; b < 11; ++b)
        {
            float choose_mat = random_double();
            vec3 center(a + 0.9f * random_double(), 0.2f, b + 0.9f * random_double());
            if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9)
            {
                if (choose_mat < 0.8)
                {
                    world.push_back(sphere(center, 0.2f,
                                           std::make_shared<lambertian>(vec3(random_double() * random_double(),
                                                                             random_double() * random_double(),
                                                                             random_double() * random_double()))));
                }
                else if (choose_mat < 0.95)
                {
                    world.push_back(sphere(center, 0.2f,
                                           std::make_shared<metal>(vec3(0.5f * (1.0f + random_double()),
                                                                        0.5f * (1.0f + random_double()),
                                                                        0.5f * (1.0f + random_double())),
                                                                   0.5f * float(random_double()))));
                }
                else
                {
                    world.push_back(sphere(center, 0.2f, std::make_shared<dielectric>(1.5f)));
                }
            }
        }
    }
    world.push_back(sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, std::make_shared<dielectric>(1.5f)));
    world.push_back(sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<lambertian>(vec3(0.4f, 0.2f, 0.1f))));
    world.push_back(sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, std::make_shared<metal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));
    return std::move(world);
}
