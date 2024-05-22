#include <iostream>
#include "vectors.hpp"
// #include "system.hpp"
#include "solver.hpp"
#include "loader.hpp"
#include <fstream>
#include "quadtree.hpp"
#include <cstdlib>

void afficheobjloader();
Quadtree *buildqtree(float width, float length, vecs::Vec2 point, float radius);
void testqtree();

int main()
{
    afficheobjloader();
    return 0;
}

Quadtree *buildqtree(float width, float length, vecs::Vec2 point, float radius)
{
    float newWidth = width / 2;
    float newLength = length / 2;
    Quadtree *qtree = (Quadtree *)malloc(sizeof(Quadtree));
    qtree->root = vecs::Vec2(newWidth, newLength);
    qtree->bottomleft = nullptr;
    qtree->bottomright = nullptr;
    qtree->topleft = nullptr;
    qtree->topright = nullptr;
    Quadtree *curr = qtree;
    vecs::Vec2 topleftcorner = vecs::Vec2(qtree->root.X - newWidth, qtree->root.Y + newLength);
    vecs::Vec2 bottomrightcorner = vecs::Vec2(qtree->root.X + newWidth, qtree->root.Y - newLength);
    while ((topleftcorner - point).norm() > radius && (bottomrightcorner - point).norm() > radius)
    {
        std::cout << curr->root.X << ", " << curr->root.Y << std::endl;
        Quadtree *child = (Quadtree *)std::malloc(sizeof(Quadtree));
        newWidth = newWidth / 2;
        newLength = newLength / 2;
        if (point.X < curr->root.X)
        {
            if (point.Y < curr->root.Y)
            {
                // recherche en bas à gauche
                child->root = vecs::Vec2(curr->root.X - newWidth, curr->root.Y - newLength);
                curr->bottomleft = child;
            }
            else
            {
                // recherche en haut à gauche
                child->root = vecs::Vec2(curr->root.X - newWidth, curr->root.Y + newLength);
                curr->topleft = child;
            }
        }
        else
        {
            if (point.Y < curr->root.Y)
            {
                // recherche en bas à droite
                child->root = vecs::Vec2(curr->root.X + newWidth, curr->root.Y - newLength);
                curr->bottomright = child;
            }
            else
            {
                // recherche en haut à droite
                child->root = vecs::Vec2(curr->root.X + newWidth, curr->root.Y + newLength);
                curr->topright = child;
            }
        }
        curr = child;
        topleftcorner = vecs::Vec2(curr->root.X - newWidth, curr->root.Y + newLength);
        bottomrightcorner = vecs::Vec2(curr->root.X + newWidth, curr->root.Y - newLength);
    }
    return qtree;
}

void testqtree()
{
    Quadtree *qtree = (Quadtree *)malloc(sizeof(Quadtree));
    qtree->bottomleft = nullptr;
    qtree->bottomright = nullptr;
    qtree->topleft = nullptr;
    qtree->topright = nullptr;
    buildqtree(500.0f, 500.0f, vecs::Vec2(0.0f, 0.0f), 10.0f);
    std::free(qtree);
}

void afficheobjloader()
{

    objl::Loader loader = objl::Loader();
    char filename[] = "models/big_terrain.obj";
    loader.load(filename);
    Solver solver = Solver();
    std::ofstream myfile;
    // myfile.open("tools/golf.txt", std::ofstream::out | std::ofstream::trunc);
    myfile.open("tools/coords.obj", std::ofstream::out | std::ofstream::trunc);
    float dt = 0.1f;
    float counter = 0.0f;
    // myfile << "[";
    while (counter < 40.0f)
    {
        // myfile << "(" << solver.system.position.X << "," << solver.system.position.Y << "," << solver.system.position.Z << ")";
        // myfile << ",";
        myfile << "v " << solver.system.position.X << " " << solver.system.position.Y << " " << solver.system.position.Z << "\n";

        solver.update(dt);
        counter += dt;
    }
    // myfile << "]";
    myfile.close();
}