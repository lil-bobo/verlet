#include "solver.hpp"

// on utilise des valeurs numériques pour reduire le nombre de variables
Solver::Solver() : system(0.0f, 0.0f, 5.0f, 0.03f), gravity(vecs::Vec3(0.0f, 0.0f, -20.0f)) {}

void Solver::update(float dt)
{
    applyGravity();
    applyConstraintV3(dt);
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

// void Solver::applyConstraintV3(float dt)
// {
//     // On se charge de détecter les collisions d'une balle de golf (system) sur un terrain quelconque qu'on représente par la structure de données Loader (avec les faces et les sommets et les normales aux sommets)
//     // On regarde plutôt si la balle VA rentrer en collision (c'est plus simple à coder et plus logique comme ca on évite les moments ou la balle est dans le sol)
//     // objl::Loader loader = objl::Loader();
//     // char filename[] = "models/cercle.obj";
//     // loader.load(filename);
//     vecs::Vec3 nextVelocity = this->system.velocity + this->system.acceleration * dt;
//     vecs::Vec3 nextPosition = this->system.position + this->system.velocity * dt;
//     bool impact = false;
//     for (const auto &face : this->loader.faces)
//     {
//         unsigned int s1 = face.vertexIndices[0];
//         unsigned int s2 = face.vertexIndices[1];
//         unsigned int s3 = face.vertexIndices[2];

//         vecs::Vec3 pos = this->system.position;
//         vecs::Vec3 s1tos2 = loader.vertices[s2] - loader.vertices[s1];
//         vecs::Vec3 s1tos3 = loader.vertices[s3] - loader.vertices[s1];

//         vecs::Vec3 n = loader.normals[s1] + loader.normals[s2] + loader.normals[s3]; // vecteur normal a la face

//         float d = -(vecs::dotV3(loader.vertices[s1], n)); // pour avoir la constante de l'équation cartésienne du plan

//         float t_impact = -d / (vecs::dotV3(pos, n)); // avoir le temps a partir duquel il y a impact
//         // Verifier que t_impact soit compris dans l'intervale de temps (entre t et t+dt)
//         if (t_impact > 0 && t_impact < dt)
//         {
//             // on est bien compris dans l'intervale
//             // alors il existe un impact pour cette surface donc on met a jour les deplacement
//             this->system.velocity = this->system.velocity + this->system.acceleration * t_impact;
//             this->system.position = this->system.position + this->system.velocity * t_impact;
//             // maintenant il reste dt - t_impact secondes à réaliser
//             // on fait le rebond avec la surface
//             this->system.velocity = this->system.velocity - n * ((vecs::dotV3(this->system.velocity, n)) * 2);
//             this->system.velocity = this->system.velocity + this->system.acceleration * (dt - impact);
//             this->system.position = this->system.position + this->system.velocity * (dt - impact);
//             impact = true;
//             break;
//         }
//     }
//     if (!impact)
//     {
//         this->system.position = nextPosition;
//         this->system.velocity = nextVelocity;
//     }
//     this->system.acceleration = vecs::Vec3();
// }

// void Solver::applyConstraintV3(float dt)
// {
//     vecs::Vec3 nextVelocity = this->system.velocity + this->system.acceleration * dt;
//     vecs::Vec3 nextPosition = this->system.position + this->system.velocity * dt;
//     bool impact = false;

//     objl::Loader loader = objl::Loader();
//     char filename[] = "models/map.obj";
//     loader.load(filename);

//     for (const auto &face : loader.faces)
//     {
//         unsigned int s1 = face.vertexIndices[0];
//         unsigned int s2 = face.vertexIndices[1];
//         unsigned int s3 = face.vertexIndices[2];

//         vecs::Vec3 pos = this->system.position;
//         float r = this->system.radius;
//         vecs::Vec3 s1tos2 = loader.vertices[s2] - loader.vertices[s1];
//         vecs::Vec3 s1tos3 = loader.vertices[s3] - loader.vertices[s1];

//         // Calculate the face normal
//         vecs::Vec3 n = vecs::crossV3(s1tos2, s1tos3) / vecs::crossV3(s1tos2, s1tos3).norm();

//         // Calculate d using one of the vertices of the face
//         float d = -(vecs::dotV3(n, loader.vertices[s1]));

//         // Calculate the distance of the sphere's center to the plane
//         float distToPlane = vecs::dotV3(pos, n) + d;

//         // Calculate the velocity projection onto the normal
//         float velocityProjection = vecs::dotV3(this->system.velocity, n);

//         // Check if the sphere is moving towards the plane
//         if (velocityProjection < 0 && fabs(distToPlane) <= r)
//         {
//             float t_impact = (r - distToPlane) / (-velocityProjection);
//             float cushion = 0.5;
//             // Check if the impact time is within the time step
//             if (t_impact >= 0 && t_impact < dt)
//             {
//                 std::cout << "impact aux coordonnées : (" << this->system.position.X << ", " << this->system.position.Y << ", " << this->system.position.Z << ")\n";
//                 // Update the system's state to the point of impact
//                 this->system.position = this->system.position + this->system.velocity * t_impact;
//                 this->system.velocity = this->system.velocity + this->system.acceleration * t_impact;

//                 // Reflect the velocity off the plane
//                 this->system.velocity = this->system.velocity - n * (2 * vecs::dotV3(this->system.velocity, n));
//                 this->system.velocity = this->system.velocity * cushion;
//                 // Continue with the remaining time after the impact
//                 float remainingTime = dt - t_impact;
//                 this->system.velocity = this->system.velocity + this->system.acceleration * remainingTime;
//                 this->system.position = this->system.position + this->system.velocity * remainingTime;

//                 impact = true;
//                 break;
//             }
//         }
//     }

//     if (!impact)
//     {
//         this->system.position = nextPosition;
//         this->system.velocity = nextVelocity;
//     }

//     this->system.acceleration = vecs::Vec3();
// }

// void Solver::applyConstraintV3(float dt)
// {
//     objl::Loader loader = objl::Loader();
//     char filename[] = "models/plat.obj";
//     loader.load(filename);
//     bool changed = false;
//     std::cout << this->system.position.Z << std::endl;
//     for (const auto &face : loader.faces)
//     {
//         // std::cout << "looping" << std::endl;
//         vecs::Vec3 normal, impactPoint;
//         if (ballIntersectsTriangle(loader, face, normal, impactPoint))
//         {
//             changed = true;
//             std::cout << "Collision détectée aux coordonnées : (" << impactPoint.X << ", " << impactPoint.Y << ", " << impactPoint.Z << ")" << std::endl;
//             float t_impact = vecs::distance(this->system.position, impactPoint) / this->system.velocity.norm();
//             this->system.position = impactPoint;
//             this->system.velocity = this->system.velocity - normal * (2 * vecs::dotV3(this->system.velocity, normal));
//             float remainingTime = dt - t_impact;
//             this->system.position = this->system.position + this->system.velocity * remainingTime;
//             break;
//         }
//     }
//     // std::cout << "\n";
//     if (!changed)
//     {
//         this->system.velocity = this->system.velocity + this->system.acceleration * dt;
//         this->system.position = this->system.position + this->system.velocity * dt;
//     }
//     this->system.acceleration = vecs::Vec3();
// }

bool Solver::ballIntersectsTriangle(objl::Loader loader, objl::Face face, vecs::Vec3 &normal, vecs::Vec3 &impactPoint)
{
    unsigned int s1 = face.vertexIndices[0];
    unsigned int s2 = face.vertexIndices[1];
    unsigned int s3 = face.vertexIndices[2];

    vecs::Vec3 edge1 = loader.vertices[s2] - loader.vertices[s1];
    vecs::Vec3 edge2 = loader.vertices[s3] - loader.vertices[s1];
    normal = vecs::crossV3(edge1, edge2).normalize();

    float distanceToPlane = vecs::dotV3(this->system.position - loader.vertices[s1], normal);
    if (std::abs(distanceToPlane) > this->system.radius)
    {
        return false;
    }

    vecs::Vec3 projectedCenter = this->system.position - normal * distanceToPlane;

    vecs::Vec3 v0 = loader.vertices[s3] - loader.vertices[s1];
    vecs::Vec3 v1 = loader.vertices[s2] - loader.vertices[s1];
    vecs::Vec3 v2 = projectedCenter - loader.vertices[s1];

    float dot00 = vecs::dotV3(v0, v0);
    float dot01 = vecs::dotV3(v0, v1);
    float dot02 = vecs::dotV3(v0, v2);
    float dot11 = vecs::dotV3(v1, v1);
    float dot12 = vecs::dotV3(v1, v2);

    float invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    bool isInTriangle = (u >= 0) && (v >= 0) && (u + v < 1);

    if (isInTriangle)
    {
        impactPoint = projectedCenter;
        return true;
    }

    if (vecs::distance(this->system.position, loader.vertices[s1]) <= this->system.radius)
    {
        impactPoint = loader.vertices[s1];
        return true;
    }
    if (vecs::distance(this->system.position, loader.vertices[s2]) <= this->system.radius)
    {
        impactPoint = loader.vertices[s2];
        return true;
    }
    if (vecs::distance(this->system.position, loader.vertices[s3]) <= this->system.radius)
    {
        impactPoint = loader.vertices[s2];
        return true;
    }

    auto pointToSegmentDistance = [](const vecs::Vec3 &p, const vecs::Vec3 &a, const vecs::Vec3 &b)
    {
        vecs::Vec3 ab = b - a;
        vecs::Vec3 ap = p - a;
        float t = vecs::dotV3(ap, ab) / vecs::dotV3(ab, ab);
        t = std::max(0.0f, std::min(1.0f, t));
        vecs::Vec3 projection = a + ab * t;
        return vecs::distance(p, projection);
    };

    if (pointToSegmentDistance(this->system.position, loader.vertices[s1], loader.vertices[s2]) <= this->system.radius)
    {
        impactPoint = loader.vertices[s1] + (loader.vertices[s2] - loader.vertices[s1]) * (vecs::dotV3(this->system.position - loader.vertices[s1], loader.vertices[s2] - loader.vertices[s1]) / vecs::dotV3(loader.vertices[s2] - loader.vertices[s1], loader.vertices[s2] - loader.vertices[s1]));
        return true;
    }
    if (pointToSegmentDistance(this->system.position, loader.vertices[s2], loader.vertices[s3]) <= this->system.radius)
    {
        impactPoint = loader.vertices[s2] + (loader.vertices[s3] - loader.vertices[s2]) * (vecs::dotV3(this->system.position - loader.vertices[s2], loader.vertices[s3] - loader.vertices[s2]) / vecs::dotV3(loader.vertices[s3] - loader.vertices[s2], loader.vertices[s3] - loader.vertices[s2]));
        return true;
    }
    if (pointToSegmentDistance(this->system.position, loader.vertices[s3], loader.vertices[s1]) <= this->system.radius)
    {
        impactPoint = loader.vertices[s3] + (loader.vertices[s1] - loader.vertices[s3]) * (vecs::dotV3(this->system.position - loader.vertices[s3], loader.vertices[s1] - loader.vertices[s3]) / vecs::dotV3(loader.vertices[s1] - loader.vertices[s3], loader.vertices[s1] - loader.vertices[s3]));
        return true;
    }

    return false;
}

void Solver::applyConstraintV3(float dt)
{
    objl::Loader loader = objl::Loader();
    char filename[] = "models/plat.obj";
    loader.load(filename);
    for (const objl::Face &face : loader.faces)
    {
        unsigned int s1 = face.vertexIndices[0]; // côté 1 du triangle
        unsigned int s2 = face.vertexIndices[1]; // côté 2 du triangle
        unsigned int s3 = face.vertexIndices[2]; // côté 3 du triangle

        // On étudie le mouvement qu'on s'apprête à faire

        vecs::Vec3 nextVelocity = this->system.velocity + this->system.acceleration * dt; // vitesse a la fin si tout se passe bie n
        vecs::Vec3 nextPosition = this->system.position + nextVelocity * dt;              // pareil pour la position

        // on regarde s'il existe un point de la droite reliant l'ancienne position a la nouvelle passant a travers le triangle
        vecs::Vec3 prevToNext = nextPosition - this->system.position;

        vecs::Vec3 c1 = loader.vertices[s2] - loader.vertices[s1];
        vecs::Vec3 c2 = loader.vertices[s3] - loader.vertices[s1];
        vecs::Vec3 normal = vecs::crossV3(c1, c2).normalize();

        float t = vecs::dotV3(normal, loader.vertices[s1]) - vecs::dotV3(normal, this->system.position);
        float denom = vecs::dotV3(prevToNext, vecs::Vec3(1.0f, 1.0, 1.0f));

        // Véfrifier que t_impact est valide

        if (denom == 0)
        {
            continue;
        }
        else
        {
            t = t / vecs::dotV3(prevToNext, vecs::Vec3(1.0f, 1.0, 1.0f)); // somme des coefficients de prevToNext
            // Ce n'est pas le temps mais plutot un coefficient
            if (t > 0 && t < dt)
            {
                // alors c'est bien une intersection
                // on vérifie maintenant que le point d'intersection appartient au triangle (cad entre les 3 sommets)
                // BARYCENTRE ETC
                vecs::Vec3 inter = this->system.position + prevToNext * t; // coordonnées du points d'intersection
                vecs::Vec3 c3 = inter - loader.vertices[s1];
                float u = vecs::dotV3(c3, c1);
                float v = vecs::dotV3(c3, c2);
                float w = vecs::dotV3(c1, c1);
                float x = vecs::dotV3(c2, c2);
                float y = vecs::dotV3(c2, c1);
                // Résolution
                float a;
                float b = (u * x - v * y) / (w * x - y * y); // OPTI: créer une constante pour calculer le denominateur qu'une seule fois
                float c = (v * w - u * y) / (w * x - y * y);
                a = 1 - b - c;
                // Le point est à l'interieur du triangle sous certaines conditions
                if (0 <= a && a <= 1 && 0 <= b && b <= 1 && 0 <= c && c <= 1)
                {
                    // collision
                }
            }
        }

        //

        // si oui, on regarde si le point d'intersection appartient au triangle
    }
}