#include "solver.hpp"

Solver::Solver() : system(), gravity(vecs::Vec2(0.0f, 9.81f)) {}

void Solver::update(float dt)
{
    applyGravity();
    applyConstraint();
    updatePositions(dt);
}

void Solver::applyGravity()
{
    this->system.accelerate(gravity);
}

void Solver::applyConstraint()
{
    // Dans un premier temps, notre contrainte spatiale sera un cercle de rayon r;
    // Le centre du cercle est en (0, 0)
    vecs::Vec2 center = vecs::Vec2();
    float radius = 100.0f;
    const vecs::Vec2 toObj = center - this->system.position;
    const float distance = toObj.norm();
    if (distance > radius)
    {
        // On fait la reflexion de la vélocité
        vecs::Vec2 normal = toObj / distance;
        this->system.velocity = vecs::reflection(this->system.velocity, normal);
    }
}

void Solver::updatePositions(float dt)
{
    this->system.updatePosition(dt);
}