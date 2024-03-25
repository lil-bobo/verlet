#pragma once

#include "vectors.hpp"
#include "system.hpp"

struct Solver
{
    Solver();
    System system;
    const vecs::Vec2 gravity;
    void update(float dt);
    void applyGravity();
    void applyConstraint();
    void updatePositions(float dt);
};