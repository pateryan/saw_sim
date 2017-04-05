#include <iostream>

#include "lattice.hpp"

using namespace std;

int main(void)
{
    auto lattice = saw::Lattice(4, 4);
    lattice.print(cout);
    return 0;
}
