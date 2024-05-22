#include "vectors.hpp"

namespace vecs
{
    // Vecteur à deux coordonnées

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

    float dotV2(const Vec2 &vec1, const Vec2 &vec2)
    // Produit scalaire entre deux vecteurs
    {
        return vec1.X * vec2.X + vec1.Y * vec2.Y;
    }

    Vec2 reflectionV2(Vec2 v, Vec2 n)
    // La reflexion d'un vecteur par rapport à un autre (dans la plupart des cas, la normale)
    {
        return v - (n * vecs::dotV2(v, n) * 2);
    }

    // Vecteur à trois coordonnées

    Vec3::Vec3() : X(0.0f), Y(0.0f), Z(0.0f) {}
    Vec3::Vec3(float X_, float Y_, float Z_) : X(X_), Y(Y_), Z(Z_) {}

    bool Vec3::operator==(const Vec3 &other) const
    {
        return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
    }

    bool Vec3::operator!=(const Vec3 &other) const
    {
        return (this->X != other.X || this->Y != other.Y || this->Z != other.Z);
    }

    Vec3 Vec3::operator+(const Vec3 &other) const
    {
        return Vec3(this->X + other.X, this->Y + other.Y, this->Z + other.Z);
    }

    Vec3 Vec3::operator-(const Vec3 &other) const
    {
        return Vec3(this->X - other.X, this->Y - other.Y, this->Z - other.Z);
    }

    Vec3 Vec3::operator*(const float &other) const
    {
        return Vec3(this->X * other, this->Y * other, this->Z * other);
    }

    Vec3 Vec3::operator/(const float &other) const
    {
        return Vec3(this->X / other, this->Y / other, this->Z / other);
    }

    float Vec3::norm()
    {
        return sqrt(this->X * this->X + this->Y * this->Y + this->Z * this->Z);
    }

    Vec3 Vec3::normalize()
    {
        return Vec3(this->X, this->Y, this->Z) / this->norm();
    }

    Vec3 crossV3(Vec3 v, Vec3 u)
    {
        return Vec3(v.Y * u.Z - v.Z * u.Y, v.Z * u.X - v.X * u.Z, v.X * u.Y - v.Y - u.X);
    }

    Vec3 reflectionV3(Vec3 v, Vec3 u)
    {
        return v - (u * vecs::dotV3(v, u) * 2);
    }

    float dotV3(Vec3 v, Vec3 u)
    {
        return v.X * u.X + v.Y * u.Y + v.Z + u.Z;
    }

    float distance(Vec3 v, Vec3 u)
    {
        return (v - u).norm();
    }
}
