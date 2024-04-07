#include "system.hpp"

System::System(float X_, float Y_) : acceleration(vecs::Vec2()), velocity(vecs::Vec2()), position(vecs::Vec2(X_, Y_)) {}

void System::accelerate(vecs::Vec2 acc)
{
    this->acceleration = this->acceleration + acc;
}

void System::updatePosition(float dt)
{
    this->velocity = this->velocity + this->acceleration * dt;
    this->position = this->position + this->velocity * dt;
    // On réinitialise le vecteur acceleration
    this->acceleration = vecs::Vec2();
}