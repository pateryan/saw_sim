#ifndef INCLUDE_LATTICE_H
#define INCLUDE_LATTICE_H 1

#include <vector>
#include <ostream>
#include <cstdint>
#include <climits>

#include "direction.hpp"

#define INVALID_LATTICE_SITE INT_MAX

namespace saw {

enum class BoundaryCondition : std::uint8_t {
    periodic = 0,
    finite   = 1
};

class Lattice {
public:
    Lattice(std::size_t width, std::size_t height, 
            BoundaryCondition bc = BoundaryCondition::periodic);
    ~Lattice() {};

    BoundaryCondition get_bc(void) {return bc;}
    std::uint8_t operator [](std::size_t i) const {return lattice_sites[i];}
    std::uint8_t& operator [](std::size_t i) {return lattice_sites[i];}
    std::size_t get_size() {return width * height;}

    void print(std::ostream&) const;
    void print_neighbor(std::ostream&) const;
    void reset(void);
    std::size_t get_neighbor(std::size_t position, Direction d);

private:
    std::vector<std::uint8_t> lattice_sites;
    std::size_t width;
    std::size_t height;
    std::size_t size;
    BoundaryCondition bc;
    std::vector<std::vector<std::size_t>> nearest_neighbor_arr;
};

} // namespace saw
#endif // INCLUDE_LATTICE_H
