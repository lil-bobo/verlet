#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <math.h>

namespace vecs
{

    // Vecteur à deux coordonnées

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
    float dotV2(const Vec2 &vec1, const Vec2 &vec2);
    Vec2 reflectionV2(Vec2 v, Vec2 n);

    // Vecteur à trois coordonnées

    struct Vec3
    {
        Vec3();
        Vec3(float X_, float Y_, float Z_);
        bool operator==(const Vec3 &other) const;
        bool operator!=(const Vec3 &other) const;
        Vec3 operator+(const Vec3 &other) const;
        Vec3 operator-(const Vec3 &other) const;
        Vec3 operator*(const float &other) const;
        Vec3 operator/(const float &other) const;

        float norm();

        float X;
        float Y;
        float Z;
    };
    Vec3 crossV3(Vec3 v, Vec3 u);
    float dotV3(Vec3 v, Vec3 u);

}
