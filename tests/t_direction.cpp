#include <iostream>
#include <random>
#include <chrono>

#include "direction.hpp"

#define GENERATE_DIRECTION_NUM 10
#define RNG_STRESS_TEST 10000000 // ten million

using namespace std;

int main(void)
{
    saw::Direction d;

    for (auto i = 0u; i < 4; ++i){
        d = (saw::Direction)i;
        cout << "Direction is " << saw::direction_string(d) << endl;
        cout << "Opposite direction is " << saw::direction_string(saw::opposite_direction(d)) << endl;
    }

    // test Direction_rng
    auto rng = saw::Direction_rng();

    cout << "Randomly generating " << GENERATE_DIRECTION_NUM << " directions" << endl;
    for (auto i = 0; i < GENERATE_DIRECTION_NUM; ++i) {
        if ((i == 16) || (i == GENERATE_DIRECTION_NUM -1)) {
            cout << rng.generate_direction() << endl;
        } else {
            cout << rng.generate_direction() << ", ";
        }
    }

    cout << "Randomly generatign " << GENERATE_DIRECTION_NUM << " non-reversing directions" << endl;
    for (auto i = 0; i < GENERATE_DIRECTION_NUM; ++i) {
        // Note this also tests the operator << overload.
        if ((i == 16) || (i == GENERATE_DIRECTION_NUM -1)) {
            cout << rng.generate_nonreversing_direction() << endl;
        } else {
            cout << rng.generate_nonreversing_direction() << ", ";
        }
    }

    cout << "Testing randomness of rng functions" << endl;
    cout << "Tested with " << RNG_STRESS_TEST << " iterations" << endl;
    size_t flag[4] = {0u};
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0ul; i < RNG_STRESS_TEST; ++i) {
        auto d = rng.generate_direction();
        //cout << d << endl;
        switch (d) {
            case saw::Direction::left:
                flag[0]++;
                break;
            case saw::Direction::right:
                flag[1]++;
                break;
            case saw::Direction::up:
                flag[2]++;
                break;
            case saw::Direction::down:
                flag[3]++;
                break;
            case saw::Direction::inval:
                cout << "invalid direction generated!" << endl;
                break;
            default:
                cout << "invalid direction generated!" << endl;
                break;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end - start;
    cout << "left generated:  " << flag[0] << " (" << 100 * ((double)flag[0]) / RNG_STRESS_TEST << "%)" << endl;
    cout << "right generated: " << flag[1] << " (" << 100 * ((double)flag[1]) / RNG_STRESS_TEST << "%)" << endl;
    cout << "up generated:    " << flag[2] << " (" << 100 * ((double)flag[2]) / RNG_STRESS_TEST << "%)" << endl;
    cout << "down generated:  " << flag[3] << " (" << 100 * ((double)flag[3]) / RNG_STRESS_TEST << "%)" << endl;
    cout << endl;
    cout << "Stress test took " << elapsed_time.count() << " seconds" << endl;

    return 0;
}
