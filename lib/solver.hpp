#pragma once

#include "system.hpp"
#include "loader.hpp"

struct Solver
{
    Solver();
    System system;
    const vecs::Vec3 gravity;
    void update(float dt);                                                                                          // l'équivalent de main pour le code de Solver
    void applyGravity();                                                                                            // effet de pesanteur
    void updatePositions(float dt);                                                                                 // inutile
    void applyConstraintV3(float dt);                                                                               // controle des collisions (obosolète)
    bool ballIntersectsTriangle(objl::Loader loader, objl::Face face, vecs::Vec3 &normal, vecs::Vec3 &impactPoint); // détection d'intersection avec la surface
};
