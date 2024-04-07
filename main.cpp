#include <iostream>
#include "vectors.hpp"
// #include "system.hpp"
#include "solver.hpp"
#include "loader.hpp"

int main()
{
    Solver solver;
    objl::Loader loader = objl::Loader();
    char filename[] = "models/terrain.obj";
    loader.load(filename);
    return 0;
}
