#include <iostream>

#include "lattice.hpp"

using namespace std;

int main(void)
{
    auto lattice = saw::Lattice(4, 4);
    lattice.print(cout);
    lattice.print_neighbor(cout);
    return 0;
}
