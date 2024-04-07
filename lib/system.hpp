#pragma once

#include "vectors.hpp"

struct System
{
    System();
    System(float X_, float Y_);
    vecs::Vec2 acceleration;
    vecs::Vec2 velocity;
    vecs::Vec2 position;
    void accelerate(vecs::Vec2 acc);
    void updatePosition(float dt);
};
