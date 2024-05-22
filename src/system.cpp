#include "system.hpp"

System::System(float X_, float Y_, float Z_, float radius) : acceleration(vecs::Vec3()), velocity(vecs::Vec3()), position(vecs::Vec3(X_, Y_, Z_)) { this->radius = radius; }

void System::accelerate(vecs::Vec3 acc)
{
    this->acceleration = this->acceleration + acc;
}

void System::updatePosition(float dt)
{
    this->velocity = this->velocity + this->acceleration * dt;
    this->position = this->position + this->velocity * dt;
    // On réinitialise le vecteur acceleration
    this->acceleration = vecs::Vec3();
}