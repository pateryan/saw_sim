#include "lattice.hpp"

#include <climits>

#define NUM_NEIGHBORS 4

namespace saw {

namespace impl {
static std::vector<std::size_t> 
calculate_neighbors(std::size_t width, std::size_t height, 
                    std::size_t loc, BoundaryCondition bc);
} // namespace impl

Lattice::Lattice(std::size_t width, std::size_t height, BoundaryCondition bc)
{
    this->bc                   = bc;
    this->width                = width;
    this->height               = height;
    this->size                 = width * height;
    this->lattice_sites        = std::vector<std::uint8_t>(size);
    this->nearest_neighbor_arr = std::vector<std::vector<std::size_t>>(size);

    for (auto i = 0ul; i < size; ++i) {
        nearest_neighbor_arr[i] = impl::calculate_neighbors(width, height, i, bc);
    }
    for (auto& i : lattice_sites) {
        i = 0;
    }
}

/**
 * prints the lattice in proper orientation (last element in top right corner)
 * to stream. Each line of the lattice is properly indented
 */
void 
Lattice::print(std::ostream& stream) const
{
    // warning, this is an unsigned number being decremented, having i >=
    // 0 will lead to an underflow on --i, resulting in an infinite loop.
    for (auto i = size - 1; i > 0; --i) {
        if ((i + 1) % width == 0) {
            stream << std::endl;
        }
        stream << (unsigned int)lattice_sites[i] << " ";
    }
    stream << (unsigned int)lattice_sites[0] << " ";
    stream << std::endl;
}

void
Lattice::print_neighbor(std::ostream& stream) const
{
    for (auto i = 0ul; i < size; ++i) {
        stream << i << ": ";
        for (auto v: nearest_neighbor_arr[i]) {
            if (v == INVALID_LATTICE_SITE) {
                stream << 'x' << ",\t";
            } else {
                stream << v << ",\t";
            }
        }
        stream << std::endl;
    }
}

std::size_t
Lattice::get_neighbor(std::size_t loc, Direction d)
{
    switch(d){
        case Direction::left:
            return nearest_neighbor_arr[loc][0];
        case Direction::up:
            return nearest_neighbor_arr[loc][1];
        case Direction::right:
            return nearest_neighbor_arr[loc][2];
        case Direction::down:
            return nearest_neighbor_arr[loc][3];
        case Direction::inval:
            return INVALID_LATTICE_SITE;
    }
    return INVALID_LATTICE_SITE; // shut up gcc warning
}

} // namespace saw

//----------------------------------------------------------------------------
//-----------------------INTERNAL FUNCTION DECLARATIONS-----------------------
//----------------------------------------------------------------------------

/*
 * These functions should remain unknown to Lattice, and should not be called
 * by the lattice api itself. They are purely implementation functions for the
 * implementation. The next section (STATIC FUNCTION IMPLEMENTATION) will
 * implement all static functions, incuding those known to Lattice.
 */

namespace saw { namespace impl {
// impl of static functions

// internal functions that Lattice does not need to know about
static std::vector<std::size_t> 
calculate_neighbors_periodic(std::size_t width, std::size_t height, 
                             std::size_t loc);

static std::vector<std::size_t> 
calculate_neighbors_finite(std::size_t width, std::size_t height, 
                           std::size_t loc);

//----------------------------------------------------------------------------
//-----------------------STATIC FUNCTION IMPLEMENTATION-----------------------
//----------------------------------------------------------------------------

static std::vector<std::size_t> 
calculate_neighbors(std::size_t width, std::size_t height, 
                    std::size_t loc, BoundaryCondition bc)
{
    auto vec = std::vector<std::size_t>(NUM_NEIGHBORS);
    if (bc == BoundaryCondition::periodic) {
       vec = calculate_neighbors_periodic(width, height, loc);
    } else {
       vec = calculate_neighbors_finite(width, height, loc);
    } 
    return vec;
}

static std::vector<std::size_t> 
calculate_neighbors_periodic(std::size_t width, std::size_t height, 
                             std::size_t loc)
{
    auto vec = std::vector<size_t>(NUM_NEIGHBORS);
    // special case where there is only one element
    if (width == 1 && height == 1) {
        vec[0] = 0;
        vec[1] = 0;
        vec[2] = 0;
        vec[3] = 0;
        return vec;
    }
    // left boundary
    if (loc % height == 0) {
        vec[0] = loc + (width - 1); 
    } else {
        vec[0] = loc - 1;
    }
    // top boundary
    if (loc >= width * (height - 1)) {
        vec[1] = loc - width * (height - 1);
    } else {
        vec[1] = loc + width;
    }
    // right boundary
    if ((loc + 1) % height == 0) {
        vec[2] = loc - (width - 1); 
    } else {
        vec[2] = loc + 1;
    }
    // bottom bounday
    if (loc < width) {
        vec[3] = loc + width * (height - 1);
    } else {
        vec[3] = loc - width;
    }
    return vec;
}

static std::vector<std::size_t> 
calculate_neighbors_finite(std::size_t width, std::size_t height, 
                             std::size_t loc)
{
    auto vec = std::vector<size_t>(NUM_NEIGHBORS);
    // left boundary
    if (loc % height == 0) {
        vec[0] = INVALID_LATTICE_SITE;
    } else {
        vec[0] = loc - 1;
    }
    // top boundary
    if (loc >= width * (height - 1)) {
        vec[1] = INVALID_LATTICE_SITE;
    } else {
        vec[1] = loc + width;
    }
    // right boundary
    if ((loc + 1) % height == 0) {
        vec[2] = INVALID_LATTICE_SITE;
    } else {
        vec[2] = loc + 1;
    }
    // bottom bounday
    if (loc < width) {
        vec[3] = INVALID_LATTICE_SITE;
    } else {
        vec[3] = loc - width;
    }
    return vec;
}

}} // namespace saw::impl
