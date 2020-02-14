#pragma once
#include <iostream>
#include <cmath>
#include <stdlib.h>

class vec3;
std::istream &operator>>(std::istream &is, vec3 &vec);
std::ostream &operator<<(std::ostream &os, vec3 &vec);

bool operator==(const vec3 &lhs, const vec3 &rhs);
bool operator!=(const vec3 &lhs, const vec3 &rhs);
vec3 operator+(const vec3 &lhs, const vec3 &rhs);
vec3 operator+(const vec3 &lhs, const float t);
vec3 operator+(const float t, const vec3 &rhs);
vec3 operator-(const vec3 &lhs, const vec3 &rhs);
vec3 operator-(float t, const vec3 &rhs);
vec3 operator-(const vec3 &lhs, float t);
vec3 operator*(const vec3 &lhs, const vec3 &rhs);
vec3 operator*(float t, const vec3 &rhs);
vec3 operator*(const vec3 &lhs, float t);
vec3 operator/(const vec3 &lhs, const vec3 &rhs);
vec3 operator/(const vec3 &lhs, float t);

float dot(const vec3 &lhs, const vec3 &rhs);
vec3 cross(const vec3 &lhs, const vec3 &rhs);
vec3 sqrt(const vec3 &rhs);

vec3 unit_vector(vec3 v);

class vec3
{
    friend std::istream &operator>>(std::istream &is, vec3 &vec);
    friend std::ostream &operator<<(std::ostream &os, vec3 &vec);
    friend bool operator==(const vec3 &lhs, const vec3 &rhs);
    friend bool operator!=(const vec3 &lhs, const vec3 &rhs);
    friend vec3 operator+(const vec3 &lhs, const vec3 &rhs);
    friend vec3 operator+(const vec3 &lhs, const float t);
    friend vec3 operator+(const float t, const vec3 &rhs);
    friend vec3 operator-(const vec3 &lhs, const vec3 &rhs);
    friend vec3 operator-(float t, const vec3 &rhs);
    friend vec3 operator-(const vec3 &lhs, float t);
    friend vec3 operator*(const vec3 &lhs, const vec3 &rhs);
    friend vec3 operator*(float t, const vec3 &rhs);
    friend vec3 operator*(const vec3 &lhs, float t);
    friend vec3 operator/(const vec3 &lhs, const vec3 &rhs);
    friend vec3 operator/(const vec3 &lhs, float t);

    friend float dot(const vec3 &lhs, const vec3 &rhs);
    friend vec3 cross(const vec3 &lhs, const vec3 &rhs);
    friend vec3 sqrt(const vec3 &rhs);

    friend vec3 unit_vector(vec3 v);

public:
    vec3() : vec3(0.0f, 0.0f, 0.0f){};
    vec3(float e0, float e1, float e2) : e{e0, e1, e2} {}
    vec3(const vec3 &v) : vec3(v.e[0], v.e[1], v.e[2]) {}

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    float r() const { return e[0]; }
    float g() const { return e[1]; }
    float b() const { return e[2]; }

    const vec3 &operator+() { return *this; }
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float &operator[](int i) { return e[i]; }

    vec3 &operator+=(const vec3 &rhs);
    vec3 &operator-=(const vec3 &rhs);
    vec3 &operator*=(const vec3 &rhs);
    vec3 &operator*=(const float t);
    vec3 &operator/=(const vec3 &rhs);
    vec3 &operator/=(const float t);

    float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    float length() const { return sqrt(squared_length()); }
    void make_unit_vector();

private:
    float e[3];
};

// inline class member functions
inline vec3 &vec3::operator+=(const vec3 &rhs)
{
    *this = *this + rhs;
    return *this;
}

inline vec3 &vec3::operator-=(const vec3 &rhs)
{
    *this = *this - rhs;
    return *this;
}

inline vec3 &vec3::operator*=(const vec3 &rhs)
{
    *this = *this * rhs;
    return *this;
}

inline vec3 &vec3::operator*=(const float t)
{
    *this = *this * t;
    return *this;
}

inline vec3 &vec3::operator/=(const vec3 &rhs)
{
    *this = *this / rhs;
    return *this;
}

inline vec3 &vec3::operator/=(const float t)
{
    *this = *this / t;
    return *this;
}

inline void vec3::make_unit_vector()
{
    *this /= length();
}

// inline friend functions
inline std::istream &operator>>(std::istream &is, vec3 &vec)
{
    is >> vec.e[0] >> vec.e[1] >> vec.e[2];
    return is;
}

inline std::ostream &operator<<(std::ostream &os, vec3 &vec)
{
    os << vec.e[0] << " " << vec.e[1] << " " << vec.e[2];
    return os;
}

inline bool operator==(const vec3 &lhs, const vec3 &rhs)
{
    return lhs.e[0] == rhs.e[0] && lhs.e[1] == rhs.e[1] && lhs.e[2] == rhs.e[2];
}

inline bool operator!=(const vec3 &lhs, const vec3 &rhs)
{
    return !(lhs == rhs);
}

inline vec3 operator+(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1], lhs.e[2] + rhs.e[2]);
}

inline vec3 operator+(const vec3 &lhs, const float t)
{
    return vec3(lhs.e[0] + t, lhs.e[1] + t, lhs.e[2] + t);
}

inline vec3 operator+(const float t, const vec3 &rhs)
{
    return rhs + t;
}

inline vec3 operator-(const vec3 &lhs, const vec3 &rhs)
{
    return lhs + -rhs;
}

inline vec3 operator-(float t, const vec3 &rhs)
{
    return t + -rhs;
}

inline vec3 operator-(const vec3 &lhs, float t)
{
    return lhs + -t;
}

inline vec3 operator*(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.e[0] * rhs.e[0], lhs.e[1] * rhs.e[1], lhs.e[2] * rhs.e[2]);
}

inline vec3 operator*(float t, const vec3 &rhs)
{
    return vec3(t * rhs.e[0], t * rhs.e[1], t * rhs.e[2]);
}

inline vec3 operator*(const vec3 &lhs, float t)
{
    return t * lhs;
}

inline vec3 operator/(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.e[0] / rhs.e[0], lhs.e[1] / rhs.e[1], lhs.e[2] / rhs.e[2]);
}

inline vec3 operator/(const vec3 &lhs, float t)
{
    return lhs * (1 / t);
}

inline float dot(const vec3 &lhs, const vec3 &rhs)
{
    return lhs.e[0] * rhs.e[0] + lhs.e[1] * rhs.e[1] + lhs.e[2] * rhs.e[2];
}

inline vec3 cross(const vec3 &lhs, const vec3 &rhs)
{
    return vec3(lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1],
                -lhs.e[0] * rhs.e[2] + lhs.e[2] * rhs.e[0],
                lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]);
}

inline vec3 sqrt(const vec3 &rhs)
{
    return vec3(sqrt(rhs.e[0]), sqrt(rhs.e[1]), sqrt(rhs.e[2]));
}

inline vec3 unit_vector(vec3 v)
{
    v.make_unit_vector();
    return v;
}
