#include "solver.hpp"

Solver::Solver() : system(20.0f, 0.0f), gravity(vecs::Vec2(0.0f, -9.81f)) {}

void Solver::update(float dt)
{
    applyGravity();
    applyConstraintV2(dt);
    // updatePositions(dt);
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
        // On a besoin d'un meilleur système de détection de collisions
        vecs::Vec2 normal = toObj / distance;
        this->system.velocity = vecs::reflectionV2(this->system.velocity, normal);
        this->system.position = center + normal * (-1) * distance;
    }
}

void Solver::updatePositions(float dt)
// Cette fonction sert plus ou moins à rien
{
    this->system.updatePosition(dt);
}

void Solver::applyConstraintV2(float dt)
{
    vecs::Vec2 center = vecs::Vec2();
    float radius = 100.0f;

    vecs::Vec2 nextPosition = this->system.position + this->system.velocity * dt;
    vecs::Vec2 nextVelocity = this->system.velocity + this->system.acceleration * dt;

    const vecs::Vec2 toObj = center - nextPosition;
    const float distance = toObj.norm();

    if (distance > radius)
    {
        float t_impact = (radius - this->system.position.norm()) / ((nextPosition - this->system.position).norm() - this->system.position.norm());
        // On met a jour la position et la vitesse pendant t_impact
        this->system.velocity = this->system.velocity + this->system.acceleration * t_impact;
        this->system.position = this->system.position + this->system.velocity * t_impact;
        // On calcul la reaction de la collision
        vecs::Vec2 normal = toObj / distance;
        this->system.velocity = vecs::reflectionV2(this->system.velocity, normal);
        this->system.velocity = this->system.velocity + this->system.acceleration * (dt - t_impact);
        this->system.position = this->system.position + this->system.velocity * (dt - t_impact);
    }
    else
    {
        this->system.velocity = nextVelocity;
        this->system.position = nextPosition;
    }
    this->system.acceleration = vecs::Vec2();
}