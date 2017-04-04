#include "direction.hpp"

namespace saw{
Direction opposite_direction(Direction d)
{
    switch (d) {
        case Direction::left:
            return Direction::right;
            break;
        case Direction::up:
            return Direction::down;
            break;
        case Direction::right:
            return Direction::left;
            break;
        case Direction::down:
            return Direction::up;
            break;
        case Direction::inval:
            return Direction::inval;
            break;
        default:
            return Direction::inval;
            break;
    }
}

std::string
direction_string(Direction d)
{
    std::string s;
    switch(d) {
        case Direction::left:
            s = "left";
            break;
        case Direction::right:
            s = "right";
            break;
        case Direction::up:
            s = "up";
            break;
        case Direction::down:
            s = "down";
            break;
        case Direction::inval:
            s = "invalid";
            break;
        default:
            s = "invalid";
            break;
    }
    return s;
}
} // namespace saw
