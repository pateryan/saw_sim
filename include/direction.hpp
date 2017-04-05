#ifndef INCLUDE_DIRECTION_H 
#define INCLUDE_DIRECTION_H 1

#include <string>
#include <ostream>
#include <random>

#include <cstdint>

namespace saw {

enum class Direction : std::uint8_t
{
    right = 0,
    left  = 1,
    up    = 2,
    down  = 3,
    inval = 4
};

// Useful overload for printing out directions sanely.
std::ostream& operator<<(std::ostream& os, Direction d);

Direction   opposite_direction(Direction d);
std::string direction_string(Direction d);

//----------------------------------------------------------------------------
//--------------------------------CLASS DIRECTION_RNG-------------------------
//----------------------------------------------------------------------------

class Direction_rng
{
public:
    Direction_rng();
    ~Direction_rng() {};

    Direction generate_direction();
    Direction generate_nonreversing_direction();
private:
    std::mt19937 generator;
    std::uniform_int_distribution<std::uint8_t> dist;
    Direction last;
};

} // namespace saw
#endif // INCLUDE_DIRECTION_H
