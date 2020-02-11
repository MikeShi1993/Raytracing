#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <iostream>
#include "vec3.h"
#include "ray.h"
#include "random.h"
#include "hittable.h"
#include "material.h"

using std::cout;
using std::endl;

TEST_CASE("vec3 class")
{
    vec3 v1{1, 2, 3};
    vec3 v2{2, 4, 6};
    vec3 v3{v1};
    vec3 v4{2, 2, 2};
    SUBCASE("vec3 class constructor")
    {
        CHECK(v1.x() == 1);
        CHECK(v1.y() == 2);
        CHECK(v1.z() == 3);
        CHECK(v1.r() == 1);
        CHECK(v1.g() == 2);
        CHECK(v1.b() == 3);
        CHECK(-v1.x() == -1);
        CHECK(-v1.y() == -2);
        CHECK(-v1.z() == -3);
        CHECK(v1.length() == sqrt(14.0f));
        CHECK(v1 != v2);
        CHECK(v1 == v3);
        CHECK(v1 + v2 == vec3(3, 6, 9));
        CHECK(v1 - v2 == -v1);
        CHECK(v1 - v2 == vec3(-1, -2, -3));
        CHECK(v1 * v2 == vec3(2, 8, 18));
        CHECK(v1 * 1 == v1);
        CHECK(2 * v1 == v2);
        CHECK(v1 / v2 == vec3(0.5, 0.5, 0.5));
        CHECK(v2 / 2 == v1);
        CHECK(dot(v1, v2) == 28);
        CHECK(cross(v1, v4) == vec3(-2, 4, -2));
        CHECK(v1 - 1 == vec3(0.0f, 1.0f, 2.0f));
        CHECK(1 - v1 == vec3(0.0f, -1.0f, -2.0f));
    }

    SUBCASE("vec3 arithmetic member functions")
    {
        v1 += v2;
        CHECK(v1 == vec3(3, 6, 9));
        v1 -= v2;
        CHECK(v1 == vec3(1, 2, 3));
        v1 /= vec3(1, 1, 1);
        CHECK(v1 == vec3(1, 2, 3));
        v1 *= vec3(1, 1, 1);
        CHECK(v1 == vec3(1, 2, 3));
        v1 /= 1;
        CHECK(v1 == vec3(1, 2, 3));
        v1 *= 1;
        CHECK(unit_vector(v1) == vec3(1 / sqrt(14.0f), 2 / sqrt(14.0f), 3 / sqrt(14.0f)));
        CHECK(v1 == vec3(1, 2, 3));
        v1.make_unit_vector();
        CHECK(v1 == vec3(1 / sqrt(14.0f), 2 / sqrt(14.0f), 3 / sqrt(14.0f)));
    }

    SUBCASE("ray class")
    {
        vec3 A(1, 2, 3);
        vec3 B(2, 2, 2);
        ray ry(A, B);
        CHECK(ry.point_at_parameter(2) == vec3(5, 6, 7));
        CHECK(ray().point_at_parameter(1) == vec3(0, 0, 0));
    }
}

TEST_CASE("random function")
{
    auto a = random_double();
    auto b = random_double();
    CHECK((a < 1.0 && a >= 0.0));
    CHECK((b < 1.0 && b >= 0.0));
    CHECK(a != b);
}

TEST_CASE("hit_record class")
{
    hit_record hr;
    CHECK(hr.mat_ptr == nullptr);
}