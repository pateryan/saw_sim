#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "direction.hpp"
#include "lattice.hpp"
#include "walk.hpp"

using namespace std;

namespace saw {

} // namespace saw

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "usage: " << argv[0] << " <length> <side_length> " << std::endl;
        return 1;
    }

    size_t walk_len = strtoul(argv[1], NULL, 10);
    size_t width    = strtoul(argv[2], NULL, 10);

    auto lat = saw::Lattice(width, width);

    /*
     * define rngs
     */
    std::random_device r;
    std::mt19937_64 twister(r());
    std::uniform_int_distribution<std::size_t> lat_gen(0, width * width - 1);
    std::uniform_int_distribution<std::uint8_t> walk_gen(0, 3);


    size_t start_position = lat_gen(twister);
    auto walk = saw::Walk(&lat, walk_len, start_position);
    walk.generate(twister, walk_gen);

    //lat.print_neighbor(cout);
    lat.print(cout);

    return 0;
}
