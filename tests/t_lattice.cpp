#include <iostream>

#include "lattice.hpp"

using namespace std;

int main(void)
{
    cout << "testing lattice print method" << endl;
    cout << "periodic bounds" << endl;
    auto lattice = saw::Lattice(1, 1);
    for (auto i = 1; i < 5; ++i) {
        cout << "i = " << i << endl;
        lattice = saw::Lattice(i, i);
        lattice.print(cout);
        cout << endl;
        lattice.print_neighbor(cout);
    }
    cout << endl;
    cout << "testing lattice print method" << endl;
    cout << "finite bounds" << endl;
    for (auto i = 1; i < 5; ++i) {
        cout << "i = " << i << endl;
        lattice = saw::Lattice(i, i, saw::BoundaryCondition::finite);
        lattice.print(cout);
        cout << endl;
        lattice.print_neighbor(cout);
    }

    cout << endl;
    cout << "testing get_neighbor()" << endl;
    auto d = saw::Direction::left;
    lattice = saw::Lattice(4,4);
    cout << "periodic" << endl;
    cout << "left of lattice[0] is " << lattice.get_neighbor(0, d) << endl;
    cout << "left of lattice[1] is " << lattice.get_neighbor(1, d) << endl;
    d = saw::Direction::right;
    cout << "right of lattice[0] is " << lattice.get_neighbor(0, d) << endl;
    cout << "right of lattice[3] is " << lattice.get_neighbor(3, d) << endl;
    cout << "finite" << endl;
    lattice = saw::Lattice(4,4, saw::BoundaryCondition::finite);
    d = saw::Direction::left;
    if (lattice.get_neighbor(0, d) == INVALID_LATTICE_SITE) {
        cout << "left of lattice[0] is " << 'x' << endl;
    } else {
        cout << "left of lattice[0] is " << lattice.get_neighbor(0, d) << endl;
    }
    if (lattice.get_neighbor(1, d) == INVALID_LATTICE_SITE) {
        cout << "left of lattice[1] is " << 'x' << endl;
    } else {
        cout << "left of lattice[1] is " << lattice.get_neighbor(1, d) << endl;
    }
    d = saw::Direction::right;
    if (lattice.get_neighbor(0, d) == INVALID_LATTICE_SITE) {
        cout << "right of lattice[0] is " << 'x' << endl;
    } else {
        cout << "right of lattice[0] is " << lattice.get_neighbor(0, d) << endl;
    }
    if (lattice.get_neighbor(3, d) == INVALID_LATTICE_SITE) {
        cout << "right of lattice[3] is " << 'x' << endl;
    } else {
        cout << "right of lattice[3] is " << lattice.get_neighbor(3, d) << endl;
    }
        
    return 0;
}
