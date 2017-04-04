#include <iostream>

#include "direction.hpp"

using namespace std;

int main(void)
{
    saw::Direction d;

    for (auto i = 0u; i < 4; ++i){
        d = (saw::Direction)i;
        cout << "Direction is " << saw::direction_string(d) << endl;
        cout << "Opposite direction is " << saw::direction_string(saw::opposite_direction(d)) << endl;
    }
    return 0;
}
