#pragma once

#include "vectors.hpp"

struct System
{
    System();
    vecs::Vec2 acceleration;
    vecs::Vec2 velocity;
    vecs::Vec2 position;
    void accelerate(vecs::Vec2 acc);
    void updatePosition(float dt);
};