#ifndef INCLUDE_DIRECTION_H 
#define INCLUDE_DIRECTION_H 1

#include <string>

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

Direction opposite_direction(Direction d);
std::string direction_string(Direction d);

} // namespace saw
#endif // INCLUDE_DIRECTION_H
