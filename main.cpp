#include <iostream>
#include "vectors.hpp"
#include "system.hpp"
#include "solver.hpp"

int main()
{
    Solver solver;
    float counter = 0.0f;
    float dt = 0.1f;
    while (counter < 10.0f)
    {
        solver.update(dt);
        std::cout << "(" << solver.system.position.X << "," << solver.system.position.Y << ")" << std ::endl;
        counter += dt;
    }
    return 0;
}