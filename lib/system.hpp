#pragma once

#include "vectors.hpp"

struct System
{
    System();
    System(float X_, float Y_, float Z_, float radius);
    vecs::Vec3 acceleration;
    vecs::Vec3 velocity;
    vecs::Vec3 position;
    float radius;
    void accelerate(vecs::Vec3 acc);
    void updatePosition(float dt);
};
