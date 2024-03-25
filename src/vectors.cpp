#pragma once

#include "vectors.hpp"

namespace vecs
{
    Vec2::Vec2() : X(0.0f), Y(0.0f) {}
    Vec2::Vec2(float X_, float Y_) : X(X_), Y(Y_) {}

    bool Vec2::operator==(const Vec2 &other) const
    {
        return (this->X == other.X && this->Y == other.Y);
    }

    bool Vec2::operator!=(const Vec2 &other) const
    {
        return (this->X != other.X || this->Y != other.Y);
    }

    Vec2 Vec2::operator+(const Vec2 &other) const
    {
        return Vec2(this->X + other.X, this->Y + other.Y);
    }

    Vec2 Vec2::operator-(const Vec2 &other) const
    {
        return Vec2(this->X - other.X, this->Y - other.Y);
    }

    Vec2 Vec2::operator*(const float &other) const
    {
        return Vec2(this->X * other, this->Y * other);
    }

    Vec2 Vec2::operator/(const float &other) const
    {
        return Vec2(this->X / other, this->Y / other);
    }

    float Vec2::norm() const
    {
        return sqrt(this->X * this->X + this->Y * this->Y);
    }

    float dot(const Vec2 &vec1, const Vec2 &vec2)
    // Produit scalaire entre deux vecteurs
    {
        return vec1.X * vec2.X + vec1.Y * vec2.Y;
    }

    Vec2 reflection(Vec2 v, Vec2 n)
    // La reflexion d'un vecteur par rapport à un autre (dans la plupart des cas, la normale)
    {
        return v - (n * vecs::dot(v, n) * 2);
    }

    // Vec2 cross(const Vec2 &vec1, const Vec2 vec2)
    // {
    //     return Vec2(0.0f, 0.0f);
    // }
    // Is the cross product in a 2 dimension universe relevant ?
    // Using the right hand rule, it isn't.
}
