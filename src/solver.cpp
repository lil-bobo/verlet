#include "solver.hpp"

// on utilise des valeurs numériques pour reduire le nombre de variables
Solver::Solver() : system(0.0f, 0.0f, 1.2f, 1.0f), gravity(vecs::Vec3(0.0f, 0.0f, -9.81f)) {}

void Solver::update(float dt)
{
    applyGravity();
    // applyConstraintV3(dt);
    apply_constraint(dt);
    // updatePositions(dt);
}

void Solver::applyGravity()
{
    this->system.accelerate(gravity);
}

void Solver::updatePositions(float dt)
{
    // Cette fonction sert à rien
    this->system.updatePosition(dt);
}

float distance_squarred(vecs::Vec3 M_dt, vecs::Vec3 H)
{
    return (M_dt - H).norm();
}

vecs::Vec3 projeter_point_sur_triangle(vecs::Vec3 M_dt, vecs::Vec3 A, vecs::Vec3 n)
{
    return M_dt - n * vecs::dotV3(M_dt - A, n) / vecs::dotV3(n, n);
}

float trouver_k(vecs::Vec3 A, vecs::Vec3 B, vecs::Vec3 C, vecs::Vec3 M_t, vecs::Vec3 M_t_dt, float r)
{
    vecs::Vec3 n = vecs::crossV3(B - A, C - A);
    float tol = 0.000001;
    float k_min = 0, k_max = 1;

    while (k_max - k_min > tol)
    {
        float k = (k_min + k_max) / 2;
        vecs::Vec3 M_dt = M_t + (M_t_dt - M_t) * k;
        vecs::Vec3 H = projeter_point_sur_triangle(M_dt, A, n);
        if (distance_squarred(M_dt, H) < r * r)
        {
            k_max = k;
        }
        else
        {
            k_min = k;
        }
    }
    return (k_min + k_max) / 2;
}

bool is_in_triangle(vecs::Vec3 A, vecs::Vec3 B, vecs::Vec3 C, vecs::Vec3 M_t)
{
    vecs::Vec3 p12 = B - A;
    vecs::Vec3 p13 = C - A;

    vecs::Vec3 normal = vecs::crossV3(p13, p12);

    vecs::Vec3 p1M = M_t - A;

    vecs::Vec3 proj = normal * vecs::dotV3(p1M, normal) / vecs::dotV3(normal, normal);
    proj = p1M - proj;

    proj = M_t; // en fait le M_t dans lse parametres est déjà la projection du point sur le plan

    vecs::Vec3 p1H = proj - A; // du coté 1 vers la projection (H) de M sur le plan
    vecs::Vec3 p2H = proj - B; // du coté 2 vers la projection (H) de M sur le plan
    vecs::Vec3 p3H = proj - C; // du coté 3 vers la projection (H) de M sur le plan

    vecs::Vec3 p23 = C - B;

    float p1H_length = p1H.norm();
    float p2H_length = p2H.norm();
    float p3H_length = p3H.norm();

    float p12_length = p12.norm();
    float p13_length = p13.norm();
    float p23_length = p23.norm();

    // FORMULE DE HÉRON pour calculer l'air d'un triangle en ne connaissant que la longueur des 3 côtés

    float pa = (p12_length + p13_length + p23_length) / 2;                           // pour le grand triangle
    float a = sqrtf(pa * (pa - p12_length) * (pa - p13_length) * (pa - p23_length)); // aire du grand triangle

    float pa1 = (p12_length + p1H_length * p2H_length) / 2;
    float a1 = sqrtf(pa1 * (pa1 - p12_length) * (pa1 - p1H_length) * (pa1 - p2H_length));

    float pa2 = (p13_length + p1H_length * p3H_length) / 2;
    float a2 = sqrtf(pa2 * (pa2 - p13_length) * (pa2 - p1H_length) * (pa2 - p3H_length));

    float pa3 = (p23_length + p2H_length * p3H_length) / 2;
    float a3 = sqrtf(pa3 * (pa3 - p23_length) * (pa3 - p2H_length) * (pa3 - p3H_length));

    return (a == a1 + a2 + a3);
}

vecs::Vec3 calculate_rebound(vecs::Vec3 M_t, vecs::Vec3 M_t_plus_dt, vecs::Vec3 normal)
{
    vecs::Vec3 v = M_t_plus_dt - M_t; // Vecteur de mouvement
    return v - normal * 2 * vecs::dotV3(v, normal);
}

void Solver::apply_constraint(float dt)
{
    objl::Loader loader = objl::Loader();
    char filename[] = "models/test.obj";
    loader.load(filename);
    bool hasChanged = false;
    for (const auto &face : loader.faces)
    {
        unsigned int p1 = face.vertexIndices[0];
        unsigned int p2 = face.vertexIndices[1];
        unsigned int p3 = face.vertexIndices[2];

        vecs::Vec3 A = loader.vertices[p1];
        vecs::Vec3 B = loader.vertices[p2];
        vecs::Vec3 C = loader.vertices[p3];

        vecs::Vec3 M_t = this->system.position;
        vecs::Vec3 M_t_dt = this->system.position + this->system.velocity * dt;

        float k = trouver_k(A, B, C, M_t, M_t_dt, this->system.radius);

        vecs::Vec3 M_k = M_t + (M_t_dt - M_t) * k;
        vecs::Vec3 n = vecs::crossV3(B - A, C - A).normalize();
        vecs::Vec3 H = projeter_point_sur_triangle(M_k, A, n);

        bool inTriangle = is_in_triangle(A, B, C, H);

        float distance_to_plane = (M_k - H).norm();

        // Il faut que la distance entre M et H soit superieur ou égale au rayon pour qu'il n'y ait pas de collisions
        // Si la distance est inférieur au rayon, alors il y a collision

        if (inTriangle && distance_to_plane <= this->system.radius)
        {
            // simulation du rebond
            vecs::Vec3 rebound_vector = calculate_rebound(M_t, M_k, n);
            this->system.velocity = rebound_vector / dt;
            this->system.position = M_k;
            hasChanged = true;
        }
        else
        {
            // ne rien faire
            continue;
        }
    }
    if (!hasChanged)
    {
        this->system.velocity = this->system.velocity + this->system.acceleration * dt;
        this->system.position = this->system.position + this->system.velocity * dt;
    }
    this->system.acceleration = vecs::Vec3();
}