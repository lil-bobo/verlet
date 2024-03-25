#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

namespace vecs
{
    struct Vec2
    {
        Vec2();
        Vec2(float X_, float Y_);

        bool operator==(const Vec2 &other) const;
        bool operator!=(const Vec2 &other) const;
        Vec2 operator+(const Vec2 &other) const;
        Vec2 operator-(const Vec2 &other) const;
        Vec2 operator*(const float &other) const;
        Vec2 operator/(const float &other) const;

        float norm() const;

        float X;
        float Y;
    };
    float dot(const Vec2 &vec1, const Vec2 &vec2);
    Vec2 reflection(Vec2 v, Vec2 n);
}
