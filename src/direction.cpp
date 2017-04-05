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

std::ostream& operator<<(std::ostream& os, const Direction d)
{
    os << direction_string(d);
    return os;
}


Direction_rng::Direction_rng()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<std::uint8_t> rng(0, 3);
    this->generator = mt;
    this->dist = rng;
    this->last = Direction::inval;
}

Direction
Direction_rng::generate_nonreversing_direction()
{
    auto d = Direction::inval;
    do {
        d = (Direction)dist(generator);
    } while (d == opposite_direction(last));
    this->last = d;
    return d;
}

Direction
Direction_rng::generate_direction()
{
    auto d = (Direction)dist(generator);
    this->last = d;
    return d;
}

} // namespace saw
